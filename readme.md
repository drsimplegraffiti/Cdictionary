Dry run first to see what it would delete before actually deleting:
```bash
find . -maxdepth 1 -type f ! -name "*.*"
```

delete
```bash
find . -maxdepth 1 -type f ! -name "*.*" -delete
```


### Resources
1. man pages — fastest, right in your terminal
```bash
man fgets        # full docs for fgets
man strchr       # any function
man 3 printf     # section 3 = C standard library functions
```
2. cppreference.com — best online reference
https://en.cppreference.com/w/c
Has every C function with signature, description, parameters, return value, and examples. Just search fgets in the search bar.

3. man pages inside Neovim directly
:Man fgets
:Man 3 fgets
:Man 3 printf

4. GNU C Library docs
https://www.gnu.org/software/libc/manual/html_node/
More detailed than man pages, explains behaviour edge cases.

find /usr/include -name "unistd.h"
:e /usr/include/unistd.h

5. :Man intro
6. For keywords
https://cppreference.com/c/language/extern

7. tldr pages — community examples, often clearer than man pages
    tldr fgets
(install via: sudo apt install tldr)

    8. info pages — more detailed than man, hyperlinked sections
    info libc
    info "(libc) Line Input"

    9. clangd / LSP in Neovim — hover and go-to-definition
    - Hover over a function (e.g. fgets) shows its signature/docs
    - gd jumps to the header declaration in /usr/include

    10. Read the actual glibc source
    https://sourceware.org/git/?p=glibc.git;a=tree
    or clone it locally to see real implementations

    11. cdecl.org — decode confusing declarations
    https://cdecl.org
    e.g. paste "char *(*foo)(int)" and it explains it in English

    12. Compiler Explorer (godbolt.org) — see what a function compiles to
    https://godbolt.org
    Great for understanding low-level behavior of stdlib calls

    13. Books for deep examples
    - "The C Programming Language" (K&R) — classic, terse, example-driven
    - "Modern C" by Jens Gustedt (free PDF) — more modern explanations
    - "Beej's Guide to C" — free, very example-heavy
    https://beej.us/guide/bgc/
https://beej.us/guide/bgc/html/split/

14. GDB to step through stdlib calls live
gdb ./a.out
break fgets
run
(lets you inspect what's actually happening at runtime)


//# is called Octothorpe

NOTE:
You can force GCC to use one of these standards with the -std= command line argument. If you want it to be picky about the standard, add -pedantic.
gcc -std=c11 -pedantic foo.c
gcc -Wall -Wextra -std=c23 -pedantic foo.c
or
gcc -Wall -Wextra -std=c2x -pedantic sandbox_02.c -o main                                                                                         system

### void functions
Means functions accepts no argument
```c
int main(void){
    return 0;
}
```


### Pass by reference vs Pass by Value
```c

#include <stdio.h>

void incrementPassByReference(int *a) {
    (*a)++; // Dereference first, then increment the VALUE
}

void incrementPassByValue(int a) {
    a++;
    printf("Inside incrementPassByValue, a is %d\n", a);
}

int main(void) {
    int i = 10;
    int *ptr = &i;

    incrementPassByReference(ptr);
    printf("After incrementPassByReference: i == %d\n", *ptr); // 11
    printf("After incrementPassByReference: i == %d\n", i);    // 11

    incrementPassByValue(i);
    printf("After incrementPassByValue: i == %d\n", i); // still 11, unchanged

    return 0;
}
```


### Pointer
```c

#include <stdio.h>

void increment(int *a) {
    *a = *a + 1;
}

int main(void) {
    int a = 9;
    printf("real value: %d\n", a);

    // %p expects a void * argument — that's what the C standard specifies.
    // (void *)(&a) - keeps compiler from throwing a warning.
    printf("memory address: %p\n", (void *)(&a)); // correct, explicit cast to void*
    printf("memory address: %p\n", &a);           // technically wrong type (int*)

    char b = 'A'; // this is a pointer to a char
    printf("Memory address of b is %p\n", (void *)(&b));
    printf("Dereference of char b is %c\n", *(char *)(&b)); // cast back to char* before dereferencing

    int i;
    int *p; // this is NOT a dereference--this is a type "int*"

    p = &i; // p now points to i, p holds address of i

    i = 10;                 // i is now 10
    printf("i is %d\n", i); // prints "10"
    *p = 20;                // the thing p points to (namely i!) is now 20!!

    printf("i is %d\n", i);  // prints "20"
    printf("i is %d\n", *p); // "20"! dereference-p is the same as i!

    int az = 9;
    printf("Before increment, az is %d\n", az);
    increment(&az);
    printf("After increment, az is %d\n", az);

    // declaring multi pointer, same line
    // int *pt1, *pt2; same as int pt1, *pt2;
    // int *p, q;  // p is a pointer to an int; q is just an int.

    int *pp;

    // Prints size of an 'int'
    printf("%zu\n", sizeof(int));

    // pp is type 'int *', so prints size of 'int*'
    printf("%zu\n", sizeof pp);

    // *pp is type 'int', so prints size of 'int'
    printf("%zu\n", sizeof *pp);


//  TLDR:Distilled pointer dereferencing and sizeof operator mechanicsDistilled pointer dereferencing and sizeof operator mechanicsTLDR:
//
// sizeof(int) → size of an int (usually 4 bytes)
// sizeof p → p is a pointer (int *), so this gives the size of a pointer (usually 8 bytes on 64-bit systems) — same for any pointer type, int*, char*, double*, etc.
// sizeof *p → *p dereferences p, givin

    // NULL pointer: pointer that does not point to anything
    int *ptr_alpha = NULL;
    if (ptr_alpha == NULL) {
        printf("Error: pointer to NULL");
        return 1;
    }
    *ptr_alpha = 12; // crashes the program, segmentation fault error
}
```

### Arrays 
```c

#include <stdio.h>

#define COUNT 5

// in multi diemensional arrays we dont need a size
void print_2D_array(int a[2][3]) {
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++)
            printf("%d ", a[row][col]);
        printf("\n");
    }
}
// void times2(int *a, int len): most common
// void times3(int a[], int len)
// void times4(int a[5], int len)

void times2(int arr[], int size) { // instead of int arr[], you can also use
                                   // arr* or arr[4]
    for (int i = 0; i < size; i++) {
        printf("when index is %d, %d * 2 is %d\n", i, arr[i], arr[i] * 2);
    }
}

int main(void) {
    printf("%zu\n", sizeof(double[48]));

    // int arr[COUNT] = {1, 2, 3, 4, 5};
    int a[3] = {22, 37, 3490};
    for (int i = 0; i < COUNT; ++i) {
        printf("i is %d and value is %d\n", i, a[i]);
    }

    int row, col;
    int ar[2][5] = {// Initialize a 2D array
                    {0, 1, 2, 3, 4},
                    {5, 6, 7, 8, 9}};

    for (row = 0; row < 2; row++) {
        for (col = 0; col < 5; col++) {
            printf("(%d,%d) = %d\n", row, col, ar[row][col]);
        }
    }

    printf("====================\n");
    // initialize with specific index
    int arx[3][3] = {[0][0] = 1, [0][1] = 2, [0][2] = 3};

    for (row = 0; row < 2; row++) {
        for (col = 0; col < 5; col++) {
            printf("(%d,%d) = %d\n", row, col, arx[row][col]);
        }
    }

    // NOTE: Arrays are pointers
    // Generally speaking, when a C programmer talks about a pointer to an array,
    // they’re talking about a pointer to the first element of the array

    // pointer to the first element of the array
    int b[4] = {189, 2, 3, 4};
    int *p;

    p = &b[0];          // p points to the first element of the array
    printf("%d\n", *p); // dereferenced

    // same as
    p = b;
    printf("%d\n", *p); // dereferenced

    int x[4] = {3, 2, 1, 0};
    int size = sizeof(x) / sizeof(int);
    times2(x, size);

    int xx[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};

    print_2D_array(xx);
}
```


### Strings
```c
#include <stdio.h>
#include <string.h>

int my_strlen(char *s) {

    int count = 0;
    while (s[count] != '\0') {
        count++;
    }
    return count;
}

int main(void) {

    // pointer to a char
    // the string literal itself has type char[14] (array of char, including the
    // null terminator) but it decays to a pointer to its first element when
    // assigned to s. So s doesn't "contain" the string — it points to where the
    // string lives in memory.
    char *s = "Hello, world!"; // Actually "Hello, world!\0" behind the scenes
    printf("string is %s\n", s);
    // s[0] = 'Y'; // segment fault. you can index a char pointer like this

    // but can work like this
    for (int i = 0; i < 14; i++)
        printf("%c", s[i]);
    printf("\n");

    // if you need a mutable copy use: char s[]
    char t[] = "Hello, world!";
    t[0] = 'i';
    printf("string is %s\n", t);

    // char *s = "..." → s is a pointer to a string literal stored in read-only
    // memory. You can reassign s to point elsewhere, but you cannot modify the
    // characters (s[0] = 'h' is undefined behavior).

    // char t[] = "..." → t is an
    //  array, and the string literal is copied into it on the stack (writable
    //  memory). You can modify characters (t[0] = 'h' is fine), but t itself is
    //  fixed-size and can't be reassigned to point elsewhere.
    //
    //  Quick way to remember: *s = pointer to read-only text, t[] = your own
    //  writable copy.

    int res = my_strlen("james");
    printf("my string len : %d\n", res);

    char ss[] = "Hello, world!";
    char tt[100]; // big enough to hold the copy

    //     dest, src
    strcpy(tt, ss); // copy s into t

    tt[0] = 'z'; // modify t only

    printf("%s\n", ss); // "Hello, world!" (unchanged)
    printf("%s\n", tt); // "zello, world!" (modified)
}
```

### Str copy
```c
#include <stdio.h>
#include <string.h>

int main(void) {

    char name[10] = "jude";
    char name2[50];

    strcpy(name2, name);

    name2[0] = 'B';

    printf("%s\n", name2);
}
```


### Struct
```c
#include <stdio.h>
#include <string.h>

struct Person {
    char name[10];
    int age;
};

struct Man {
    char *name;
    int age;
};

int main(void) {
    struct Person p1;
    p1.age = 9;
    char *myName = "jude";
    strcpy(p1.name, myName);

    printf("my name is %s\n", p1.name);

    // use directly
    struct Man m1;
    m1.name = "jude okafor";
    m1.age = 90;
    printf("my name is %s, and age is %d\n", m1.name, m1.age);
}
```


### Cat
```c

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// ANSI color codes
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\x1b[0m"
#define WHITE "\x1b[37m"

const char *keywords[] = {
    "auto",      "break",    "case",     "char",   "const",   "continue",
    "default",   "do",       "double",   "else",   "enum",    "extern",
    "float",     "for",      "goto",     "if",     "inline",  "int",
    "long",      "register", "restrict", "return", "short",   "signed",
    "sizeof",    "static",   "struct",   "switch", "typedef", "union",
    "unsigned",  "void",     "volatile", "while",  "_Bool",   "_Complex",
    "_Imaginary", "printf"};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))
int is_keyword(const char *word) {
    for (size_t i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void print_highlighted(const char *str) {

    char buffer[256];
    int idx = 0;

    while (*str) {

        // If current char is part of a word (identifier/keyword)
        if (isalpha((unsigned char)*str) || *str == '_') {
            buffer[idx++] = *str;
        } else {
            // flush buffer before handling symbol
            if (idx > 0) {
                buffer[idx] = '\0';

                if (is_keyword(buffer)) {
                    printf(MAGENTA "%s" RESET, buffer); // keywords = purple
                } else {
                    printf("%s", buffer);
                }

                idx = 0;
            }

            switch (*str) {

            case '=':
                printf(GREEN "=" RESET);
                break;
            case '(':
            case ')':
                printf(YELLOW "%c" RESET, *str);
                break;

            case '.':
                printf(RED "%c" RESET, *str);
                break;

            case '"':
                printf(MAGENTA "%c" RESET, *str);
                break;

            case '/':
                printf(CYAN "%c" RESET, *str);
                break;

            case '{':
            case '}':
                printf(BLUE "%c" RESET, *str);
                break;

            default:
                putchar(*str);
                break;
            }
        }

        str++;
    }

    // flush last word
    if (idx > 0) {
        buffer[idx] = '\0';
        if (is_keyword(buffer)) {
            printf(MAGENTA "%s" RESET, buffer);
        } else {
            printf("%s", buffer);
        }
    }
}

// void print_highlighted(const char *str) {
//
//     while (*str) {
//
//         switch (*str) {
//         case '=':
//             printf(GREEN "=" RESET);
//             break;
//         case '(':
//         case ')':
//             printf(YELLOW "%c" RESET, *str);
//             break;
//
//         case '.':
//             printf(RED "%c" RESET, *str);
//             break;
//
//         case '"':
//             printf(MAGENTA "%c" RESET, *str);
//             break;
//
//         case '/':
//             printf(CYAN "%c" RESET, *str);
//             break;
//
//         case '{':
//         case '}':
//             printf(BLUE "%c" RESET, *str);
//             break;
//
//         default:
//             putchar(*str);
//             break;
//         }
//
//         str++;
//     }
//
//
//
// }

// void print_highlighted(const char *str) {
//
//     while (*str) {
//
//         switch (*str) {
//         case '=':
//             printf(GREEN "=" RESET);
//             break;
//
//         case '(':
//         case ')':
//             printf(YELLOW "%c" RESET, *str);
//             break;
//         case '.':
//             printf(RED "%c" RESET, *str);
//             break;
//         case '"':
//             printf(MAGENTA "%c" RESET, *str);
//             break;
//
//         case '/':
//             printf(CYAN "%c" RESET, *str);
//             break;
//
//         case '{':
//         case '}':
//             printf(BLUE "%c" RESET, *str);
//             break;
//
//             // default:
//             //     putchar(*str);
//
//             // default:
//             //     if (isalpha((unsigned char)*str)) {
//             //         printf(WHITE "%c" RESET, *str);
//             //     } else {
//             //         putchar(*str);
//             //     }
//
//         default:
//             if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
//             {
//                 printf(WHITE "%c" RESET, *str);
//             } else {
//                 putchar(*str);
//             }
//         }
//
//         str++;
//     }
// }

// A minimal "cat" - prints file contents with line numbers
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    char line[1024];
    int linecount = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        linecount++;

        printf("%d: ", linecount);
        print_highlighted(line);

        // if (linecount % 2 == 0) {
        //     printf(GREEN "%d: %s" RESET, linecount, line);
        // } else if (strstr(line, "=")) {
        //     printf("%d: ", linecount);
        //     print_highlighted(line);
        //
        // } else if (strstr(line, ")")) {
        //     printf(RED "%d: %s" RESET, linecount, line);
        // } else {
        //     printf(BLUE "%d: %s" RESET, linecount, line);
        // }
    }

    fclose(fp);
    return 0;
}
```


### fscanf
```c
#include <stdio.h>

int main(void) {
    FILE *fp;
    char name[1024]; // Big enough for any line this program will encounter
    float length;
    int mass;

    fp = fopen("hello.txt", "r");
    if (fp == NULL) {
        printf("file not found\n");
        return 1;
    }

    while (fscanf(fp, "%s %f %d", name, &length, &mass) != EOF)
        printf("%s whale, %d tonnes, %.1f meters\n", name, mass, length);

    fclose(fp);
}
```


### Struct
```c

#include <stdio.h>

typedef struct animal {
    char *name;
    int age;
} animalia;

// anonymous structs
typedef struct {
    char *color;
    int height;
} Person;

int main() {
    // both works
    animalia lion = {"lion", 18};
    struct animal tiger = {"tiger", 18};

    printf("animalia: %s\n", lion.name);
    printf("animal: %s\n", tiger.name);

    Person p1 = {"black", 180};
    printf("person one is: %s\n", p1.color);

    // positional
    Person p2 = {.height = 190, .color = "red"};
    printf("person 2 is: %s and height is %d\n", p2.color, p2.height);

    return 0;
}
```


### Array and pointer
```c
#include <stdio.h>

int main(void)
{
    int a[] = {11, 22, 33, 44, 55};

    int *p = a;  // p points to the first element of a, 11

    // Print all elements of the array a variety of ways:

    for (int i = 0; i < 5; i++)
        printf("%d\n", a[i]);      // Array notation with a

    for (int i = 0; i < 5; i++)
        printf("%d\n", p[i]);      // Array notation with p

    for (int i = 0; i < 5; i++)
        printf("%d\n", *(a + i));  // Pointer notation with a

    for (int i = 0; i < 5; i++)
        printf("%d\n", *(p + i));  // Pointer notation with p

    for (int i = 0; i < 5; i++)
        printf("%d\n", *(p++));    // Moving pointer p
        //printf("%d\n", *(a++));    // Moving array variable a--ERROR!
}
```

#### Arrays and pointer
```c

#include <stdio.h>

// if you have a pointer to a type, adding one to the pointer moves to the next
// item of that type directly after it in memory.

int main() {

    int a[10] = {1, 2, 3, 4, 5};
    // int *p = a;" works just as well
    int *p = &a[0]; // Then let’s get a pointer to the first element in that
                    // array:

    printf("first elem: %d\n", *p);     // Prints 1
    printf("first elem: %d\n", *p + 0); // Prints 1

    printf("second elem: %d\n", *p + 1);   // prints the next element 2
    printf("second elem: %d\n", *(p + 1)); // prints the next element 2

    for (int i = 0; i < 5; i++) {
        printf("%d\n", *(p + i)); // Same as p[i]!
    }

    while (*p != 4) {
        printf("P is currently: %d\n", *p);
        p++;
    }




    return 0;
}
```

### Array pointers and function call
```c
#include <stdio.h>

int my_strlen(char *s) {

    int count = 0;
    while (s[count] != '\0') {
        count++;
    }
    return count;
}

int main(void) {
    char s[] = "Antelopes";
    char *t = "Wombats";

    printf("%d\n", my_strlen(s)); // Works!
    printf("%d\n", my_strlen(t)); // Works, too!
}
```

### Memcpy
memcpy() is a C standard library function used to copy raw bytes from one memory location to another.

Its prototype is:
```bash
void *memcpy(void *dest, const void *src, size_t n);
```
Parameters:

- dest → destination memory address
- src → source memory address
- n → number of bytes to copy

NOTE: though strcpy() is more appropriate for strings
```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Memory layout of s:
    // G o a t s ! \0

    // | Character | Bytes |
    // | --------- | ----- |
    // | G         | 1     |
    // | o         | 1     |
    // | a         | 1     |
    // | t         | 1     |
    // | s         | 1     |
    // | !         | 1     |
    // | \0        | 1     |

    // Total = 7 bytes
    // memcpy(t, s, 7) copies all 7 bytes:

    // Before:
    //
    // s: [G][o][a][t][s][!][\0]
    // t: [?][?][?][?][?][?][?]
    //
    // After:
    //
    // s: [G][o][a][t][s][!][\0]
    // t: [G][o][a][t][s][!][\0]

    char s[] = "Goats!";
    char t[100];

    memcpy(t, s, 7);  // Copy 7 bytes--including the NUL terminator!

    printf("%s\n", t);  // "Goats!"
}
```

### memcpy ints
```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    int a[] = {11, 22, 33};
    int b[3];

    memcpy(b, a, 3 * sizeof(int));  // Copy 3 ints of data

    printf("%d\n", b[1]);  // 22
}
```

# What is a `void *` (void pointer)?

A **void pointer** (`void *`) is a special pointer type in C that can point to **any type of data**.

```c
int x = 42;

void *ptr = &x;
```

Here, `ptr` points to an `int`, but the compiler only knows it's a **generic pointer**.

---

## Why use it?

Because it allows functions to work with different data types.

For example, `memcpy()` is declared as:

```c
void *memcpy(void *dest, const void *src, size_t n);
```

This means you can copy:

```c
int a = 10;
int b;

memcpy(&b, &a, sizeof(int));
```

or

```c
char s[] = "hello";
char t[10];

memcpy(t, s, strlen(s) + 1);
```

The same function works for both because it accepts `void *`.

---

## You cannot dereference a `void *`

This is illegal:

```c
void *ptr = &x;

printf("%d\n", *ptr);   // Error
```

The compiler doesn't know:

- Is it an `int`?
- A `char`?
- A `double`?

So it doesn't know how many bytes to read.

---

## You must cast it first

```c
int x = 42;

void *ptr = &x;

printf("%d\n", *(int *)ptr);
```

Step by step:

```c
(int *)ptr
```

tells the compiler:

> "Treat this address as pointing to an `int`."

Then:

```c
*(int *)ptr
```

reads the integer stored there.

Output:

```text
42
```

---

## Memory example

```c
int x = 42;
void *ptr = &x;
```

```text
Address      Value
0x1000       42

ptr -----> 0x1000
```

`ptr` knows the address:

```text
0x1000
```

but not the type of data at that address.

---

## Pointer arithmetic doesn't work directly

This is illegal:

```c
void *ptr = &x;

ptr++;   // Error in standard C
```

Because the compiler doesn't know how far to move:

- `int *` → move by `sizeof(int)`
- `char *` → move by `sizeof(char)`
- `double *` → move by `sizeof(double)`

A `void *` has no size.

Instead:

```c
char *p = (char *)ptr;
p++;
```

Now the compiler knows to move 1 byte.

---

## Common uses of `void *`

- `malloc()`

```c
int *arr = malloc(10 * sizeof(int));
```

`malloc()` returns a `void *`.

- `memcpy()`
- `memmove()`
- `qsort()`
- Generic data structures (linked lists, stacks, hash tables)

Example:

```c
typedef struct Node {
    void *data;
    struct Node *next;
} Node;
```

Now a node can store an `int`, `char`, `struct`, or anything else.

---

## Simple analogy

Think of a normal pointer as a labeled box:

```c
int *p;
```

The label says:

> "This box contains an integer."

A `void *` is an unlabeled box:

```c
void *p;
```

You know it points somewhere, but before opening it, you must tell the compiler what type of data is inside.

That's why `void *` is often called a **generic pointer**.

### Allocation malloc
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int *p = malloc(sizeof(int));
    if (p == NULL) {
        printf("error allocating\n");
        return 0;
    }

    *p = 12;

    printf("P is now %d\n", *p);
    free(p);
    p = NULL;
    *p = 12; // Undefined Error

    return 0;
}
```

### Allocating and Error Checking at the same time
```c
int *x;

if ((x = malloc(sizeof(int) * 10)) == NULL) {
    printf("Error allocating 10 ints\n");
    // do something here to handle it
}
```

### Allocate dynamic ints
```c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Allocate space for 10 ints
    int *p = malloc(sizeof(int) * 10);

    // Assign them values 0-45:
    for (int i = 0; i < 10; i++)
        p[i] = i * 5;

    // Print all values 0, 5, 10, 15, ..., 40, 45
    for (int i = 0; i < 10; i++)
        printf("%d\n", p[i]);

    // Free the space
    free(p);
}
```

#### Realloc
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Allocate space for 20 floats
    float *p = malloc(sizeof *p * 20);  // sizeof *p same as sizeof(float)

    // Assign them fractional values 0.0-1.0:
    for (int i = 0; i < 20; i++)
        p[i] = i / 20.0;

    // But wait! Let's actually make this an array of 40 elements
    float *new_p = realloc(p, sizeof *p * 40);

    // Check to see if we successfully reallocated
    if (new_p == NULL) {
        printf("Error reallocing\n");
        return 1;
    }

    // If we did, we can just reassign p
    p = new_p;

    // And assign the new elements values in the range 1.0-2.0
    for (int i = 20; i < 40; i++)
        p[i] = 1.0 + (i - 20) / 20.0;

    // Print all values 0.0-2.0 in the 40 elements:
    for (int i = 0; i < 40; i++)
        printf("%f\n", p[i]);

    // Free the space
    free(p);
}
```


### Signed and unsigned 
```c
int a;           // signed
signed int a;    // signed
signed a;        // signed, "shorthand" for "int" or "signed int", rare
unsigned int b;  // unsigned
unsigned c;      // unsigned, shorthand for "unsigned int"


#include <stdio.h>

int main(void) {
    // Type 	        Minimum 	                       Maximum
    // int 	            -9,223,372,036,854,775,808 9,223,372,036,854,775,807
    // unsigned int 	0 18,446,744,073,709,551,615

    // Notice that the largest positive unsigned int is approximately twice as
    // large as the largest positive int. So you can get some flexibility there.

    signed a = 10;
    printf("signed no is %d\n", a);
}
```


### Char is lowkey an int
```c
#include <stdio.h>

int main(void) {

    char c = 'a';
    printf("c is actually an int: %d\n", c); // 97

    char a = 10, b = 20;
    printf("%d\n", a + b); // 30!

    char e = 10;
    char f = 'B'; // ASCII value 66. 
                  // the character constant will be converted to a char whose value is the same as the ASCII value of the character.

    printf("%d\n", e + f); // 76!
}
```

### number variants
```c

| Type                 | Minimum Bytes | Minimum Value        | Maximum Value        |
| -------------------- | ------------- | -------------------- | -------------------- |
| `char`               | 1             | -128 or 0            | 127 or 255           |
| `signed char`        | 1             | -128                 | 127                  |
| `short`              | 2             | -32768               | 32767                |
| `int`                | 2             | -32768               | 32767                |
| `long`               | 4             | -2147483648          | 2147483647           |
| `long long`          | 8             | -9223372036854775808 | 9223372036854775807  |
| `unsigned char`      | 1             | 0                    | 255                  |
| `unsigned short`     | 2             | 0                    | 65535                |
| `unsigned int`       | 2             | 0                    | 65535                |
| `unsigned long`      | 4             | 0                    | 4294967295           |
| `unsigned long long` | 8             | 0                    | 18446744073709551615 |


<limits.h>
| Type                 | Min Macro   | Max Macro    |
| -------------------- | ----------- | ------------ |
| `char`               | `CHAR_MIN`  | `CHAR_MAX`   |
| `signed char`        | `SCHAR_MIN` | `SCHAR_MAX`  |
| `short`              | `SHRT_MIN`  | `SHRT_MAX`   |
| `int`                | `INT_MIN`   | `INT_MAX`    |
| `long`               | `LONG_MIN`  | `LONG_MAX`   |
| `long long`          | `LLONG_MIN` | `LLONG_MAX`  |
| `unsigned char`      | `0`         | `UCHAR_MAX`  |
| `unsigned short`     | `0`         | `USHRT_MAX`  |
| `unsigned int`       | `0`         | `UINT_MAX`   |
| `unsigned long`      | `0`         | `ULONG_MAX`  |
| `unsigned long long` | `0`         | `ULLONG_MAX` |


#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void) {
    printf("int min: %d : int max: %d\n", INT_MIN, INT_MAX);
    printf("char min: %d : char max: %d\n", CHAR_MIN, CHAR_MAX);

    printf("float min: %f : float max: %f\n", FLT_MIN, FLT_MAX);
    printf("float min (FLT_MIN): %e\n", FLT_MIN);
    printf("float max (FLT_MAX): %e\n", FLT_MAX);
    return 0;
}
```

```c
// ===============================
// C NUMBER LITERALS CHEAT SHEET
// ===============================

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    // =========================
    // HEXADECIMAL & OCTAL
    // =========================

    int hex = 0x1A;     // hex = 26
    int oct = 012;      // octal = 10 (NOT 12)

    int bad1 = 00111;   // octal = 73, not 111
    int bad2 = 01111;   // octal interpretation

    printf("hex: %d\n", hex);
    printf("oct: %d\n", oct);

    // =========================
    // BINARY (non-standard GCC/Clang extension)
    // =========================

    int bin = 0b101010; // 42

    printf("bin: %d\n", bin);

    // =========================
    // INTEGER SUFFIXES
    // =========================

    int a = 1234;
    long b = 1234L;
    long long c = 1234LL;

    unsigned int d = 1234U;
    unsigned long e = 1234UL;
    unsigned long long f = 1234ULL;

    printf("a=%d b=%ld c=%lld\n", a, b, c);
    printf("d=%u e=%lu f=%llu\n", d, e, f);

    // =========================
    // UNSUFFIXED RULE (type inference)
    // =========================

    int x = 1234;      // int (usually)
    int y = 0xFF;      // hex constant rule differs internally

    printf("x=%d y=%d\n", x, y);

    // =========================
    // FLOATING POINT LITERALS
    // =========================

    float fx = 3.14f;     // float
    double dx = 3.14;     // double (default)
    long double lx = 3.14L;

    printf("fx=%f dx=%f lx=%Lf\n", fx, dx, lx);

    // =========================
    // SCIENTIFIC NOTATION (E notation)
    // =========================

    double sci = 1.23e3;   // 1230
    double sci2 = 1.23e-3; // 0.00123

    printf("sci=%e sci2=%e\n", sci, sci2);

    // =========================
    // HEX FLOATING POINT
    // =========================

    double hx = 0xa.1p3;   // hex float (base 2 exponent)

    printf("hex float (dec): %f\n", hx);
    printf("hex float (hex): %a\n", hx);

    // =========================
    // LIMIT MACROS
    // =========================

    printf("INT_MIN=%d INT_MAX=%d\n", INT_MIN, INT_MAX);
    printf("CHAR_MIN=%d CHAR_MAX=%d\n", CHAR_MIN, CHAR_MAX);

    printf("FLT_MIN=%e FLT_MAX=%e\n", FLT_MIN, FLT_MAX);

    return 0;
}

```


### Type conversion
Numeric Value to String
```c
#include <stdio.h>

int main(void)
{
    char s[10];
    float f = 3.14159;

    // Convert "f" to string, storing in "s", writing at most 10 characters
    // including the NUL terminator

    snprintf(s, 10, "%f", f);

    printf("String value: %s\n", s);  // String value: 3.141590
}
```

### String to Numeric Value
the atoi (pronounced a-to-i) family and the strtol (stir-to-long) family.
Function 	Description
atoi 	String to int
atof 	String to float
atol 	String to long int
atoll 	String to long long int

```c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *pi = "3.14159";
    float f;

    f = atof(pi);

    printf("%f\n", f);
}
```

Function 	Description
strtol 	String to long int
strtoll 	String to long long int
strtoul 	String to unsigned long int
strtoull 	String to unsigned long long int
strtof 	String to float
strtod 	String to double
strtold 	String to long double

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = "3490";

    // Convert string s, a number in base 10, to an unsigned long int.
    // NULL means we don't care to learn about any error information.

    unsigned long int x = strtoul(s, NULL, 10);

    printf("%lu\n", x);  // 3490
}
```

we feed in a deliberately bad number, and we’ll see how strtol() lets us know
where the first invalid digit is.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = "34x90";  // "x" is not a valid digit in base 10!
    char *badchar;

    // Convert string s, a number in base 10, to an unsigned long int.

    unsigned long int x = strtoul(s, &badchar, 10);

    // It tries to convert as much as possible, so gets this far:

    printf("%lu\n", x);  // 34

    // But we can see the offending bad character because badchar
    // points to it!

    printf("Invalid character: %c\n", *badchar);  // "x"
}
```

But what if nothing goes wrong? In that case, badchar will point to the NUL
terminator at the end of the string. So we can test for it:
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = "3490";  // "x" is not a valid digit in base 10!
    char *badchar;

    // Convert string s, a number in base 10, to an unsigned long int.

    unsigned long int x = strtoul(s, &badchar, 10);

    // Check if things went well

    if (*badchar == '\0') {
        printf("Success! %lu\n", x);
    } else  {
        printf("Partial conversion: %lu\n", x);
        printf("Invalid character: %c\n", *badchar);
    }
}
```


### Char conversion
```c

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("%d %d\n", 5, '5'); // '5' is 53

    // 0  1  2  3  4  5  6  7  8  9
    // 48 49 50 51 52 53 54 55 56 57
    char c = '6'; // '6' is value 54

    int x = c; // x has value 54, the code point for '6'

    int y = c - '0'; // y has value 6, just like we want
    printf("y is now: %d\n", y);
    return 0;
}
```


### void conversion
```c

int main(){

    int x = 10;

    void *p = &x;  // &x is type int*, but we store it in a void*

    int *q = p;    // p is void*, but we store it in an int*
    return 0;
}
```


### Type qualifier
These allows us to declare constant values 

```c

#include <stdio.h>

// const in parameter lists for functions
void foo(const int x) {
    printf("x is %d\n", x);
    printf("%d\n", x + 30); // OK, doesn't modify "x"
}

int main() {

    int const x = 90;
    // x = 19; // 1. Cannot assign to variable 'x' with const-qualified type
    // 'const int' [typecheck_assign_const]

    foo(x);

    // int y[] = {10, 20};
    // const int *p = y;

    const int *p; // Can't modify what p points to
    int const
        *ptr; // Can't modify what p points to, just like the previous line

    int u = 10;
    int *const pp = &u;
    *pp = 20; // Set "x" to 20, no problem
    printf("%d\n", *pp);

    // char **p;
    // p++;     // OK!
    // (*p)++;  // OK!
    //
    // char **const p;
    // p++;     // Error!
    // (*p)++;  // OK!
    //
    // char *const *p;
    // p++;     // OK!
    // (*p)++;  // Error!
    //
    // char *const *const p;
    // p++;     // Error!
    // (*p)++;  // Error!
    return 0;
}
```


### restrict in C (TL;DR)

`restrict` is a pointer qualifier that tells the compiler:

> This pointer is the **only way** to access the memory it points to (for its lifetime).

## Why it exists
It removes the compiler’s need to assume pointer aliasing, enabling better optimizations.

## Example
```c
void copy(int *restrict dst, int *restrict src, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

Meaning here
dst and src do NOT overlap
No other pointer will access those memory regions
Without restrict

Compiler must assume:

dst and src may point to the same memory
So it generates more cautious (often slower) code
With restrict
Better optimization (vectorization, fewer memory reloads)
More efficient generated code
```

# C Type Qualifiers & Storage-Class Specifiers (Summary)

## Type Qualifiers

### const
- Makes a variable read-only (cannot be modified after initialization).
- Common in function parameters to guarantee no modification.

#### With pointers
- `const int *p` / `int const *p` → pointer to **read-only data**
- `int *const p` → **constant pointer** (cannot change address)
- `const int *const p` → both pointer and data are read-only

⚠️ If you cast away const and modify anyway → **undefined behavior**

---

### restrict
- Compiler hint: this pointer is the **only way to access the pointed memory**
- No aliasing allowed with other pointers

Benefits:
- Enables aggressive optimizations (vectorization, caching in registers)

⚠️ If violated → **undefined behavior**

---

### volatile
- Value may change outside program control (hardware, interrupts, etc.)
- Forces compiler to always reload from memory

Use cases:
- Hardware registers
- Memory-mapped IO

---

### _Atomic
- Used for thread-safe atomic operations
- Avoids race conditions (covered in atomics/multithreading topics)

---

## Storage-Class Specifiers

### auto
- Default for local variables
- Automatic storage duration (created on scope entry, destroyed on exit)
- Must be initialized manually (otherwise garbage value)

---

### static
#### Block scope
- Variable retains value between function calls
- Initialized once (defaults to 0 if not set)

#### File scope
- Limits visibility to current source file (internal linkage)

---

### extern
- Refers to a variable defined in another file
- Enables cross-file global access

⚠️ If original variable is `static`, it cannot be accessed externally

---

### register
- Hint to store variable in CPU register for speed
- Compiler may ignore it

Restrictions:
- Cannot take address (`&variable`)
- Often obsolete in modern compilers

---

### _Thread_local
- Each thread gets its own independent copy of the variable
- Prevents race conditions on shared state

Alias: `thread_local` (from `<threads.h>`)


# C Type Qualifiers & Storage-Class Specifiers (with Examples)

## const

```c
const int x = 10;
// x = 20; ❌ error

void foo(const int x) {
    printf("%d\n", x); // OK
}
```

### const with pointers
```c
const int *p = &x;   // data is const
p++;                 // OK
// *p = 5;           // ❌ error

int *const q = &x;   // pointer is const
*q = 5;              // OK
// q++;              // ❌ error

const int *const r = &x; // both const
```

### restrict
```c
void copy(int *restrict dst, int *restrict src, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

int main() {
    int a[3] = {1,2,3};
    int b[3];

    copy(b, a, 3);  // OK
    // copy(a, a, 3); ❌ undefined behavior
}
```


### volatile
```c
volatile int *p;

// value may change outside program control
while (*p == 0) {
    // waits for hardware update
}
```

### auto
```c
void f() {
    int x = 10;   // auto (implicit)
    auto int y = 20; // same thing (rarely used)
}
```

### static: block scope (persists across calls)
```c
void counter() {
    static int count = 0;
    count++;
    printf("%d\n", count);
}
```

### file scope (hidden from other files)
```c
static int secret = 42;
```

### extern
- file1.c
```c
int a = 10;
```
- file2.c
```c
extern int a;

int main() {
    printf("%d\n", a);
}
```

### register
```c
int main() {
    register int i;

    for (i = 0; i < 10; i++) {
        printf("%d\n", i);
    }

    // int *p = &i; ❌ error
}

```


# Compiling with Object Files (TL;DR)

## What are Object Files?
- Intermediate compiled files containing machine code.
- Not yet executable until linked together.
- Extensions:
  - Windows: `.obj`
  - Linux/macOS: `.o`

## Compile to Object Files

```bash
gcc -c foo.c   # produces foo.o
gcc -c bar.c   # produces bar.o
```

## Link Object Files into an Executable

```bash
gcc -o app foo.o bar.o
```

## Alternative (Compile + Link in One Step)

```bash
gcc -o app foo.c bar.c
```

## Why Use Object Files?

For small projects:
- Compile and link in one command.

For large projects:
- Compiling source files is slow.
- Linking object files is fast.

### Example

Suppose you have 1000 source files:

1. Compile all once:

```bash
gcc -c *.c
```

2. Link them:

```bash
gcc -o app *.o
```

3. Later, if only `foo.c` changes:

```bash
gcc -c foo.c   # rebuild only foo.o
gcc -o app *.o # relink everything
```

✅ Only the changed file is recompiled.

## Benefit

- Much faster builds.
- Avoids recompiling unchanged source files.
- Commonly used with build tools like `make`.

## Key Idea

```text
.c source files
      ↓ compile
.o object files
      ↓ link
executable
```

Object files allow incremental builds: recompile only changed files, then relink.


#### argv and argc
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int total = 0;

    for (int i = 1; i < argc; i++) {  // Start at 1, the first argument
        int value = atoi(argv[i]);    // Use strtol() for better error handling

        total += value;
    }

    printf("%d\n", total);
}


```


### unusued variables
```c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int total = 0;

    // Cute trick to get the compiler to stop warning about the
    // unused variable argc:
    (void)argc;

    for (char **p = argv + 1; *p != NULL; p++) {
        int value = atoi(*p); // Use strtol() for better error handling

        total += value;
    }

    printf("%d\n", total);
}
```

### EXIT STATUS
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("usage: mult x y\n");
        return EXIT_FAILURE;   // Indicate to shell that it didn't work
    }

    printf("%d\n", atoi(argv[1]) * atoi(argv[2]));

    return 0;  // same as EXIT_SUCCESS, everything was good.
}
```
Ex2
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    printf("argc is: %d\n", argc);
    if (argc != 3) {
        printf("usage: mult x y\n");
        return EXIT_FAILURE; // Indicate to shell that it didn't work
    }

    printf("%d\n", atoi(argv[1]) * atoi(argv[2]));

    return 0; // same as EXIT_SUCCESS, everything was good.
    // check exit status
    // echo $? returns 0 if success and 1 if failure

    // Bash says the exit code should be between 0 and 255, though a number of
    // codes are reserved.

    // On Linux, if you try any code outside the range 0-255, it will bitwise
    // AND the code with 0xff, effectively clamping it to that range.
}
```


### Get ENV
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // in your terminal, run env to see the lists of envs you have
    char *val = getenv("LANG");  // Try to get the value

    // Check to make sure it exists
    if (val == NULL) {
        printf("Cannot find the FROTZ environment variable\n");
        return EXIT_FAILURE;
    }

    printf("Value: %s\n", val);
}
```


### Unix-like Alternative Environment Variables
```c
#include <stdio.h>

extern char **environ;  // MUST be extern AND named "environ"

int main(void)
{
    for (char **p = environ; *p != NULL; p++) {
        printf("%s\n", *p);
    }

    // Or you could do this:
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}
```


### Environment variable
```c
#include <stdio.h>

int main(int argc, char **argv, char **env)  // <-- env!
{
    (void)argc; (void)argv;  // Suppress unused warnings

    for (char **p = env; *p != NULL; p++) {
        printf("%s\n", *p);
    }

    // Or you could do this:
    for (int i = 0; env[i] != NULL; i++) {
        printf("%s\n", env[i]);
    }
}
```

### Suppress unused variables
```c

#include <stdio.h>

int main(){

    int x = 0;
    (void)x;
}

```


### macro
```c


#include <stdio.h>
#define EXTRA_HAPPY 1

int main(void) {

    // conditional compilation
#ifdef EXTRA_HAPPY
    printf("eh is %d\n", EXTRA_HAPPY);
#else
    printf("Not defined\n");
#endif
    printf("OK!\n");
}
```
Negate it
```c
#ifdef EXTRA_HAPPY
    printf("I'm extra happy!\n");
#endif

#ifndef EXTRA_HAPPY
    printf("I'm just regular\n");
#endif
```

### elif mode
```c
#include <stdio.h>
#define MODE_1

int main(void) {

#ifdef MODE_1
    printf("This is mode 1\n");
#elifdef MODE_2
    printf("This is mode 2\n");
#elifdef MODE_3
    printf("This is mode 3\n");
#else
    printf("This is some other mode\n");
#endif
}
```


### General conditional
```c
#include <stdio.h>

#define HAPPY_FACTOR 1

int main(void)
{

#if HAPPY_FACTOR == 0
    printf("I'm not happy!\n");
#elif HAPPY_FACTOR == 1
    printf("I'm just regular\n");
#else
    printf("I'm extra happy!\n");
#endif

    printf("OK!\n");
}
```


One hackish thing this is used for is to comment out large numbers of lines quickly129.
If you put an #if 0 (“if false”) at the front of the block to be commented out and an #endif at the end, you can get this effect:
```c

#include <stdio.h>

#define HAPPY_FACTOR 1

int main(void) {
#if 0
    printf("All this code"); /* is effectively */
    printf("commented out"); // by the #if 0
#endif
}
```

### Losing a Macro: #undef
If you’ve defined something but you don’t need it any longer, you can undefine it with #undef.
```c

#include <stdio.h>

int main(void)
{
#define GOATS

#ifdef GOATS
    printf("Goats detected!\n");  // prints
#endif

#undef GOATS  // Make GOATS no longer defined

#ifdef GOATS
    printf("Goats detected, again!\n"); // doesn't print
#endif
}
```


### Built-in Macros
These are all defined:

Macro 	Description
__DATE__ 	The date of compilation—like when you’re compiling this file—in Mmm dd yyyy format
__TIME__ 	The time of compilation in hh:mm:ss format
__FILE__ 	A string containing this file’s name
__LINE__ 	The line number of the file this macro appears on
__func__ 	The name of the function this appears in, as a string130
__STDC__ 	Defined with 1 if this is a standard C compiler
__STDC_HOSTED__ 	This will be 1 if the compiler is a hosted implementation131, otherwise 0
__STDC_VERSION__ 	This version of C, a constant long int in the form yyyymmL, e.g. 201710L

```c
#include <stdio.h>

int main(void)
{
    printf("This function: %s\n", __func__);
    printf("This file: %s\n", __FILE__);
    printf("This line: %d\n", __LINE__);
    printf("Compiled on: %s %s\n", __DATE__, __TIME__);
    printf("C Version: %ld\n", __STDC_VERSION__);
}
```

Response:
```

This function: main
This file: sandbox_02.c
This line: 7
Compiled on: Jun 19 2026 09:33:12
C Version: 201710
```


### Macros with One Argument
```c
#include <stdio.h>

// #define SQR(x) x * x  // Not quite right, but bear with me
#define SQR(x) ((x) * (x))   // Good!
int main(void)
{
    printf("%d\n", SQR(12));  // 144
    // printf("%d\n", SQR(3 + 4));  // 19!!??
    printf("%d\n", SQR(3 + 4));  // now 49
}
```


```c
#include <stdio.h>
#include <math.h>  // For sqrt()

#define QUADP(a, b, c) ((-(b) + sqrt((b) * (b) - 4 * (a) * (c))) / (2 * (a)))
#define QUADM(a, b, c) ((-(b) - sqrt((b) * (b) - 4 * (a) * (c))) / (2 * (a)))
#define QUAD(a, b, c) QUADP(a, b, c), QUADM(a, b, c)

int main(void)
{
    printf("2*x^2 + 10*x + 5 = 0\n");
    printf("x = %f or x = %f\n", QUAD(2, 10, 5));
}
```


### Macros with Variable Arguments
```c
#include <stdio.h>

// Combine the first two arguments to a single number,
// then have a commalist of the rest of them:

#define X(a, b, ...) (10*(a) + 20*(b)), __VA_ARGS__

int main(void)
{
    printf("%d %f %s %d\n", X(5, 4, 3.14, "Hi!", 12));
}
```


### Macros with Variable Arguments
```c
#include <stdio.h>

// Combine the first two arguments to a single number,
// then have a commalist of the rest of them:

#define X(a, b, ...) (10*(a) + 20*(b)), __VA_ARGS__

int main(void)
{
    printf("%d %f %s %d\n", X(5, 4, 3.14, "Hi!", 12));
}
```


### Concatenation
```c
#include <stdio.h>

#define CAT(a, b) a##b

int main(void) {

    printf("%f\n", CAT(3.14, 1592));
    return 0;
}
```

### stringifiaction
```c
#include <stdio.h>

#define PRINT_INT_VAL(x) printf("%s = %d\n", #x, x)

int main(void)
{
    int a = 5;

    PRINT_INT_VAL(a);  // prints "a = 5"
}
```

```c
#define STR(x) #x

printf("%s\n", STR(3.14159));
```

### Multi line macro
```c

#include <stdio.h>

#define PRINT_NUMS_TO_PRODUCT(a, b) do { \
    int product = (a) * (b); \
    for (int i = 0; i < product; i++) { \
        printf("%d\n", i); \
    } \
} while(0)

int main(void)
{
    PRINT_NUMS_TO_PRODUCT(2, 4);  // Outputs numbers from 0 to 7
}
```


```c

#include <stdio.h>
:wa
#include <stdlib.h>

#define ASSERT_ENABLED 1

#if ASSERT_ENABLED
#define ASSERT(c, m)                                                           \
    do {                                                                       \
        if (!(c)) {                                                            \
            fprintf(stderr, __FILE__ ":%d: assertion %s failed: %s\n",         \
                    __LINE__, #c, m);                                          \
            exit(1);                                                           \
        }                                                                      \
    } while (0)
#else
#define ASSERT(c, m) // Empty macro if not enabled
#endif

int main(void) {
    int x = 30;

    ASSERT(x < 20, "x must be under 20");
}
```


### Error macro
```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {

#ifndef __STDC_IEC_559__
#error I really need IEEE-754 floating point to compile. Sorry!
#endif
}
```

### Pragma
```c

#include <stdio.h>
#include <stdlib.h>

// This tells the compiler: "split these 10 loop iterations across however many CPU threads are available, run them in parallel." Each thread executes a chunk of iterations.
int main(void) {

#pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        printf("hey\n");
    }
}
```
Run: 
```bash
 gcc sandbox_02.c -Wall -Wextra -g -fopenmp  && ./a.out 
 ```
Without -fopenmp, gcc just ignores the pragma and runs it as a normal single-threaded loop.


```c
#include <stdio.h>
#include <complex.h>

/* ---- 1. FP_CONTRACT / CX_LIMITED_RANGE ---- */

#pragma STDC FP_CONTRACT OFF
#pragma STDC CX_LIMITED_RANGE ON

void fp_contract_example(void) {
    /* With FP_CONTRACT OFF, this is computed as two separate
       rounded operations (multiply, then add) instead of being
       fused into a single fused-multiply-add (FMA) instruction,
       which can give a different (less precise) result. */
    double a = 1.0000001, b = 2.0000001, c = 3.0000001;
    double result = a * b + c;
    printf("fp result: %.10f\n", result);
}

void cx_limited_range_example(void) {
    /* With CX_LIMITED_RANGE ON, the compiler is allowed to use the
       textbook complex multiply/divide formulas instead of the
       safer (but slower) ones that guard against overflow/NaN
       on huge or tiny magnitudes. Only safe if you know your
       values won't hit those edge cases. */
    double complex x = 3.0 + 4.0 * I;
    double complex y = 1.0 + 2.0 * I;
    double complex z = x * y;
    printf("cx result: %f + %fi\n", creal(z), cimag(z));
}

/* ---- 2. _Pragma operator ---- */

/* These two lines are equivalent: */
#pragma GCC diagnostic ignored "-Wunused-variable"
_Pragma("GCC diagnostic ignored \"-Wunused-variable\"")

/* Useful because _Pragma can be wrapped in a macro,
   while #pragma cannot. */
#define DISABLE_WARNING(x) _Pragma(#x)

void pragma_macro_example(void) {
    DISABLE_WARNING(GCC diagnostic ignored "-Wunused-variable")
    int unused_var = 42; /* warning suppressed */
}

/* ---- 3. #line directive ---- */

void line_example(void) {
    printf("Before: line %d, file %s\n", __LINE__, __FILE__);

#line 300
    printf("After #line 300: line %d, file %s\n", __LINE__, __FILE__);

#line 1 "generated_code.c"
    printf("After #line with filename: line %d, file %s\n", __LINE__, __FILE__);
}

/* ---- 4. Null directive ---- */

#define FOO

void null_directive_example(void) {
#ifdef FOO
    #            /* does nothing, purely cosmetic */
    printf("FOO is defined\n");
#else
    printf("Something\n");
#endif

    /* Same idea, used for visual block separation: */
#
#ifdef FOO
    int x = 2;
#endif
#
#if 0
    int x2 = 12;
#endif
#
}

int main(void) {
    fp_contract_example();
    cx_limited_range_example();
    pragma_macro_example();
    line_example();
    null_directive_example();
    return 0;
}
```
