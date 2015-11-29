#include <stdio.h>
#include <pthread.h>

typedef struct {
	int n;
	long res;
} FibArgs;

void *fib(void *arg) {
	FibArgs *args = arg;
	if ( args->n == 0 )
		args->res = 0;
	else if ( args->n == 1 )
		args->res = 1;
	else {
		FibArgs one = { args->n - 1, 0 };
		FibArgs two = { args->n - 2, 0 };
		pthread_t th1, th2;
		
		pthread_create( &th1, NULL, fib, &one );
		pthread_create( &th2, NULL, fib, &two );

		pthread_join( th1, NULL );
		pthread_join( th2, NULL );
		args->res = one.res + two.res;
	}

	return 0;
}

int main() {
	int n;
	pthread_t tid;

	printf( "Enter fib number:" );
	scanf( "%d", &n );

	FibArgs start = { n, 0 };
	pthread_create( &tid, NULL, fib, &start );
	pthread_join( tid, NULL );

	printf( "Fib of %d is %ld. \n", n, start.res);
	getchar();
	return 0;
}
