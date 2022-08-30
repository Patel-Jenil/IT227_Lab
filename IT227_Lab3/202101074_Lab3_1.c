#include <stdio.h>
#include <stdlib.h>
// Jenil_Patel_202101074
// array of function pointers (*fns[](int n))

void fib(unsigned long long n) {
    unsigned long long A, A_1 = 1, A_2=1;
	printf(":\n");
	if (n <= 0) {
		printf("0\n");
		return;
	}
	if (1 <=n)
		printf("1 ");
	if (2 <=n )
		printf("1 ");
		
	for (long i=3; i<=n; ++i) {
		A = A_1 + A_2;
		printf("%llu ", A);
		A_1 = A_2;
		A_2 = A;
	}
	printf("\n");
}

void fact(unsigned long long n) {
    if (n<0) {
		printf("-1");
		return;
	}
	unsigned long long ans = 1; 
	while (n--) {
		ans *= (n+1);
	}
	printf("%llu\n" , ans);
}

void numlen(unsigned long long n) {
    unsigned long count = 0;
    while (n>0 && ++count)
        n/=10;
    printf("%lu\n", count);
}

void stop(unsigned long long n) {
	printf("\nAdios Amigo\n\n");
	exit(0);
}

int main() {
	void (*fns[4])(unsigned long long n) = {fib, fact, numlen ,stop};
	unsigned long long n;
	int choice;
    char *prefix[] = {"The Fibonacci series upto", "-->", "Length of the number [", ""};
    char *suffix[] = {"", "! = ", "] = ", ""};
	while(1) {
		printf("\n=====================================");
		printf("\n1. Fibonacci series upto n.\n");
		printf("2. Factorial\n");
		printf("3. Number-length\n");
		printf("4. Exit\n");
		printf("Enter operation to perform: ");
		scanf("%d", &choice);
		if (choice<1 || choice>4)
			printf("\n%d invalid option\n", choice);
		else {
            if (choice == 4)
                goto exitPoint;
			printf("Enter the number: ");
			scanf("%llu", &n);
			printf("\n%s %llu %s",prefix[choice-1],n, suffix[choice-1]);
            exitPoint:
			fns[choice-1](n);
		}
		getchar();
		getchar();
	}
    return 0;
}