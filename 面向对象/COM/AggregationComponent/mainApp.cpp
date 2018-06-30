/*模拟实现组件组件的聚合，

基本情况：

被聚合的内部组件具有两个业务接口 I3,I4
聚合者（外部组件）具有两个业务接口 I1,I2
OuterComponent：
	I1 { f1 }
	I2 { f2 }
InnerComponent:
	I3 { f3 }
	I4 { f4 }


目标：
1.内部组件可以被外部组件聚合使用；
2.内部组件可以独立被使用；

下面代码未考虑的主要事情如下：
1.引用计数的运用逻辑；
2.COM库中对相关接口、函数的标准定义；
3.多文件形式；
4.动态链接库的实现方式；
5.bool返回类型的函数调用结果的真假值判断；
另外，测试得并不充分，很可能存在Bug.
*/

#include <iostream.h>
#include <stdio.h>

#define IID_I1  1
#define IID_I2  2
#define IID_I3  3
#define IID_I4  4
#define IID_IUnknown 5
#define IID_INonDelegatingUnknown 6  //不需要被客户知道
#define IID_IClassFactory 7
#define CLSID_IDCompoentInner 8
#define CLSID_IDCompoentOuter 9

class IUnknown
{
public:
	virtual bool QueryInterface(int interfaceID, void** ppv) = 0;
	virtual void AddRef( ) = 0;
	virtual void Release( ) = 0;
};

class I1 : public IUnknown
{
public:
	virtual void f1( ) = 0;
};

class I2 : public IUnknown
{
public:
	virtual void f2( ) = 0;
};

class I3 : public IUnknown
{
public:
	virtual void f3( ) = 0;
};

class I4 : public IUnknown
{
public:
	virtual void f4( ) = 0;
};

class IClassFactory : public IUnknown
{
public:
	virtual bool CreateInstance(IUnknown* pOuter, int interfaceID, void** ppv) = 0;
};

class INonDelegatingUnknown 
{
//对被聚合组件来说，是真正的IUnknown接口
//不需要被客户知道，只需被其类厂知道.
public:
	virtual bool NondelegatingQueryInterface(int interfaceID, void** ppv) = 0;
	virtual void NondelegatingAddRef( ) = 0;
	virtual void NondelegatingRelease( ) = 0;
};

//_________________________________________________________________
//被聚合组件的实现
class InnerComponet : public I3, public I4, public INonDelegatingUnknown
{
private:
	long m_theCounter;
	IUnknown* m_pUnknownOuter;
public:
	InnerComponet(IUnknown* pUnknownOuter)
	{
		m_theCounter = 1;
		if (pUnknownOuter == 0)
			m_pUnknownOuter = reinterpret_cast<IUnknown*>
					(static_cast<INonDelegatingUnknown*>(this));
		else
			m_pUnknownOuter = pUnknownOuter;
	}

	/* 虽然是正规的IUnknown接口中的函数，但对被聚合组件来说，
	随后的三个函数，是假的IUnknown接口实现 */
	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		return m_pUnknownOuter->QueryInterface(interfaceID,ppv);
		//正是因为把任务转交(代理)出去了，所以说是假的.
		//可能转交给外层（聚合者），也可能转交给自己.
	}

	virtual void AddRef( )
	{
		m_pUnknownOuter->AddRef( );
	}
	virtual void Release( )
	{
		m_pUnknownOuter->Release( );
	}
	//以下三个函数，虽然名字不正规，但对被聚合组件来说，
	//是其真正的IUnknown接口中三个函数的实现.
	//是自己对IUnknown接口的实现.
	virtual bool NondelegatingQueryInterface(int interfaceID, void** ppv)
	{
		if (interfaceID == IID_IUnknown)
			*ppv = static_cast<INonDelegatingUnknown*>(this);
		else if (interfaceID == IID_I3)
			*ppv = static_cast<I3*>(this);
		else if (interfaceID == IID_I4)
			*ppv = static_cast<I4*>(this);
		else
		{
			*ppv = 0;
			return false;
		}
		return true;
	}

	virtual void NondelegatingAddRef( )
	{
		m_theCounter++;
	}

	virtual void NondelegatingRelease( )
	{
		if (--m_theCounter == 0)
			delete this;
	}
	virtual void f3( )
	{
		cout << "f3 in the inner component is called." << endl;
	}
	virtual void f4( )
	{
		cout << "f4 in the inner component is called." << endl;
	}

};

class InnerComponetFactory : public IClassFactory
{
private:
	long m_theCounter;
public:
	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		if ((interfaceID == IID_IUnknown)
		     ||(interfaceID == IID_IClassFactory))
			*ppv = static_cast<IClassFactory*> (this);
		else
		{
			*ppv = 0;
			return false;
		}
		return true;
	}

	virtual void AddRef( )
	{
		m_theCounter++;
	}

	virtual void Release( ) 
	{
		if (--m_theCounter == 0)
			delete this;
	}
	virtual bool CreateInstance(IUnknown* pOuter, int interfaceID, void** ppv)
	{
		if ((pOuter!=0) && (interfaceID != IID_IUnknown))
			return false;
		InnerComponet* pInner = new InnerComponet(pOuter);
		bool returnValue = pInner->NondelegatingQueryInterface(interfaceID,ppv);
		return returnValue;
	}
};

//下面是模拟的内部组件导出函数
bool GetClassObject_InnerComponet(int classID,int interfaceID,void** ppv)
{
	if (classID != CLSID_IDCompoentInner)
		return false;
	InnerComponetFactory* pFactory = new InnerComponetFactory;
	bool returnValue = pFactory->QueryInterface(interfaceID,ppv);
	return returnValue;
}

//_________________________________________________________________

//随后是外部组件（聚合者）的实现
//外部组件也可能是其它组件的内部组件(可聚合组件)，
//这里没把它实现成可聚合组件.

class OuterComponent : public I1, public I2
{
private:
	I3* m_pI3;
	IUnknown* m_pInner;
	long m_theCounter;
public:
	OuterComponent( )
	{
		m_pI3 = 0;
		m_pInner = 0;
		m_theCounter = 1;
		IClassFactory* pInnerFactory;
		//随后代码未做函数返回值真假判定
		GetClassObject_InnerComponet(
				CLSID_IDCompoentInner,
				IID_IClassFactory,
				(void**)&pInnerFactory);
		IUnknown* pOuter = static_cast<I1*>(this);
		 pInnerFactory->CreateInstance(
				pOuter,IID_IUnknown,(void**)&m_pInner);
		m_pInner->QueryInterface(IID_I3,(void**)&m_pI3);
	}

	~OuterComponent( )
	{//类似如下代码，本例子中没考虑引用计数
		if (m_pI3)
			m_pI3->Release( );
		if (m_pInner)
			m_pInner->Release( );
	}

	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		if (interfaceID == IID_IUnknown)
			*ppv = static_cast<I1*> (this);
		else if (interfaceID == IID_I1)
			*ppv = static_cast<I1*> (this);
		else if (interfaceID == IID_I2)
			*ppv = static_cast<I2*> (this);
		else if (interfaceID == IID_I3)
			*ppv = m_pI3;
		else
		{
			*ppv = 0;
			return false;
		}
		//若考虑引用计数，可写出类似如下代码，
		//但需要在合适地方匹配Release；
		//reinterpret_cast<IUnknown*>(*ppv)->AddRef( );
		return true;
	}

	virtual void AddRef( )
	{
		m_theCounter++;
	}

	virtual void Release( )
	{
		if (--m_theCounter==0)
			delete this;
	}
	virtual void f1( )
	{
		cout << "f1 in the outer component is called." << endl;
	}
	virtual void f2( )
	{
		cout << "f2 in the outer component is called." << endl;
	}
};

class OuterComponetFactory : public IClassFactory
{
private:
	long m_theCounter;
public:
	virtual bool QueryInterface(int interfaceID, void** ppv)
	{
		if ((interfaceID == IID_IUnknown)
		     ||(interfaceID == IID_IClassFactory))
			*ppv = static_cast<IClassFactory*> (this);
		else
		{
			*ppv = 0;
			return false;
		}
		//reinterpret_cast<IUnknown*>(*ppv)->AddRef( );
		return true;
	}

	virtual void AddRef( )
	{
		m_theCounter++;
	}

	virtual void Release( ) 
	{
		if (--m_theCounter == 0)
			delete this;
	}
	virtual bool CreateInstance(IUnknown* pOuter, int interfaceID, void** ppv)
	{
		if (pOuter!=0) //这里不考虑被聚合
			return false;
		OuterComponent* theOuterComponent = new OuterComponent;
		bool returnValue = theOuterComponent->QueryInterface(interfaceID,ppv); 
		/*if (returnValue)
			theOuterComponent->Release( ); 
			*/
		return returnValue;
	}
};

bool GetClassObject_OuterComponet(int classID,int interfaceID,void** ppv)
{
	if (classID != CLSID_IDCompoentOuter)
		return false;
	OuterComponetFactory* pFactory = new OuterComponetFactory;
	bool returnValue = pFactory->QueryInterface(interfaceID,ppv);
	return returnValue;
}

int main( )
{
	cout << "外部组件模拟测试：" << endl;
	IClassFactory* pOuterFactory;
	GetClassObject_OuterComponet(
		CLSID_IDCompoentOuter,
		IID_IClassFactory,
		(void**)&pOuterFactory);
	IUnknown* pOuterComponent;
	pOuterFactory->CreateInstance(
			0,IID_IUnknown,(void**)&pOuterComponent); 
	I1* pI1;
	pOuterComponent->QueryInterface(IID_I1,(void**)&pI1);
	pI1->f1( ); 
	I2* pI2;
	pOuterComponent->QueryInterface(IID_I2,(void**)&pI2);
	pI2->f2( );
	I3* pI3;
	pOuterComponent->QueryInterface(IID_I3,(void**)&pI3);
	pI3->f3( );
	I4* pI4;
	pOuterComponent->QueryInterface(IID_I4,(void**)&pI4);

	bool bValue = pOuterComponent->QueryInterface(IID_I4,(void**)&pI4);
	if (bValue == false)
		cout << "Interface I4 is not supported by the outer component." <<endl;
	
	cout << endl << endl <<endl;
	cout << "内部组件独立（未被聚合）模拟测试：" << endl;
	IClassFactory* pInnerFactory;
	GetClassObject_InnerComponet(
		CLSID_IDCompoentInner,
		IID_IClassFactory,
		(void**)&pInnerFactory);
	IUnknown* pInnerComponent;
	pInnerFactory->CreateInstance(
		0,IID_IUnknown,(void**)&pInnerComponent);
	I1*  pToI1;
	pInnerComponent->QueryInterface(IID_I1,(void**)&pToI1);
	if (bValue == false)
		cout << "Interface I1 is not supported by the inner component." <<endl;
	I2*  pToI2;
	pInnerComponent->QueryInterface(IID_I2,(void**)&pToI2);
	if (bValue == false)
		cout << "Interface I2 is not supported by the inner component." <<endl;
	I3*  pToI3;
	pInnerComponent->QueryInterface(IID_I3,(void**)&pToI3);
	pToI3->f3( ); 
	I4*  pToI4;
	pInnerComponent->QueryInterface(IID_I4,(void**)&pToI4);
	pToI4->f4( ); 
	cout << endl << endl;

	cout << "按任意键结束测试" << endl;
	getchar( );
	return 0;
}

