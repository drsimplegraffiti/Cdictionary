
int sumArray(int arr[], int size) {

  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum;
}

int main() {

  // Note array decays to pointer: means when you pass an array to a function C
  // automatically converts it to a pointer to its first element.

  int numbers[] = {1, 2, 3, 4, 5};
  // in memory
  // address:  0x100  0x104  0x108  0x10C  0x110
  // value:      1      2      3      4      5

  int size = sizeof(numbers) / sizeof(numbers[0]);

  // When you write:
  // sumArray(numbers, size);
  // C silently turns it into :
  // sumArray(&numbers[0], size); pointer to first element
  sumArray(numbers, size);

  // So inside sumArray, arr is just a pointer — not a copy of the array. This
  // is why these three signatures are identical:
  // int sumArray(int arr[], int size)   // looks like array
  // int sumArray(int *arr, int size)    // pointer, same thing
  // int sumArray(int arr[5], int size)  // size is ignored, same thing

  return 0;
}
