#include <stdio.h>
#include <string.h>

// union shares memory among its members
union Data {
  int i;
  float f;
  char str[20];
};

int main() {
  union Data d1;

  // proof they share the same memory address
  printf("address of d1.i:   %p\n", (void *)&d1.i);
  printf("address of d1.f:   %p\n", (void *)&d1.f);
  printf("address of d1.str: %p\n", (void *)&d1.str);

  // proof only one value is valid at a time
  d1.i = 10;
  printf("\nset i = 10\n");
  printf("i:   %d\n", d1.i);
  printf("f:   %f\n", d1.f);   // garbage
  printf("str: %s\n", d1.str); // garbage

  d1.f = 12.3f;
  printf("\nset f = 12.3\n");
  printf("i:   %d\n", d1.i); // garbage
  printf("f:   %.2f\n", d1.f);
  printf("str: %s\n", d1.str); // garbage

  // size proof: union size = size of largest member (str = 20 bytes)
  printf("\nsizeof union:  %zu\n", sizeof(d1));
  printf("sizeof int:    %zu\n", sizeof(d1.i));
  printf("sizeof float:  %zu\n", sizeof(d1.f));
  printf("sizeof str:    %zu\n", sizeof(d1.str));

  return 0;
}
