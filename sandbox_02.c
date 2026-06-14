
#include <stdio.h>
#include <string.h>

int main() {

  char name[50];
  int len;


  do {
    printf("Enter a name: ");
    // scanf("%s", name);
    // John snow + \0
    fgets(name, sizeof(name), stdin);
    // overwrite the \0 to \n
    name[strcspn(name, "\n")] = '\0';

    len = strlen(name);
    if (len > 8) {
      printf("Lenght must not be greater than 8\n");
      // return 1;
    }

  } while (len > 8);

  printf("Lenght is: %d\n", len);
  printf("Name is: %s\n", name);

  return 0;
}
