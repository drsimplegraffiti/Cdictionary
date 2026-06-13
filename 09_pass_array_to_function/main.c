#include <stdio.h>
int sumArray(int arr[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }

  return sum;
}

int main() {
  int numbers[] = {1, 2, 3, 4, 5};
  printf("Size of numbers[]: %zu\n", sizeof(numbers)); // 20 (5 * 4 bytes) 
  int size =
      sizeof(numbers) / sizeof(numbers[0]); // or sizeof(numbers) / sizeof(int)
  printf("size/no of elements in this array is: %d\n", size);

  // int result = sumArray(int *arr, int size)
  int result = sumArray(numbers, size);
  printf("Sum array elements: %d\n", result);

  return 0;
}
