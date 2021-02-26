#include <stdio.h> 

int factorial(int n)
{
	printf("factorial(%d)\n", n);
	if(n<=1) return(1);
	else return n*factorial(n-1);
}

int factorial_iter(int n)
{
	int i, result=1;
	for(i=1; i<=n; i++)
		result *= i;
	return(result);
}

double slow_power(double x, int n)
{
	int i;
	double r = 1.0;
	for(i=0; i<n; i++)
		r *= x;
	return(r);
}

double iter_power(double x, int n)
{
	if(n==0) return(1.0);
	else if(n==1) return(x);
	else return(x*iter_power(x, n-1));
}

double power(double x, int n)
{
	if(n==0) return 1;
	else if((n%2)==0)
		return power(x*x, n/2);
	else return x*power(x*x, (n-1)/2);
}

int fib(int n)
{
	if(n==0) return 0;
	else if(n==1) return 1;
	else return (fib(n-1)+fib(n-2));
}

int fib_iter(int n)
{
	if(n<2) return n;
	else
	{
		int tmp, current=1, last=0;
		for(i=2; i<=n; i++)
		{
			tmp = current;
			current += last;
			last = tmp;
		}
		return current;
}
