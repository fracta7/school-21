#include <stdio.h>

int main() {
	int a;
	int b;

	printf("Enter the first number:");

	// first we check if the input is digit
	if (scanf("%d", &a) == 1) {
		printf("Enter the second number:");

		// then we check the second number
		if (scanf("%d", &b) == 1) {
			
			// we compare if the first digit is higher than the second.
			// if it is higher we print the first, otherwise the second.
			if (a > b) {
				printf("%d\n", a);
			} else {
				printf("%d\n", b);
			}
		} else {
			// print n/a in case not a number
			printf("\nn/a\n");
		}
	} else {
		// print n/a in case not a number
		printf("\nn/a\n");
	}

	return 0;
}
