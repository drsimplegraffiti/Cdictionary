
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main() {

  char name[90];
  char email[90];

  // fgets(char *restrict s, int n, FILE *restrict stream);
  //  restrict is a keyword telling the compiler that the  pointers don't
  //  overlap in memory

  // char *s : buffer to write into
  // int n         // max bytes to read - prevents buffer overflow
  // FILE *stream  // where to read from - stdin, or a file pointer
  // fgets(name, sizeof(name), stdin);
  //          ^^^^^^^^^^^^  reads max 49 chars + \0

  // validate name
  do {
    // validation
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // strip newline

    if (name[0] == '\0') {
      printf("name cannot be empty, try again\n");
    }

  } while (name[0] == '\0');

  // validate email independently
  do {
    printf("Enter email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';
    if (email[0] == '\0') {
      printf("email cannot be empty, try again\n");
    }
  } while (email[0] == '\0');

  printf("name: %s\nemail: %s\n", name, email);

  return 0;
}
