#include <stdio.h>
#include <stdlib.h>
// Jenil_Patel_202101074
// array of function pointers (*fns[](int n))

void fib(long n) {
    long long A, A_1 = 1, A_2=1;
	printf(":\n");
	if (n <= 0) {
		printf("0\n");
		return;
	}
	if (1 <=n) {
		printf("1 ");
	}
	if (2 <=n ) {
		printf("1 ");
	}
	for (long i=3; i<=n; ++i) {
		A = A_1 + A_2;
		printf("%lld ", A);
		A_1 = A_2;
		A_2 = A;
	}
	printf("\n");
}

void fact(long n) {
    if (n<0) {
		printf("-1");
		return;
	}
	long long ans = 1, temp = n; 
	while (n--) {
		ans *= temp;
	}
	printf("%lld\n" , ans);
}

void numlen(long n) {
	if (n < 0) {
		n *= -1;
	}
    int count = 0;
    while (n>0 && ++count)
        n/=10;
    printf("%d\n", count);
}

void stop(long n) {
	printf("\nAdios Amigo\n\n");
	exit(0);
}

int main() {
	void (*fns[4])(long n) = {fib, fact, numlen ,stop};
	long int n;
	int choice;
    char *prefix[] = {"The Fibonacci series upto", "-->", "Length of the number [", ""};
    char *suffix[] = {"", "! = ", "] = ", ""};
	while(1) {
		printf("\n=====================================");
		printf("\n1 for Fibonacci series upto n.\n");
		printf("2 for Factorial\n");
		printf("3 for Number-length\n");
		printf("4 for Exit\n");
		printf("Enter operation to perform: ");
		scanf("%d", &choice);
		if (choice<1 || choice>4)
			printf("\n%d invalid option\n", choice);
		else {
            if (choice == 4)
                goto exitPoint;
			printf("Enter the number: ");
			scanf("%ld", &n);
			printf("\n%s %ld %s",prefix[choice-1],n, suffix[choice-1]);
            exitPoint:
			fns[choice-1](n);
		}
	}
    return 0;
}