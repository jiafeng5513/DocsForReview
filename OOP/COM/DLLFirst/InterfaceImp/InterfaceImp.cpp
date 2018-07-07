// InterfaceImp.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "GameInterface.h"
#include "DiceGame.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}
/*
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
	}
	return TRUE;
}
*/

extern "C" __declspec(dllexport) GameInterface* getGame( )
{
	GameInterface*	pI = new DiceGame;
	return pI;
}

int num = 0;

extern "C" __declspec(dllexport) void setNum( )
{
	cout << "Input an integer number: " ;
	cin >> num;
}

extern "C" __declspec(dllexport) int getNum( )
{
	return num;
}

