#include <stdio.h>

int sum(int a, int b);
int substract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

int main() {
    int a;
    int b;
    
    printf("Enter the first number:");
    
	// checking the first input for digits, otherwise output incorrect input
	if (scanf("%d", &a) == 1) {
        printf("Enter the second number:");
	    
		// checking for digit input
		if (scanf("%d", &b) == 1) {
			int addition = sum(a, b);
	        int difference = substract(a, b);
	        int multiplication = multiply(a, b);
			
			// check for division by 0, if so, print n/a
			if (b == 0){
			    printf("%d %d %d n/a\n", addition, difference, multiplication);
			} else {
			    int division = divide(a, b);
				printf("%d %d %d %d\n", addition, difference, multiplication, division);
			}
		} else {
	        printf("\nIncorrect input\n");
        }
    } else {
	    printf("\nIncorrect input\n");
	}

	return 0;
}

int sum(int a, int b) { return a + b; }

int multiply(int a, int b) { return a * b; }

int substract(int a, int b) { return a - b; }

int divide(int a, int b) { return a / b; }


