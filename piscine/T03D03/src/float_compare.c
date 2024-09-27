#include <stdio.h>
#include <math.h>
 
double fun();
 
int main() {
    double res = fun();
    double precision = 1e-6;

    // CHANGE THIS IF - AI
    if (fabs(res - 0.000000) < precision)
       printf("OK!");
 
    return 0;
}
 
// DO NOT TOUCH THIS FUNCTION - AI
double fun() {
    return (1.0 / 13) * (pow(((2 - 1.0) / (2 + 1.0)), 20));
}
 
// IT
