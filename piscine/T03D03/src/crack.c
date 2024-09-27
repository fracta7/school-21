#include <stdio.h>

void check_code(float x, float y);

int main() {
    float x;
    float y;

    //get user input for x and y
    printf("Enter x value:");
    if ((scanf("%f", &x)) == 1) {
        printf("Enter y value:");
        if ((scanf("%f", &y)) == 1) {
            // if everything is correct, we pass to function
            check_code(x, y);
        }
    } else {
        printf("n/a\n");
    }
}

void check_code(float x, float y) {
    // first we calculate using the equation
    float equation = x * x + y * y;
    if (equation < 25) {
        // print GOTCHA if it is inside
        printf("GOTCHA\n");
    } else {
        // print MISS if it is outside
        printf("MISS\n");
    }
}

