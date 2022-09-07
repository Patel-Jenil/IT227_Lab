#include <stdio.h>
#include "202101074_Lab4_1_myheader.h"
#define PI 3.14159265
#define LIMIT 10
// PATEL_JENIL_202101074

int main() {
    float sinx = 0, x , xBackup;
    printf("Enter the value of x (degrees) to find sin(x)");
    scanf("%f", &x);
    xBackup = x;
    x = x*(PI/180);
    for (int i=1, j=1; i<=LIMIT; ++i) {
        if (i%2 == 1) {
            sinx += (mypow(x,j)/myfact(j));
        } else {
            sinx += -(mypow(x,j)/myfact(j));
        }
    }
    
    printf("Sin(%0.2f): %f", xBackup, sinx);
    return 0;
}