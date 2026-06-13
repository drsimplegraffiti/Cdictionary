#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TYPE_NAME(x)                                                           \
  _Generic((x),                                                                \
      bool: "bool",                                                            \
      int: "int",                                                              \
      long: "long",                                                            \
      float: "float",                                                          \
      double: "double",                                                        \
      char *: "char *",                                                        \
      const char *: "const char *",                                            \
      default: "unknown")

//Check types

int main(int argc, char const *argv[]) {
  printf("ARG count is: %d\n", argc);

  if (argc < 1) {
    printf("please enter format like [./main something]\n");
    return -1;
  }

  // converts number string to int
  printf("number type before conversion is: %s\n", TYPE_NAME(argv[1]));
  int number = atoi(argv[1]);
  printf("number type before conversion is: %s\n", TYPE_NAME(number));

  if (number < 3) {
    printf("Please type a bigger number!! \n");
    return -1;
  }

  printf("Yay!!!!\n");

  return 0;
}
