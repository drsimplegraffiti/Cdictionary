// A double pointer is a pointer to a pointer — it stores the address of another
// pointer.

#include <stdio.h>
// int main() {
int main(int argc, char **argv) {
  //                       ^^^^ array of strings
  //                            argv[0] = program name
  //                            argv[1] = first argument
  int x = 10;
  int *ptr = &x;     // ptr stores address of x
  int **dptr = &ptr; // dptr stores address of ptr

  printf("%d\n", x);      // 10  - direct
  printf("%d\n", *ptr);   // 10  - one dereference
  printf("%d\n", **dptr); // 10  - two dereferences
  printf("%p\n", *dptr);  // 0x100 - address of x

  char *names[] = {"James", "Leon", "Mike"};
  char **ptrr = names; // pointer to first string pointer

  for (int i = 0; i < 3; i++) {
    printf("%s\n", ptrr[i]); // or *(ptr + i)
  }
}
