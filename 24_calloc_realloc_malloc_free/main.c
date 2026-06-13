#include <stdio.h>
#include <stdlib.h>

int main() {
  int size = 5;

  // 1. malloc - allocates raw uninitialized memory (contains garbage values)
  int *arr1 = (int *)malloc(size * sizeof(int));
  if (arr1 == NULL) {
    printf("malloc failed\n");
    return 1;
  }
  printf("malloc (garbage values): ");
  for (int i = 0; i < size; i++)
    printf("%d ", arr1[i]);
  printf("\n");

  // 2. calloc - allocates memory AND zeroes it out
  // calloc(number of elements, size of each element)
  int *arr2 = (int *)calloc(size, sizeof(int));
  if (arr2 == NULL) {
    printf("calloc failed\n");
    return 1;
  }
  printf("calloc (zeroed values): ");
  for (int i = 0; i < size; i++)
    printf("%d ", arr2[i]);
  printf("\n");

  // 3. realloc - resize previously allocated memory
  // old data is preserved, new slots are uninitialized
  size = 10;
  arr2 = (int *)realloc(arr2, size * sizeof(int));
  if (arr2 == NULL) {
    printf("realloc failed\n");
    return 1;
  }
  printf("realloc (resized to 10): ");
  for (int i = 0; i < size; i++)
    printf("%d ", arr2[i]);
  printf("\n");

  // 4. free - release heap memory back to the OS
  free(arr1);
  free(arr2);

  // 5. set to NULL after free - dangling pointer protection
  // after free, pointer still holds old address (dangling pointer)
  // accessing it is undefined behavior
  arr1 = NULL;
  arr2 = NULL;

  // now safe to check before using
  if (arr1 == NULL) {
    printf("arr1 is NULL, safe - wont access freed memory\n");
  }

  return 0;
}
