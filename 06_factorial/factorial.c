#include <stdio.h>

int main() {
  int n;
  unsigned long long factorial = 1; // int is 32-bit, max value 2,147,483,647
                                    // (~2.1 billion):
  // unsigned long long is 64-bit, max value 18,446,744,073,709,551,615:
  // use unsigned long long to avoid overflow
  printf("Enter factorial !: ");

  scanf("%d", &n);

  if (n < 2 || n >= 21) {
    printf("factorial must be between 2 and 20\n");
    return -1;
  }

  for (int i = 1; i <= n; i++) {
    // same as :
    //            1        * 1
    // factorial = factorial * 1;

    printf("index * factorial = %d * %llu = %llu \n", i, factorial,
           i * factorial);
    factorial *= i;
  }
  printf("Factorial is: %llu\n", factorial);
  return 0;
}
