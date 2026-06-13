#include <stdio.h>

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
int main() {
  int x = 5;
  int y = 9;

  printf("Before swap x is %d, y is %d\n", x, y);

  swap(&x, &y);

  printf("After swap x is %d, y is %d\n", x, y);
  return 0;
}
