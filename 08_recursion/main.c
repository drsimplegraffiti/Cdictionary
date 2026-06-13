#include <stdio.h>

unsigned long long factorial(int n);

int main() {
    int num;
    printf("Enter your number: ");
    scanf("%d", &num);
    printf("Factorial of %d is %llu\n", num, factorial(num));
    return 0;
}

unsigned long long factorial(int n) {
    if (n <= 1) {
        printf("base case reached: factorial(1) = 1\n");
        return 1;
    } else {
        printf("calling: factorial(%d) = %d * factorial(%d)\n", n, n, n - 1);
        unsigned long long result = n * factorial(n - 1);
        printf("returning: factorial(%d) = %llu\n", n, result);
        return result;
    }
}
