#include <iostream.h>

bool isPrime(int);
int  add(int,int);
float add(float,float);

int main( )
{
	for (int i = 2; i<20; i++)
		if (isPrime(i))
			cout << i << endl;
	cout << "____________" << endl;
	cout << add(10,20) << endl;

	return 0;
}