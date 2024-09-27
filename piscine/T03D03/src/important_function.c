#include <stdio.h>
#include <math.h>

float math_function(float x);

int main() {
    float input;
  
    printf("Enter your number:");

    // we check for correct input, otherwise "n/a"
    if ((scanf("%f", &input)) == 1) {
      float result = math_function(input);

      // print rounded result
      printf("%.1f\n", result);
    } else {
      printf("n/a\n");
    }

    return 0;
}

float math_function(float x) {
    // we divide the formula to parts so it won't be too long
    float part1 = 7e-3 * pow(x, 4);
    float part2 = ((22.8 * pow(x, 1 / 3) - 1e3) * x + 3) / (x * x / 2);
    float part3 = x * pow((10 + x), 2 / x);
    // we combine the parts and return the value
    return part1 + part2 - part3 - 1.01;
}
