
#include <stdio.h>

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void reverseArray(int arr[], int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


int main() {

  int numbers[] = {1, 4, 90, 45, 34};
  int size = sizeof(numbers) / sizeof(int);

  // pass array to function
  bubbleSort(numbers, size);

  printf("Sorted array: ");
  for (int i = 0; i < size; ++i) {
    printf("%d ", numbers[i]);
  }

  printf("\n");

  reverseArray(numbers, size);
  printf("Reversed array: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", numbers[i]);
  }

  
  printf("\n");
  return 0;
}
