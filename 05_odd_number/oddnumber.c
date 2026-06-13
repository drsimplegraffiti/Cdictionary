#include <stdio.h>

int main() {

  printf("Enter number to know if it is prime: ");
  int firstNumber;
  scanf("%d", &firstNumber);

  if (firstNumber < 2) {
    printf("Number must start from 2 above \n");
    return -1;
  }
  if (firstNumber % 2 == 0) {
    printf("this is even number\n");
  } else {
    printf("this is odd number\n");
  }
  return 0;
}
