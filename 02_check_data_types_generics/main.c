#include <stdbool.h>
#include <stdio.h>

// the \ at the end of each line is a continuation character in C macro
// if you remove it, the compiler will think the macro as ended on the first
// line
// You can also wirte it as : #define TYPE_NAME(x) _Generic((x), bool: "bool",
// int: "int", long: "long", float: "float", double: "double", char *: "char *",
// const char *: "const char *", default: "unknown")
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

int main(int argc, char const *argv[]) {

  int number = 10;
  printf("type of number is %s\n", TYPE_NAME(number));
  printf("the size of number is :%lu (bytes)\n", sizeof(number));

  bool isValid = true;
  printf("type of isValid is %s\n", TYPE_NAME(isValid));

  long financeBalance = 12999999L;
  printf("type of financeBalance is %s\n", TYPE_NAME(financeBalance));
  return 0;
}
