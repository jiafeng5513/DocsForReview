#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include "interface.h"

int main( )
{
	TRACE("Entering client main\n");
	IUnknown* pUnk;
	IMotion* pMot;
	IVisual* pVis;
	IClassFactory* pClf;
	GetClassObject(CLSID_CSpaceship,IID_IClassFactory,
		(void**)&pClf);
	pClf->CreateInstance(IID_IUnknown,(void**)&pUnk);
	pUnk->QueryInterface(IID_IMotion,(void**)&pMot); 
	pMot->QueryInterface(IID_IVisual,(void**)&pVis);
	TRACE("main:pUnk=%p,pMot=%p,pVis=%P\n",pUnk,pMot,pVis);
	pMot->Fly( );
	int nPos=pMot->GetPosition( );
	TRACE("npos=%d\n",nPos);
	pVis->Display( );
	pClf->Release( );
	pUnk->Release( );
	pMot->Release( );
	pVis->Release( );
	return 0;
}