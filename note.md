squirrelly braces not square brackets

### Character pointer
```c
#include <stdio.h>
#include <string.h>

int main() {
  const char *name = "jude"; // char * ("char pointer") is the string type
  int len = strlen(name);
  printf("%d\n", len);

```

### check c version
Method 1:
```c
#include <stdio.h>

int main() {
#if defined(__STDC_VERSION__)
    if (__STDC_VERSION__ == 202311L)      printf("C Version: C23\n");
    else if (__STDC_VERSION__ == 201710L) printf("C Version: C17 (C18)\n");
    else if (__STDC_VERSION__ == 201112L) printf("C Version: C11\n");
    else if (__STDC_VERSION__ == 199901L) printf("C Version: C99\n");
    else                                  printf("C Version: Pre-C99 standard (%ld)\n", __STDC_VERSION__);
#else
    printf("C Version: C89 / C90\n");
#endif
    return 0;
}
```

Method 2:
```c
gcc -dM -E - < /dev/null | grep __STDC_VERSION__

// -dM — instead of compiling, dump all macro definitions (#defines), including built-in predefined ones.
// -E — stop after the preprocessing stage (don't compile/assemble/link), just output preprocessed result.
// - — read input from stdin instead of a file.
// < /dev/null — feed empty input (since you only care about predefined macros, not any actual source code).
// | grep __STDC_VERSION__ — filter the huge macro dump down to just the one line showing the C standard version.
```

### Boolean
```c
// #include <stdbool.h>  // not needed in C23

// the numeric value of true == 1



#include <stdbool.h>
#include <stdio.h>

int main() {

  int is_true = true;
  printf("%d\n", is_true); // prints 1
  printf("%b\n", is_true); // prints 1
  printf("%d\n", 1 == is_true);
}

```


### Post and Pre increment
```c
#include <stdbool.h>
#include <stdio.h>

int main() {
  int i, j;
  i = 10;
  j = 5 + ++i; // Increment i first, _then_ compute 5 + i

  int k, h;
  k = 10;
  h = 5 + k++;              // Use k (10) first, _then_ increment k

  printf("%d, %d\n", i, j); // Prints 11, 16
  printf("%d, %d\n", k, h); // Prints 11, 15
}
```



### comma operator in the for loop's initialization and increment sections.
```c

#include <stdbool.h>
#include <stdio.h>

int main() {
  int i, j;
  for (i = 0, j = 10; i < 100; i++, j++)
    printf("%d, %d\n", i, j);
}
```

#### sizeof, tells size in bytes
```c
#include <stdbool.h>
#include <stdio.h>

int main() {
  printf("size of int: %zu bytes\n", sizeof(int));

  // special type to return the data type of sizeof
  int number = 90;
  size_t number_size = sizeof(number); // pronounced “size tee
  printf("size of number_size: %zu bytes\n", number_size);

  // size_t is an unsigned integer that can hold the size in bytes
  // Remember:
  int a = 999;

  // %zu is the format specifier for type size_t
  // If your compiler balks at the "z" part, leave it off

  printf("%zu\n", sizeof a);      // Prints 4 on my system
  printf("%zu\n", sizeof(2 + 7)); // Prints 4 on my system
  printf("%zu\n", sizeof 3.14);   // Prints 8 on my system
  // it’s the size in bytes of the type of the expression, not the size of the
  // expression itself. That’s why the size of 2+7 is the same as the size of
  // a—they’re both type int.
  return 0;
}
```


### Forever loop
```c
for(;;) {  // "forever"
    printf("I will print this again and again and again\n" );
    printf("for all eternity until the heat-death of the universe.\n");

    printf("Or until you hit CTRL-C.\n");
}
```
