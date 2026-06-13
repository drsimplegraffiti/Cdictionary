#include <stdio.h>

// str[] decays to a pointer to the first character when passed in
// we walk through each character by index until we hit the null terminator \0
// which marks the end of the string
int stringLength(char str[]) {
  int length = 0;

  // str[length] is equivalent to *(str + length)
  // we keep incrementing length (the offset) until we reach \0
  while (str[length] != '\0') {
    length++;
  }

  // length now equals the number of characters before \0
  return length;
}

int main() {
  // compiler automatically appends \0 at the end: null character
  // ['J','a','m','e','s',' ','L','E','E','\0']
  char text[] = "James LEE";

  printf("String length of text is: %d\n", stringLength(text));
  return 0;
}
