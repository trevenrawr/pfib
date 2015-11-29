#include <stdio.h>
#include <pthread.h>

int fib(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else return fib(n - 1) + fib(n - 2);
}

int main() {
	int n;
	long f;

	printf( "Enter fib number: " );
	scanf( "%d", &n );
	f = fib(n);
	printf( "Fib of %d is %ld. \n", n, f);
	getchar();
	return 0;
}
