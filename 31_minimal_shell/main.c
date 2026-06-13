#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char command[100];

  while (1) {                               // infinite loop = shell stays alive
    printf("myshell> ");                    // print prompt
    fgets(command, sizeof(command), stdin); // read user input
    command[strcspn(command, "\n")] = 0;    // strip trailing \n

    // if (strcmp(command, "exit") == 0) {        // if user types "exit"
    //     break;                                 // kill the loop = exit shell
    // }

    if (strcmp(command, "exit") == 0) {
      break;
    } else if (strcmp(command, "ls") == 0) {
      system("ls");

    } else if (strcmp(command, "help") == 0) {
      printf("Available commands:\n");
      printf("  ls    - list files\n");
      printf("  pwd   - print working directory\n");
      printf("  clear - clear screen\n");
      printf("  exit  - quit shell\n");
    } else if (strcmp(command, "pwd") == 0) {
      system("pwd");
    } else if (strcmp(command, "clear") == 0) {
      system("clear");
    } else {
      // unknown command
      printf("myshell: command not found: %s\n", command);
    }

    // system(command); // run the command via OS
  }

  return 0;
}
