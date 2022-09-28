#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>
#include <unistd.h>

double expo(double x, int n) {
    double sum = 1.0, pow = x, fact = 1.0; // initialize sum of series
    for (int i = 1; i <= n; i++){
        sum += 1.0 * (pow / fact);
        pow *= x;
        fact *= (i + 1);
    }
    return sum;
}

double main(int argc, char *argv[]) {
    double x, p;
    int n;
    x = atof(argv[1]);
    n = atoi(argv[2]);
    p = expo(x, n);
    printf("\nChild(PID=%d) : e^(%lf) upto %d terms = %lf\n", getpid(), x, n, p);
    exit(p);
}