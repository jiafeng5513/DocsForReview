#include <windows.h>
#include <iostream.h>
#include "GameInterface.h"
int main( )
{
	HINSTANCE Hp = ::LoadLibrary("InterfaceImp.dll"); 
	if (Hp == NULL)
	{
		cout << "Error" << endl;
		return 1;
	}
	GameInterface* (*pFunc)( );
	 pFunc = (GameInterface* (*)())::GetProcAddress(Hp,"getGame");
	if (pFunc == NULL)
	{
		cout << "Error at calling" << endl;
		return 2;
	}
	GameInterface* pGame = pFunc( );
	pGame->run( ); 

	void (*pF1)( );
	pF1 = (void (*)())::GetProcAddress(Hp,"setNum"); 
	if (pF1 == NULL)
	{
		cout << "Error at calling" << endl;
		return 3;
	}

	int (*pF2)( );
	pF2 = (int (*)())::GetProcAddress(Hp,"getNum"); 
	if (pF2 == NULL)
	{
		cout << "Error at calling" << endl;
		return 4;
	}
	
	int i = 1;

	while (i)
	{
		pF1( );
		i = pF2( );
		cout << i << endl;
	}

	::FreeLibrary(Hp);
	return 0;
}