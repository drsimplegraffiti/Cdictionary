#include <stdio.h>

int main() {

  // pointers is a variable that stores the memory address of another variable
  int number = 13;
  int *ptr_number = &number;

  printf("Actual number: %d\n", number);
  printf("Memory address of number: %p\n", &number);
  printf("Deferenced (Value at pointer): %d\n", *ptr_number);
  printf("Pointer stores: %p\n", ptr_number);

  // pointer arithmetic: pointers can be decremented or incremented
  // i.e moved through memory location
  int arr[] = {13, 24, 399, 48, 5};
  int *ptr = arr; // points to the first element of the array

  printf("first element: %d\n", *ptr); // gives 13
  ptr++;
  printf("second element: %d\n", *ptr); // gives 24

  // pointer to array
  int num[] = {1, 3, 4, 5, 6, 7};
  int size = sizeof(num) / sizeof(int);
  int *ptr_num = num;
  printf("Pointer stores first elem: %d\n", *ptr_num);

  for (int i = 0; i < size; i++) {
    printf("Element of %d: %d\n", i, *(ptr_num + i)); // same as incrementing it
                                                      // here too
  }

  return 0;
}
