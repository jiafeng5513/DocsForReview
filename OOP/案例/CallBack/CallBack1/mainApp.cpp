#include <iostream.h>
#include <stdio.h>
class Server
{
public:
	void F(int (*pFun)(int ,int ),int a,int b)
	{
		cout <<"Step1 is done by Server::F" << endl;
		int temp = pFun(a,b);
		cout << temp << endl;
		cout <<"Step3 is done by Server::F" << endl;
	}
};


class Client
{
public:
	void sendRequest(Server& aServer,int (* pF)(int,int),int a,int b)
	{
		aServer.F(pF,a,b);
	}
};


int func1(int x, int y)
{
	cout << "func1 is called" << endl;
	return (x+y);
}

int func2(int x, int y)
{
	cout << "func2 is called" << endl;
	return (x-y);
}


void main( )
{
	Server theServer;
	Client theClient;
	theClient.sendRequest(theServer,func1,10,20);
	cout << "-------" << endl;

	theClient.sendRequest(theServer,func2,10,20);
	cout << "_______" << endl;
	char c = getchar();
}
