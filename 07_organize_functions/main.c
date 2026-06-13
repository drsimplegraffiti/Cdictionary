#include "math_util.h"
#include <stdio.h>

// function declaration/ prototype .h
// function definition
int main() {

  int addRes = add(2, 4);
  double doubleRes = addTimes(2, 4);

  printf("addRes = %d, and doubleRes = %.2lf\n", addRes, doubleRes);

  return 0;
}


// gcc main.c math_util.c -o main && ./main
