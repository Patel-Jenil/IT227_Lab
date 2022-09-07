#include <stdio.h>
#include "202101074_Lab4_1_myheader.h"
#define PI 3.14159265
#define LIMIT 10
// PATEL_JENIL_202101074

int main() {
    double sinx = 0, x , xBackup;
    printf("\nEnter the value of x (degrees) to find sin(x): ");
    scanf("%lf", &x);
    xBackup = x;
    x = x*((double)PI/180.0);
    for (int i=1, j=1; i<=LIMIT; ++i, j+=2) {
        if (i%2 == 1) {
            sinx += ((double)mypow(x,j)/myfact(j));
        } else {
            sinx += -((double)mypow(x,j)/myfact(j));
        }
    }
    
    printf("Sin(%0.2lf): %0.6lf\n\n", xBackup, sinx);
    return 0;
}