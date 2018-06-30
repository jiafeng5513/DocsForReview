// ComponentA.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

class C;
class A : public IX
{
private:
	C* pOuter;
public:
	A(C* pC) { pOuter = pC; } 
	virtual bool QueryInterface(int interfaceID,void** pValue);
	virtual void AddRef( );
	virtual void Release( );
	virtual void f1( )
	{ 
		cout << "接口Ix中f1 被触发!" << endl;
	}
	virtual void f2( )
	{ 
		cout << "接口Ix中f2 被触发!" << endl;
	}
};

class B : public IY
{
private:
	C* pOuter;
public:
	B(C* pC){ pOuter = pC; }
	virtual bool QueryInterface(int interfaceID,void** pValue);
	virtual void AddRef( );
	virtual void Release( );
	virtual void g1( )
	{ 
		cout << "接口Iy中g1 被触发!" << endl;
	}
	virtual void g2( ) 
	{ 
		cout << "接口Iy中g2 被触发!" << endl;
	}
};

class C
{
public:
	C( );
	~C( );
	virtual bool QueryInterface(int interfaceID,void** pValue);
	virtual void AddRef( );
	virtual void Release( );
private:
	long theCounter;
	A* theA;
	B* theB;
};

C::C( )
{
	theA = new A(this);
	theB = new B(this);
	theCounter = 0;
}

C::~C( )
{
	delete theA;
	delete theB;
}

bool C::QueryInterface(int interfaceID,void** pValue)
{
	switch (interfaceID)
	{
		case IUnknownID :
		{
			*pValue = theA;
			break;
		}
		case IXID :
		{
			*pValue = theA;
			break;
		}
		case IYID :
		{
			*pValue = theB;
			break;
		}
		default:
		return false;
	}
	this->AddRef( );
	return true;
}
void C::AddRef( )
{
	theCounter++;
}
void C::Release( ) 
{
	if (theCounter > 0)
		theCounter--;
	if (theCounter == 0)
		delete this;
};

bool A::QueryInterface(int interfaceID,void** pValue)
{
	return pOuter->QueryInterface(interfaceID,pValue);
}
void A::AddRef( )
{
	pOuter->AddRef( );
}
void A::Release( )
{
	pOuter->Release( );
}

bool B::QueryInterface(int interfaceID,void** pValue)
{
	return pOuter->QueryInterface(interfaceID,pValue);
}
void B::AddRef( )
{
	pOuter->AddRef( );
}
void B::Release( )
{
	pOuter->Release( );
}


class Factory : public IMyClassFactory
{
public:
	Factory( ) { theCounter = 0; }
	virtual void AddRef( ) { theCounter++ ; }
	virtual void Release( ) 
	{
		if (theCounter > 0)
			theCounter--;
		if (theCounter == 0)
			delete this;
	}
	virtual bool QueryInterface(int interfaceID,void** pValue)
	{
		if ((interfaceID == IUnknownID ) || 
			(interfaceID == IClassFactoryID ))
		{
			*pValue = static_cast<IMyClassFactory* > (this) ;
			return true;
		}
		else
			return  false;
	}

	virtual bool CreateInstance(int interfaceID, void** pValue)
	{
		C* pC = new C;
		return (pC->QueryInterface( interfaceID,pValue));
	}
private:
	long theCounter;
};

IMyClassFactory* pTheFactory;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
 	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		pTheFactory = new Factory;
		char name[100];
		::GetModuleFileName(HINSTANCE(hModule), name, 100);
		cout << "组件所在位置是：" << name << endl ;	
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
//		delete pTheFactory; //用户通过Release释放，则不需要.
	}
	return TRUE;
}

/*
class A
{
public:
	void f( )
	{
	}
};

class Factory1
{
public:
	A* newInstance( )
	{
		return new A;
	}
};

class Factory2
{
public:
	A* newInstance( )
	{
		return new A;
	}
};

void main( )
{
	Factory1 f;
	A* pA = f.newInstance( );
	pA->f( ); 
}
*/

/*
extern "C" __declspec(dllexport) IMyUnkonwn* getComp( )
{
	C* pC = new C;
	IMyUnkonwn* theRet;
	pC->QueryInterface(IUnknownID,&theRet);
	
	return theRet;
}
*/

extern "C" __declspec(dllexport) bool GetClassObject(int ComponetID,int ClassFactoryIID,void** pValue)
{
	if (ComponetID != CompAID )
		return false;
	if (ClassFactoryIID != IClassFactoryID )
		return false;
//	pTheFactory = new Factory;
	return pTheFactory->QueryInterface(ClassFactoryIID,pValue);
}
//extern "C" __declspec(dllexport) 

















