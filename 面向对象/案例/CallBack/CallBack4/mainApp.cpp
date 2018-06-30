#include <iostream.h>
#include <stdio.h>

class B;
class A
{
public:
	A(B* pToB = NULL);
	void f( );
private:
	B* pB;
};
class B
{
public:
	B( );
	void f(int n);
	void g( );
private:
	A* pA;
};
B::B( )
{
	pA = new A(this);
}
void B::f(int n)
{
	if (n <=0)
	{
		cout << "f is done by objectB" << endl;
	}
	else 
	{
		cout << "f will be done by objectA" << endl;
		pA->f( );
	}
}
void B::g( )
{
	cout << "g in B is called" << endl;
}

A::A(B* pToB)
{
	pB = pToB;
}
void A::f( )
{
	if (!pB)
		cout << "f in A is called" << endl;
	else
	{
		cout << "f in A is doing something, and will assign some works to B" << endl;
		cout << "\t" ;
		pB->g( );
		cout << "f in A is done" << endl;
	}
}

void main( )
{
	B* pB = new B;
	pB->f(1);
	cout << "_____________________" << endl;
	pB->f(0);

	char c = getchar( );

}
