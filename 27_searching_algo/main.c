#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. LINEAR SEARCH - O(n)
// works on unsorted arrays
// ============================================

int linearSearch(int arr[], int size, int target) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == target)
      return i; // return index
  }
  return -1; // not found
}

// ============================================
// 2. BINARY SEARCH (iterative) - O(log n)
// array MUST be sorted
// ============================================

int binarySearch(int arr[], int size, int target) {
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2; // avoids overflow vs (left+right)/2

    if (arr[mid] == target)
      return mid;
    else if (arr[mid] < target)
      left = mid + 1; // target is in right half
    else
      right = mid - 1; // target is in left half
  }
  return -1;
}

// ============================================
// 3. BINARY SEARCH (recursive) - O(log n)
// ============================================

int binarySearchRecursive(int arr[], int left, int right, int target) {
  if (left > right)
    return -1; // base case: not found

  int mid = left + (right - left) / 2;

  if (arr[mid] == target)
    return mid;
  else if (arr[mid] < target)
    return binarySearchRecursive(arr, mid + 1, right, target);
  else
    return binarySearchRecursive(arr, left, mid - 1, target);
}

// ============================================
// 4. JUMP SEARCH - O(√n)
// sorted array, jumps in blocks then linear
// ============================================

int jumpSearch(int arr[], int size, int target) {
  int step = (int)sqrt(size); // block size
  int prev = 0;

  // jump until block containing target
  while (arr[step < size ? step : size - 1] < target) {
    prev = step;
    step += (int)sqrt(size);
    if (prev >= size)
      return -1;
  }

  // linear search within block
  while (arr[prev] < target) {
    prev++;
    if (prev == (step < size ? step : size))
      return -1;
  }

  if (arr[prev] == target)
    return prev;
  return -1;
}

// ============================================
// 5. INTERPOLATION SEARCH - O(log log n) avg
// sorted + uniformly distributed data
// estimates position like a phonebook search
// ============================================

int interpolationSearch(int arr[], int size, int target) {
  int left = 0;
  int right = size - 1;

  while (left <= right && target >= arr[left] && target <= arr[right]) {
    if (left == right) {
      if (arr[left] == target)
        return left;
      return -1;
    }

    // estimate position based on value distribution
    int pos = left + ((double)(right - left) / (arr[right] - arr[left])) *
                         (target - arr[left]);

    if (arr[pos] == target)
      return pos;
    else if (arr[pos] < target)
      left = pos + 1;
    else
      right = pos - 1;
  }
  return -1;
}

// ============================================
// 6. EXPONENTIAL SEARCH - O(log n)
// useful when array size is unknown
// finds range then does binary search
// ============================================

int exponentialSearch(int arr[], int size, int target) {
  if (arr[0] == target)
    return 0;

  // find range by doubling index
  int i = 1;
  while (i < size && arr[i] <= target)
    i *= 2;

  // binary search in found range
  return binarySearchRecursive(arr, i / 2, (i < size ? i : size - 1), target);
}

// ============================================
// helper
// ============================================

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void printResult(const char *algo, int index, int target) {
  if (index != -1)
    printf("%-25s found %d at index %d\n", algo, target, index);
  else
    printf("%-25s %d not found\n", algo, target);
}

// ============================================
// MAIN
// ============================================

int main() {
  // unsorted - only for linear search
  int unsorted[] = {64, 25, 12, 22, 11};
  int usize = sizeof(unsorted) / sizeof(int);

  // sorted - required for all others
  int sorted[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
  int ssize = sizeof(sorted) / sizeof(int);

  int target = 23;

  printf("=== UNSORTED ARRAY ===\n");
  printArray(unsorted, usize);

  printf("\n=== SORTED ARRAY ===\n");
  printArray(sorted, ssize);

  printf("\nsearching for: %d\n\n", target);

  printResult("linear search:", linearSearch(unsorted, usize, target), target);
  printResult("binary (iterative):", binarySearch(sorted, ssize, target),
              target);
  printResult("binary (recursive):",
              binarySearchRecursive(sorted, 0, ssize - 1, target), target);
  printResult("jump search:", jumpSearch(sorted, ssize, target), target);
  printResult("interpolation search:",
              interpolationSearch(sorted, ssize, target), target);
  printResult("exponential search:", exponentialSearch(sorted, ssize, target),
              target);

  // test not found
  printf("\nsearching for: 99\n\n");
  printResult("binary (iterative):", binarySearch(sorted, ssize, 99), 99);
  printResult("linear search:", linearSearch(sorted, ssize, 99), 99);

  return 0;
}

// Run: gcc main.c -o main -lm && ./main
// Summary:
// === UNSORTED ARRAY ===
// 64 25 12 22 11
//
// === SORTED ARRAY ===
// 2 5 8 12 16 23 38 45 56 72 91
//
// searching for: 23
//
// linear search:            found 23 at index 5
// binary (iterative):       found 23 at index 5
// binary (recursive):       found 23 at index 5
// jump search:              found 23 at index 5
// interpolation search:     found 23 at index 5
// exponential search:       found 23 at index 5
//
// searching for: 99
//
// binary (iterative):       99 not found
// linear search:            99 not found
