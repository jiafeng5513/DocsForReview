// ComponentA.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

class C : public IX, public IY
{
public:
	C( ) { theCounter = 0; otherData = 0; }
	virtual bool QueryInterface(int interfaceID,void** pValue);
	virtual void AddRef( ) { theCounter++ ; }
	virtual void Release( ) 
	{
		if (theCounter > 0)
			theCounter--;
		if (theCounter == 0)
			delete this;
	}
	virtual void f1( )
	{ 
		::MessageBox(NULL,"接口Ix中f1 被触发","接口Ix提供服务",MB_OK|MB_ICONINFORMATION) ;	
	}
	virtual void f2( )
	{ 
		::MessageBox(NULL,"接口Ix中f2 被触发","接口Ix提供服务",MB_OK|MB_ICONINFORMATION) ;	
	}
	virtual void g1( )
	{ 
		::MessageBox(NULL,"接口Iy中g1 被触发","接口Iy提供服务",MB_OK|MB_ICONINFORMATION) ;	
	}
	virtual void g2( ) 
	{ 
		::MessageBox(NULL,"接口Iy中g2 被触发","接口Iy提供服务",MB_OK|MB_ICONINFORMATION) ;	
	}

private:
	long theCounter;
	int otherData;
};

bool C::QueryInterface(int interfaceID,void** pValue)
{
	switch (interfaceID)
	{
		case IUnknownID :
		{
			*pValue = static_cast<IX*> (this);
			break;
		}
		case IXID :
		{
			*pValue = static_cast<IX*> (this);
			break;
		}
		case IYID :
		{
			*pValue = static_cast<IY*> (this);
			break;
		}
		default:
		return false;
	}
	this->AddRef( );
	return true;
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
		::MessageBox(NULL,name,"组件所在位置",MB_OK|MB_ICONINFORMATION) ;	

	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
//		delete pTheFactory;
	}
	return TRUE;
}

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
