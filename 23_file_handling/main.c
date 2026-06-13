#include <stdio.h>

int main() {

  // we need a special data type called FILE
  FILE *filepointer;
  filepointer = fopen("data.txt", "a");
  // filepointer = fopen("data.txt", "w");
  // if file does not exist, mode "w" will
  // create it. if exists, overwites the
  // previous content
  if (filepointer == NULL) {
    printf("Error creating/Opening file: \n");
    return 1;
  }

  // get words from user input
  char text[100];
  printf("Enter your desired words: ");
  fgets(text, sizeof(text), stdin);
  // write to a file using fprintf, just like printf but this writes to a file
  // instead of the console
  fprintf(filepointer, "%s", text);
  fclose(filepointer); // close before reopening
  printf("File written successfully \n");

  // Read
  filepointer = fopen("data.txt", "r");
  if (filepointer == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  // fgets(text, sizeof(text), filepointer); // reads only one line.
  // printf("Message from file is: %s", text);

  // to read all lines
  while (fgets(text, sizeof(text), filepointer) != NULL) {
    printf("%s", text);
  }

  fclose(filepointer);

  return 0;
}
