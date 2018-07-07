#include <iostream.h>

class Interface
{
public:
	virtual void f( ) = 0;
};

//----------------------------------------------
class Server : public Interface
{
public:
	void f( )
	{ 
		cout << "Service from Server " << endl;
	}
};

//----------------------------------------------

class Stub : public Interface
{
public:
	void f( )
	{
		Server* pS = new Server;
		//可以借助其它技术，使得Server不可见；
		//即：仅针对Interface编程.
		pS->f( ); 
		delete pS;
	}
};

class Client
{
public:
	void g( )
	{
		//Step1( );
		//Step2( );
		Stub* pStub = new Stub;
		pStub->f( );
		delete pStub;
		//OtherSteps( );
	}
};


int main( )
{
	Client c;
	c.g( );

	return 0;
}