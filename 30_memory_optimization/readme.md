
## Memory Optimization Techniques in C

### 1. Use the Right Data Types
Don't use a `double` when an `int` is enough. Smaller data types = less memory.
```c
int x;    // 4 bytes - use this
double x; // 8 bytes - only when you need decimals
```

### 2. Avoid Unnecessary Memory Allocation
Allocate only when needed, free as soon as you're done.
```c
int *arr = malloc(size * sizeof(int));
// use arr...
free(arr);      // free immediately when done
arr = NULL;     // prevent dangling pointer
```

### 3. Use Arrays Instead of Linked Lists When Possible
Arrays are stored contiguously in memory — CPU cache loves them (memory locality).
Linked lists scatter nodes across the heap — more cache misses, slower.
```c
int arr[100];        // contiguous, cache friendly
Node *list = ...;    // scattered, cache unfriendly
```

### 4. Use Static Variables When Applicable
Static variables are allocated once for the program's lifetime — no repeated malloc/free.
```c
void counter() {
    static int count = 0;  // allocated once, persists between calls
    count++;
}
```

### 5. Use realloc() Wisely
Don't over-allocate upfront. Grow memory dynamically as needed.
```c
// instead of guessing a large size upfront:
int *arr = malloc(10 * sizeof(int));
// when you need more:
arr = realloc(arr, 20 * sizeof(int));
```

### 6. Prevent Memory Leaks + Dangling Pointers
A memory leak = allocating memory and never freeing it.
Over time it consumes all available memory, slowing or crashing the program.

```c
// memory leak - never freed
int *p = malloc(100);
p = malloc(200);  // original 100 bytes lost forever

// dangling pointer - accessing freed memory
free(p);
*p = 5;  // undefined behavior

// correct pattern
free(p);
p = NULL;          // always NULL after free
if (p != NULL) {}  // safe to check before use
```

