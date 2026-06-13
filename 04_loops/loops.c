#include <stdio.h>
#include <stdlib.h>

int main() {

  printf("while loops: \n");
  int age = 10;
  while (age < 13) { // 10 < 18 == true, run
    printf("age is now %d\n", age);
    age++;
  }

  int x = 0;
  do { // will run at least once

    printf("x is now: %d\n", x);
    x++;
  } while (x < 5);


  return 0;
}
