#include <stdio.h>

void greet(const char *name, int age, char *buffer) {
  // sprintf(char *restrict s, const char *restrict format, ...)
  sprintf(buffer, "my name is %s and i am %d years old", name, age);

  // safer
  // snprintf(buffer, 100, "my name is %s and age is %d", name, age);
}

int main() {
  char output[100];
  // greet(const char *name, int age, char *buffer)
  greet("james", 4, output);

  printf("%s\n", output);

  return 0;
}



