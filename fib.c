#include <stdio.h>
#include <pthread.h>

public int fib(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else return fib(n - 1) + fib(n - 2);
}

int main() {
	int n;
	int f;

	printf( "Enter fib number:" );
	scanf( "%d", &n );
	f = fib(n);
	printf( "Fib of %d is %d. \n", n, f);
	getchar();
	return 0;
}
