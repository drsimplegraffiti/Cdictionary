#include <stdio.h>

int main() {

  double numberOne;
  double numberTwo;
  char operator;
  double result;

  printf("Enter first number: ");
  scanf("%lf", &numberOne);

  printf("Enter second number: ");
  scanf("%lf", &numberTwo);

  printf("Enter operator: ");
  scanf(" %c", &operator);

  switch (operator) {
  case '+':
    result = numberOne + numberTwo;
    printf("Result of %lf + %lf = %.2lf\n", numberOne, numberTwo, result);
    break;
  case '-':
    result = numberOne - numberTwo;
    printf("Result of %lf - %lf = %.2lf\n", numberOne, numberTwo, result);
    break;
  case '*':
    result = numberOne * numberTwo;
    printf("Result of %lf * %lf = %.2lf\n", numberOne, numberTwo, result);
    break;
  case '/':
    if (numberTwo != 0) {
      result = numberOne * numberTwo;
      printf("Result of %lf * %lf = %.2lf\n", numberOne, numberTwo, result);
      break;
    } else {
      printf("not divisible \n");
    }
    default:
        printf("invalid operator entered \n");
  }

  return 0;
}
