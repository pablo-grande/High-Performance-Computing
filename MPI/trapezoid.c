#include <stdlib.h>
#include <stdio.h>

double f(double x)
{
	return(4.0/(1.0+x*x));
}

double fragment(double a, double b, long long unsigned int num_fragments, double h)
{
	double est, x;
	long long unsigned int i;

 	est = (f(a) + f(b))/2.0;
	for (i=1; i<=num_fragments-1; i++){
		x = a + i*h;
		est += f(x);
	}
	est = est*h;

	return est;	
}

int main(int argc, char **argv) {

	int i;
	//long long unsigned int n=100000000000;
	//Reduce n in order of 5
	long long unsigned int n=1000000;
	double a=0.0, b=1.0, h=0.0;
	double result=0.0;

	h = (b-a)/n;
	result = fragment(a, b, n, h);

	printf("Result: %.20ff\n", result);
	
	exit(0);
}
