#include <math.h>
#include <stdio.h>

double witch_of_agnesi(double x);
double lemniscate_of_bernoulli(double x);
double quadratic_hyperbola(double x);

int main() {
    int entries;
    double start;
    double end;
    double increment;

    entries = 42;
    start = -M_PI;
    end = M_PI;
    increment = (end - start) / (entries - 1);

    for (int i = 0; i < entries; ++i) {
        double value = start + i * increment;
        double agnesi_value = witch_of_agnesi(value);
        double lemniscate_value = lemniscate_of_bernoulli(value);
        double hyperbola_value = quadratic_hyperbola(value);
        printf("%.7lf | ", value);
        printf("%.7lf | ", agnesi_value);
        if (lemniscate_value > 0) {
            printf("%.7lf | ", lemniscate_value);
        } else {
            printf("- | ");
        }
        printf("%.7lf", hyperbola_value);
        if (i != entries) {
            printf("\n");
        }
    }

    return 0;
}

double witch_of_agnesi(double x) { return 1.0 / (1.0 + x * x); }

double lemniscate_of_bernoulli(double x) { return sqrt(sqrt(1.0 + 4.0 * x * x) - x * x - 1.0); }

double quadratic_hyperbola(double x) { return 1.0 / (x * x); }
