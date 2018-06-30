#include <iostream.h>
#include <stdio.h>

class I
{
public:
	virtual void f1( ) = 0;
	virtual void f2( ) = 0;
};

class Server
{
public:
	void FF(I* pI)
	{
		cout << "Step1 in Server::FF(will be done by the client) " << endl;
		pI->f1( );
		cout << "Step2 in Server::FF(will be done by the client) " << endl;
		pI->f2( );
		cout << "Step3 in Server::FF(done by the Server)"<< endl;
	}
};

class Client
{
public:
	void sendRequest(Server& aServer,I* pObjOfI)
	{
		aServer.FF(pObjOfI);
	}
};

class ConcreteOneImpOfI:public I
{
public:
	void f1( )
	{
		cout << "\t A sort of implementation of f1 defined in interface I" << endl;
	}
	void f2( )
	{
		cout << "\t A sort of implementation of f2 defined in interface I" << endl;
	}
};

void main( )
{
	Server theServer;
	Client theClient;

	I* pI = new ConcreteOneImpOfI;
	theClient.sendRequest(theServer,pI); 

	char c = getchar( );
}
