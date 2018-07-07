#include <iostream.h>

class A
{
public:
	A(int anInt = 0) : i (anInt) { }
	void setInt(int anInt )
	{
		i = anInt;
	}
	int getInt( ) const 
	{ return i; }
private:
	int i;
};

class B
{
public:
	B(int anInt = 0) : j (anInt) { }
	void setJ(int anInt )
	{
		j = anInt;
	}
	int getJ( ) const 
	{ return j; }
private:
	int j;
};

int main( )
{
	A* pA = new A(100);
	B* pB = reinterpret_cast<B*> (pA);
	
	pB->setJ(1000);
	cout << pA->getInt( ) << endl;

	return 0;
}