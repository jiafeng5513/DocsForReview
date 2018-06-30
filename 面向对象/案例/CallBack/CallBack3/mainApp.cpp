#include <iostream.h>
#include <stdio.h>

class Server
{
public:
	Server( ) { }
	void F( ) 
		{ step1( ); step2( );step3( ); step4( );}
	virtual void step1( ) = 0;
	virtual void step2( ){ cout << "step2 is done by the server" << endl; }
	virtual void step3( ){ cout << "step3 is done by the server" << endl; }
	void step4( ){ cout << "step4 is done by the server" << endl; } 
	virtual ~Server( ) { }
private:
	//....
};

class Client
{
public:
	void G(Server* pS)
	{
		//....
		pS->F( );
		//....
	}
};

class S1: public Server
{
public:
	virtual void step1( ) 
		{cout << "step1 is done by the client" << endl; }
	virtual void step2( ) 
		{cout << "step2 is done by the client" << endl; }
	virtual void step3( )
		{cout << "step3 is done by the client" << endl; }
};


void main( )
{
	Client  aClient;
	Server* ps = new S1;
	aClient.G(ps);
	delete ps;

    char c = getchar( );
}
