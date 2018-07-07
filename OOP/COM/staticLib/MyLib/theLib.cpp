
bool isPrime(int n)
{
	for (int i = 2; i <= n/2; i++)
		if (n % i == 0)
			return false;
	return true;
}

int add(int i, int j)
{
	return (i+j);
}

float add(float i, float j)
{
	return (i+j);
}

