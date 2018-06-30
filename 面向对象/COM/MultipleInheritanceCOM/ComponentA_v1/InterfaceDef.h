#ifndef _interfaceDef_h_
#define _interfaceDef_h_

#define IUnknownID  0
#define IXID  1
#define IYID  2
#define IClassFactoryID 10
#define CompAID 100

bool div(float a, float b,float* pRet)
{
	if (...)
	{
		*pRet = a/b;
		return true;
	}
	else
		return false;
}


class IMyUnknown //纯的抽象类间接表示接口
{
public:
	virtual bool QueryInterface(int interfaceID,void** pValue) = 0;
	virtual void AddRef( ) = 0;
	virtual void Release( ) = 0;
};


class IX : public IMyUnknown
{
public:
	virtual void f1( ) = 0;
	virtual void f2( ) = 0;
};

class IY : public IMyUnknown
{
public:
	virtual void g1( ) = 0;
	virtual void g2( ) = 0;
};

class IMyClassFactory : public IMyUnknown
{
public:
//	virtual IMyUnknown* CreateInstance( ) = 0;
	virtual bool CreateInstance(int interfaceID, void** pValue) = 0;
};

#endif