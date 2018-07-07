#include "interfaceDef.h"
#include <windows.h>
#include <stdio.h>

/*
extern "C" __declspec(dllexport) bool GetClassObject(int ComponetID,int ClassFactoryIID,void** pValue)
{
	if (ComponetID != CompAID )
		return false;
	if (ClassFactoryIID != IClassFactoryID )
		return false;
//	pTheFactory = new Factory;
	return pTheFactory->QueryInterface(ClassFactoryIID,pValue);
}
*/

int main( )
{
	HINSTANCE theLib = ::LoadLibrary("ComponentA.dll");
	if (theLib == NULL)
		return -1;
	bool (*pFunc)(int,int,void** );
	pFunc = (bool (*) (int,int,void**)) ::GetProcAddress(theLib,"GetClassObject");
	if (pFunc == NULL)
		return -2;

	IMyClassFactory* pFactory;
	if (pFunc(CompAID,IClassFactoryID,(void**)&pFactory))
	{
		IMyUnknown* pIUnk;
		if (pFactory->CreateInstance(IUnknownID, (void**)&pIUnk))
		{
			IX* pIx;
			if ( pIUnk->QueryInterface( IXID,(void**)&pIx))
			{
				pIx->f1( );
				pIx->f2( ); 
				pIx->Release( );
			}
			IY* pIy;
			if ( pIUnk->QueryInterface( IYID,(void**)&pIy))
			{
				pIy->g2( );
				pIy->g2( );
				pIy->Release( );
			}
			pIUnk->Release( );		
		}
		pFactory->Release( ); 
	}
	::FreeLibrary(theLib);
	printf("按任意键结束客户程序......");
	getchar( );
	return 0;
}
