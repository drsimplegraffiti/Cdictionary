#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// A buffer is just a chunk of memory set aside to temporarily hold data.A
// buffer is just a chunk of memory set aside to temporarily hold data.
//  char *buf is a pointer to that chunk:

// char name[90];
// //   ^^^^ this IS the buffer - 90 bytes of memory reserved
// //        to hold characters temporarily
//
// char *buf = name;
// //   ^^^^ just a pointer pointing to that same memory

// char name[90];
//
// fgets(name, sizeof(name), stdin); // keyboard → buffer
// printf("%s", name);               // buffer → screen
// fgets(name, sizeof(name), stdin); // new input overwrites buffer

void input_required(const char *label, char *buf, int size) {
  do {
    printf("%s: ", label);
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0'; // strips space

    if (buf[0] == '\0') {
      printf("%s cannot be empty, try again\n", label);
    }


  } while (buf[0] == '\0');
}

int main() {
  char name[90];
  char email[90];

  input_required("Enter name", name, sizeof(name));
  input_required("Enter email", email, sizeof(email));

  printf("name: %s\nemail: %s\n", name, email);
  return 0;
}
