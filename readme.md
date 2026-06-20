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

### Pass struct to a function
```c
#include <stdio.h>

struct s {
    int a, b;
};

int add(struct s x)
{
    return x.a + x.b;
}

int main(void)
{
    int t = add((struct s){.a=2, .b=4});  // <-- Here

    printf("%d\n", t);
}
```

### _Bool types
```c

#include <stdio.h>

int main(void) {
    _Bool is_tall = 1;
    printf("%d \n", is_tall);
    return 0;
}
```

### Complex type
```c

#include <complex.h>
#include <stdio.h>

int main(void) {
    complex float x = 1.2 + 2.3 * I;
    complex double y = 1.2 + 2.3 * I;

    printf("%lf %lf\n", x, y);
    return 0;
}
```

### Complex type
```c

#include <complex.h>
#include <stdio.h>

int main(void) {
    complex float x = 1.2 + 2.3 * I;
    complex double y = 1.2 + 2.3 * I;

    printf("%%lf %%lf\n", x, y);
    return 0;
}
```


### enums
```c
#include <complex.h>
#include <stdio.h>

enum animal {
    ANTELOPE = 4,
    BADGER, // Will be 5
    CAT,    // Will be 6
    DOG = 3,
    ELEPHANT, // Will be 4
    FISH      // Will be 5
};

int main(void) {
    enum animal A = BADGER;
    printf("animal A: %d\n", A);
    return 0;
}
```



### compound literal
```c
#include <stdio.h>

struct s {
    int a, b;
};

int add(struct s x)
{
    return x.a + x.b;
}

int main(void)
{
    int t = add((struct s){.a=2, .b=4});  // <-- Here

    printf("%d\n", t);
}
```

### Typedef
```c
#include <stdio.h>

typedef int time_counter;

int main(void)

{
    time_counter t = 90;
    printf("t is now %d\n", t);
}
```


### 
```c
const int a;        // a is a constant int — cannot be reassigned
const int *p;        // p is a pointer to a const int — *p is read-only, p itself can change
int * const p;        // p is a const pointer to int — p can't be reassigned, but *p can change
const int * const p;  // both: p can't be reassigned AND *p is read-only

int * restrict p;     // p is the ONLY pointer used to access this memory (optimization hint, no runtime effect)

volatile int a;       // a may change outside normal program flow (hardware, signal handler) — always re-read from memory, never cached/optimized away

#include <stdatomic.h>
atomic_int a;          // a's reads/writes are atomic — safe across threads without a data race
```

### variadic function
```c

#include <stdio.h>
#include <stdarg.h>

// Variadic function: takes a count, then that many ints
int sum(int count, ...) {
    va_list args;
    va_start(args, count);   // start reading args after 'count'

    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);  // pull next int from the list
    }

    va_end(args);  // clean up
    return total;
}

// Another example: mimic a tiny printf-like function
void log_ints(const char *label, int count, ...) {
    va_list args;
    va_start(args, count);

    printf("%s: ", label);
    for (int i = 0; i < count; i++) {
        printf("%d ", va_arg(args, int));
    }
    printf("\n");

    va_end(args);
}

int main(void) {
    printf("Sum: %d\n", sum(4, 10, 20, 30, 40));  // Sum: 100
    log_ints("Values", 3, 1, 2, 3);                // Values: 1 2 3
    return 0;
}
```


### assert
```c

// <assert.h> Runtime and Compile-time Diagnostics
// #define NDEBUG 1   // uncomment this to disable the assert

#include <assert.h>
#include <stdio.h>

int goat_count = 10;

void divide_goat_herd_by(int amount) {
    assert(amount != 0);

    goat_count /= amount;
}

int main(void) {
    divide_goat_herd_by(2); // OK

    divide_goat_herd_by(0); // Causes the assert to fire
}
```


```c
#include <stdio.h>
#include <assert.h>

#define ARRAY_SIZE 16

int main(void)
{
    static_assert(ARRAY_SIZE >= 16, "ARRAY_SIZE too small"); // now true, compiles fine

    int a[ARRAY_SIZE];
    a[10] = 10;          // valid index (0..15)

    printf("%d\n", a[10]);
}
```


### Complex 

```c

#include <stdio.h>
#include <math.h>
#include <complex.h>

int main(void)
{
    double complex x = 1 + 2 * I;
    double complex y = 3 + 4 * I;
    double complex z = 8 + 1.5708 * I;
    double complex r;
    double d;

    // Build / decompose
    r = CMPLX(1, 2);
    printf("CMPLX:  %f + %fi\n", creal(r), cimag(r));
    printf("creal:  %f\n", creal(x));
    printf("cimag:  %f\n", cimag(x));
    printf("conj:   %f + %fi\n", creal(conj(x)), cimag(conj(x)));

    // Magnitude / angle
    printf("cabs:   %f\n", cabs(x));
    printf("carg:   %f\n", carg(x));

    // Exponential / log / power / roots
    printf("cexp:   %f + %fi\n", creal(cexp(x)), cimag(cexp(x)));
    printf("clog:   %f + %fi\n", creal(clog(x)), cimag(clog(x)));
    r = cpow(x, y);
    printf("cpow:   %f + %fi\n", creal(r), cimag(r));
    printf("csqrt:  %f + %fi\n", creal(csqrt(x)), cimag(csqrt(x)));

    // Trig
    printf("ccos:   %f + %fi\n", creal(ccos(z)), cimag(ccos(z)));
    printf("csin:   %f + %fi\n", creal(csin(z)), cimag(csin(z)));
    printf("ctan:   %f + %fi\n", creal(ctan(z)), cimag(ctan(z)));

    // Inverse trig
    printf("cacos:  %f + %fi\n", creal(cacos(z)), cimag(cacos(z)));
    printf("casin:  %f + %fi\n", creal(casin(z)), cimag(casin(z)));
    printf("catan:  %f + %fi\n", creal(catan(z)), cimag(catan(z)));

    // Hyperbolic
    printf("ccosh:  %f + %fi\n", creal(ccosh(z)), cimag(ccosh(z)));
    printf("csinh:  %f + %fi\n", creal(csinh(z)), cimag(csinh(z)));
    printf("ctanh:  %f + %fi\n", creal(ctanh(z)), cimag(ctanh(z)));

    // Inverse hyperbolic
    printf("cacosh: %f + %fi\n", creal(cacosh(z)), cimag(cacosh(z)));
    printf("casinh: %f + %fi\n", creal(casinh(z)), cimag(casinh(z)));
    printf("catanh: %f + %fi\n", creal(catanh(z)), cimag(catanh(z)));

    // Projection (Riemann sphere) — interesting at infinity
    d = INFINITY;
    r = cproj(d + 2 * I);
    printf("cproj:  %f + %fi\n", creal(r), cimag(r));

    return 0;
}


// gcc -std=c11 sandbox_02.c -lm -o main
```

### C programming
```c
#include <ctype.h>
#include <stdio.h>

//  Character Classification and Conversion
int main(void) {

    printf("%s\n", isalnum('a') ? "yes" : "no"); // yes
    printf("%s\n", isalnum('B') ? "yes" : "no"); // yes
    printf("%s\n", isalnum('5') ? "yes" : "no"); // yes
    printf("%s\n", isalnum('?') ? "yes" : "no"); // no

    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isalpha('a') ? "yes" : "no"); // yes
    printf("%s\n", isalpha('B') ? "yes" : "no"); // yes
    printf("%s\n", isalpha('5') ? "yes" : "no"); // no
    printf("%s\n", isalpha('?') ? "yes" : "no"); // no

    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isblank(' ') ? "yes" : "no");  // yes
    printf("%s\n", isblank('\t') ? "yes" : "no"); // yes
    printf("%s\n", isblank('\n') ? "yes" : "no"); // no
    printf("%s\n", isblank('a') ? "yes" : "no");  // no
    printf("%s\n", isblank('?') ? "yes" : "no");  // no

    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", iscntrl('\t') ? "yes" : "no"); // yes (tab)
    printf("%s\n", iscntrl('\n') ? "yes" : "no"); // yes (newline)
    printf("%s\n", iscntrl('\r') ? "yes" : "no"); // yes (return)
    printf("%s\n", iscntrl('\a') ? "yes" : "no"); // yes (bell)
    printf("%s\n", iscntrl(' ') ? "yes" : "no");  // no
    printf("%s\n", iscntrl('a') ? "yes" : "no");  // no
    printf("%s\n", iscntrl('?') ? "yes" : "no");  // no

    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isdigit('0') ? "yes" : "no"); // yes
    printf("%s\n", isdigit('5') ? "yes" : "no"); // yes
    printf("%s\n", isdigit('a') ? "yes" : "no"); // no
    printf("%s\n", isdigit('B') ? "yes" : "no"); // no
    printf("%s\n", isdigit('?') ? "yes" : "no"); // no

    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isgraph('0') ? "yes" : "no");  // yes
    printf("%s\n", isgraph('a') ? "yes" : "no");  // yes
    printf("%s\n", isgraph('B') ? "yes" : "no");  // yes
    printf("%s\n", isgraph('?') ? "yes" : "no");  // yes
    printf("%s\n", isgraph(' ') ? "yes" : "no");  // no
    printf("%s\n", isgraph('\n') ? "yes" : "no"); // no

    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", islower('c') ? "yes" : "no"); // yes
    printf("%s\n", islower('0') ? "yes" : "no"); // no
    printf("%s\n", islower('B') ? "yes" : "no"); // no
    printf("%s\n", islower('?') ? "yes" : "no"); // no
    printf("%s\n", islower(' ') ? "yes" : "no"); // no

    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isprint('c') ? "yes" : "no");  // yes
    printf("%s\n", isprint('0') ? "yes" : "no");  // yes
    printf("%s\n", isprint(' ') ? "yes" : "no");  // yes
    printf("%s\n", isprint('\r') ? "yes" : "no"); // no

    // PUNCTUATION
    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", ispunct(',') ? "yes" : "no");  // yes
    printf("%s\n", ispunct('!') ? "yes" : "no");  // yes
    printf("%s\n", ispunct('c') ? "yes" : "no");  // no
    printf("%s\n", ispunct('0') ? "yes" : "no");  // no
    printf("%s\n", ispunct(' ') ? "yes" : "no");  // no
    printf("%s\n", ispunct('\n') ? "yes" : "no"); // no

    // is space
    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isspace(' ') ? "yes" : "no");  // yes
    printf("%s\n", isspace('\n') ? "yes" : "no"); // yes
    printf("%s\n", isspace('\t') ? "yes" : "no"); // yes
    printf("%s\n", isspace(',') ? "yes" : "no");  // no
    printf("%s\n", isspace('!') ? "yes" : "no");  // no
    printf("%s\n", isspace('c') ? "yes" : "no");  // no

    // is upper
    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isupper('B') ? "yes" : "no"); // yes
    printf("%s\n", isupper('c') ? "yes" : "no"); // no
    printf("%s\n", isupper('0') ? "yes" : "no"); // no
    printf("%s\n", isupper('?') ? "yes" : "no"); // no
    printf("%s\n", isupper(' ') ? "yes" : "no"); // no

    // is hex decimal
    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%s\n", isxdigit('B') ? "yes" : "no"); // yes
    printf("%s\n", isxdigit('c') ? "yes" : "no"); // yes
    printf("%s\n", isxdigit('2') ? "yes" : "no"); // yes
    printf("%s\n", isxdigit('G') ? "yes" : "no"); // no
    printf("%s\n", isxdigit('?') ? "yes" : "no"); // no

    // to lower
    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%c\n", tolower('B')); // b (made lowercase!)
    printf("%c\n", tolower('e')); // e (unchanged)
    printf("%c\n", tolower('!')); // ! (unchanged)

    // to upper
    printf("=>>>>>>>>>>>=============>>>>>>>>>>>>>>>>>>==========>>>>>\n");
    printf("%c\n", toupper('B')); // B (unchanged)
    printf("%c\n", toupper('e')); // E (made uppercase!)
    printf("%c\n", toupper('!')); // ! (unchanged)
    return 0;
}

// gcc -std=c11 sandbox_02.c -lm -o main
```

### Errorno

```c

#include <errno.h>
#include <math.h>
#include <stdio.h>

// <errno.h> Error Information

int main(void) {

    // errno 	Holds the error status of the last call
    // errno is set to 0 on startup
    // If you’re going to use solely it to check for errors, set it to 0 before
    // the call and then check it after.

    // This is commonly used in conjunction with perror() to get a
    // human-readable error message that corresponds to the specific error.

    // Important Safety Tip: You should never make your own variable called
    // errno—that’s undefined behavior.

    double x;

    errno = 0; // Make sure this is clear before the call

    // x = acos(2.0); // Invalid argument to acos()
    // acos() requires its argument to be in the range [-1.0, 1.0] 
    x = acos(0.5); // valid: acos(0.5) ≈ 1.047198 (radians, = 60°)

    if (errno == EDOM)
        perror("acos");
    else
        printf("Answer is %f\n", x);

    return 0;
}

// gcc -std=c11 sandbox_02.c -lm -o main
```


```c
#include <stdio.h>
#include <math.h>
#include <errno.h>

int main(void)
{
    double x;

    errno = 0;       // Make sure this is clear before the call

    x = exp(1e+30);  // Pass in some too-huge number, Failed
    // x = exp(30);  // Pass in some too-huge number, Pass

    if (errno == ERANGE)
        perror("exp");
    else
        printf("Answer is %f\n", x);

    return 0;
}
```


### Errorno
```c
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <errno.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "");

    char *bad_str = "\xff";  // Probably invalid char in this locale
    wchar_t wc;
    size_t result;
    mbstate_t ps;

    memset(&ps, 0, sizeof ps);

    result = mbrtowc(&wc, bad_str, 1, &ps);

    if (result == (size_t)(-1))
        perror("mbrtowc");  // mbrtowc: Illegal byte sequence
    else
        printf("Converted to L'%lc'\n", wc);

    return 0;
}
```


### <wctype.h> Wide Character Classification and Transformation
```c

#include <stdio.h>   // fflush(stdout)
#include <wchar.h>
#include <wctype.h>

int main(void)
{
    wchar_t c = L'B';

    // --- Classification (iswXXXX) ---
    wprintf(L"iswalnum:  %ls\n", iswalnum(c)  ? L"yes" : L"no"); // alphabetic or digit
    wprintf(L"iswalpha:  %ls\n", iswalpha(c)  ? L"yes" : L"no"); // A-Z / a-z
    wprintf(L"iswblank:  %ls\n", iswblank(L' ') ? L"yes" : L"no"); // space/tab (line-separator whitespace)
    wprintf(L"iswcntrl:  %ls\n", iswcntrl(L'\n') ? L"yes" : L"no"); // control char (0x00-0x1F, 0x7F)
    wprintf(L"iswdigit:  %ls\n", iswdigit(L'5') ? L"yes" : L"no"); // 0-9
    wprintf(L"iswgraph:  %ls\n", iswgraph(c)  ? L"yes" : L"no"); // printable, non-space
    wprintf(L"iswlower:  %ls\n", iswlower(L'c') ? L"yes" : L"no"); // a-z
    wprintf(L"iswprint:  %ls\n", iswprint(c)  ? L"yes" : L"no"); // printable, incl. space
    wprintf(L"iswpunct:  %ls\n", iswpunct(L',') ? L"yes" : L"no"); // punctuation
    wprintf(L"iswspace:  %ls\n", iswspace(L' ') ? L"yes" : L"no"); // whitespace
    wprintf(L"iswupper:  %ls\n", iswupper(c)  ? L"yes" : L"no"); // A-Z
    wprintf(L"iswxdigit: %ls\n", iswxdigit(c) ? L"yes" : L"no"); // 0-9, a-f, A-F

    // --- Runtime classification: wctype() + iswctype() ---
    wctype_t cls = wctype("digit");           // get class handle for "digit" at runtime
    wprintf(L"iswctype(digit): %ls\n",
        iswctype(L'5', cls) ? L"yes" : L"no"); // same as iswdigit('5')

    // --- Conversion ---
    wprintf(L"towlower: %lc\n", towlower(c));  // B -> b
    wprintf(L"towupper: %lc\n", towupper(L'e')); // e -> E

    // --- Runtime conversion: wctrans() + towctrans() ---
    wctrans_t conv = wctrans("toupper");       // get conversion handle at runtime
    wprintf(L"towctrans(toupper): %lc\n",
        towctrans(L'b', conv));                // same as towupper('b') -> B

    return 0;
}
```


### date and time
```c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>  // ldiv()
#include <math.h>    // modfl()

int main(void)
{
    // --- time(): current calendar time (time_t) ---
    time_t now = time(NULL);

    // --- ctime()/asctime(): human-readable string (NOT thread-safe, shares static buffer) ---
    printf("ctime:    %s", ctime(&now));               // "Mon Mar  1 21:32:23 2021\n"

    // --- localtime()/gmtime(): time_t -> struct tm (NOT thread-safe, shares static buffer) ---
    struct tm *local = localtime(&now);
    struct tm *utc   = gmtime(&now);
    printf("asctime local: %s", asctime(local));        // local broken-down time as string
    printf("asctime UTC  : %s", asctime(utc));

    // --- mktime(): struct tm (local time) -> time_t ---
    struct tm bdt = {
        .tm_year = 82,  // years since 1900 -> 1982
        .tm_mon  = 3,   // 0-11 -> April
        .tm_mday = 12,
        .tm_hour = 4,
        .tm_min  = 0,
        .tm_sec  = 4,
        .tm_isdst = -1, // let mktime() figure out DST
    };
    time_t cal_a = mktime(&bdt);   // fills in tm_wday, tm_yday, tm_isdst too

    // --- timegm() (C23 / many platforms): struct tm (UTC) -> time_t, no DST involved ---
    // time_t cal_utc = timegm(&bdt);

    // --- difftime(): seconds between two time_t (don't subtract directly, type is opaque) ---
    time_t cal_b = now;
    double diff_seconds = difftime(cal_b, cal_a);
    printf("Diff: %f seconds (%f years)\n",
        diff_seconds, diff_seconds / 60 / 60 / 24 / 365.2425);

    // --- strftime(): flexible, thread-safe formatted output (the sprintf() of dates) ---
    char s[128];
    strftime(s, sizeof s, "%A, %B %d, %Y", local);
    puts(s);                                             // "Monday, March 01, 2021"

    strftime(s, sizeof s, "%I:%M:%S %p", local);
    puts(s);                                              // "09:29:00 PM"

    strftime(s, sizeof s, "%FT%T%z", local);              // ISO 8601
    puts(s);                                              // "2021-03-01T21:29:00-0800"

    // --- clock(): CPU time used by this process (NOT wall-clock time) ---
    clock_t c_start = clock();
    for (volatile long i = 0; i < 100000000; i++); // busy work
    printf("CPU time: %f seconds\n", (clock() - c_start) / (double)CLOCKS_PER_SEC);

    // --- timespec_get(): higher-resolution (nanosecond) time ---
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    printf("timespec: %lld s, %ld ns (%.9f s total)\n",
        (long long)ts.tv_sec, ts.tv_nsec,
        ts.tv_sec + ts.tv_nsec / 1000000000.0);

    return 0;
}
```


### Puts
puts() is a standard library function from <stdio.h> that prints a string to stdout (the screen) and automatically adds a newline at the end.
```c
#include <stdio.h>

int main(void) {
    puts("Hello, world!");

    // Compare it to printf:
    printf("Hello, world!\n"); // you have to add \n yourself
    puts("Hello, world!");     // \n is added automatically, no format
                               // specifiers, no multiple arguments

    return 0;
}
```

### <string.h> String Manipulation


```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <errno.h>
#include <ctype.h>

int main(void)
{
    char buf[100];

    // --- memcpy() / memmove(): copy raw bytes (dest first, like '=') ---
    char s1[100] = "Goats", t1[100];
    memcpy(t1, s1, 6);        // non-overlapping copy
    memmove(s1 + 2, s1, 6);   // overlapping copy (safe, unlike memcpy)

    // --- memccpy() (C23): copy until char 'c' found, or n bytes copied ---
    // void *memccpy(dest, src, int c, size_t n);

    // --- strcpy() / strncpy(): copy a string ---
    char dest[20];
    strcpy(dest, "I like ");                 // "I like "
    int len = strlen(dest);
    strncpy(dest + len, "hockey hockey", sizeof(dest) - len - 1);
    dest[sizeof(dest) - 1] = '\0';            // strncpy may NOT null-terminate — do it yourself

    // --- strdup() / strndup() (C23): duplicate a string on the heap, free() when done ---
    char *dup = strdup("hello, world!");
    dup[0] = toupper(dup[0]);                 // "Hello, world!"
    free(dup);

    // --- strcat() / strncat(): append src onto dest (dest must have room!) ---
    char dest2[30] = "Hello";
    strcat(dest2, ", World!");                // "Hello, World!"
    strncat(dest2, "12345678", 3);            // append only first 3 chars: "...123"

    // --- strcmp() / strncmp() / memcmp(): compare, returns <0, 0, >0 ---
    if (!strcmp("Muffin", "Muffin"))          // 0 == equal, so !0 == true
        puts("Strings match");
    strncmp("Muffin", "Muffin Sandwich", 6);  // compare only first 6 chars -> 0

    // --- strcoll(): like strcmp() but locale-aware (handles accents sanely) ---
    setlocale(LC_ALL, "");
    strcoll("\u00e9", "f");                   // "é" vs "f", locale-correct ordering

    // --- strxfrm(): pre-transform a string for fast repeated strcoll()-style comparisons ---
    int xlen = strxfrm(NULL, "abc", 0) + 1;   // NULL/0 = just get required length
    char *xbuf = malloc(xlen);
    strxfrm(xbuf, "abc", xlen);               // xbuf now ready for strcmp()
    free(xbuf);

    // --- strchr() / strrchr() / memchr(): find a char (first / last / in n bytes) ---
    char *str = "Hello, world!";
    char *p = strchr(str, ',');               // first ',' 
    p = strrchr(str, 'o');                    // last 'o'
    p = memchr(str, '!', strlen(str));        // ignores NUL, scans n bytes

    // --- strspn() / strcspn(): length of leading run of (accept / non-reject) chars ---
    strspn("a banana", "aeiou");              // 1 -> just "a"
    strcspn("the bolivian navy", "y");        // chars before first 'y'

    // --- strpbrk(): find first char in s1 that's ANY of the chars in s2 ---
    p = strpbrk("Hello, world!", "dow!");     // points at first matching char ('o')

    // --- strstr(): find a substring inside a string ---
    p = strstr("The quick brown fox", "brown");  // -> "brown fox"

    // --- strtok(): destructively split a string by delimiter chars ---
    char tokbuf[] = "Where is my bacon, dude?";
    char *token = strtok(tokbuf, ".,?! ");
    while (token != NULL) {
        printf("Word: \"%s\"\n", token);
        token = strtok(NULL, ".,?! ");        // pass NULL to continue same string
    }

    // --- memset() / memset_explicit() (C23): fill memory with a byte value ---
    struct { float a; char *b; int c; } st;
    memset(&st, 0, sizeof st);                // zero out a struct
    // memset_explicit(&password, 0, sizeof password); // guaranteed not optimized away (for secrets)

    // --- strerror(): get human-readable string for an errno value ---
    FILE *fp = fopen("NONEXISTENT.TXT", "r");
    if (fp == NULL)
        printf("Error %d: %s\n", errno, strerror(errno)); // "No such file or directory"

    // --- strlen(): length of a string, NOT counting the NUL terminator ---
    printf("Length: %zu\n", strlen("Hello, world!")); // 13

    return 0;
}
```


### <stdlib.h> Standard Library Functions
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>
#include <stdint.h>

// --- comparator for bsearch()/qsort() ---
int compar(const void *a, const void *b) {
    const int *x = a, *y = b;
    return *x - *y; // negative/0/positive
}

// --- atexit() handlers ---
void exit_handler_1(void) { printf("Exit handler 1 called!\n"); }
void exit_handler_2(void) { printf("Exit handler 2 called!\n"); }

int main(void)
{
    setlocale(LC_ALL, "");

    // ====== String <-> number conversions ======
    double d1 = atof("3.141593");                  // basic, no error checking
    int    i1 = atoi("3490");                       // basic, no error checking
    long   i2 = atol("123456");
    long long i3 = atoll("123456789012");

    char *badchar;
    double d2 = strtod("   123.4567beej", &badchar);     // robust: detects bad chars
    printf("strtod: %f, stopped at: \"%s\"\n", d2, badchar);

    long l1 = strtol("0x123", NULL, 0);              // base 0 = auto-detect (hex here)
    long l2 = strtol("101010", NULL, 2);             // explicit binary
    unsigned long ul1 = strtoul("4000000000", NULL, 10);
    printf("strtol/strtoul: %ld %ld %lu\n", l1, l2, ul1);

    // ====== Pseudorandom numbers ======
    srand((unsigned)time(NULL));                      // seed once
    int r = rand() % 10;                               // 0-9 (biased, but fine for casual use)
    printf("Random 0-9: %d\n", r);

    // ====== Dynamic memory ======
    int *p = malloc(5 * sizeof(int));                  // uninitialized memory
    int *q = calloc(5, sizeof(int));                    // zeroed memory
    int *aligned = aligned_alloc(256, 10 * sizeof(int)); // specific alignment
    p = realloc(p, 10 * sizeof(int));                    // resize (may move!)
    free(p); free(q); free(aligned);

    // ====== Integer math ======
    printf("abs(-7) = %d\n", abs(-7));
    div_t dv = div(64, -7);
    printf("64 / -7 -> quot=%d rem=%d\n", dv.quot, dv.rem);

    // ====== Sorting & searching ======
    int arr[9] = {14, 2, 3, 17, 10, 8, 6, 1, 13};
    qsort(arr, 9, sizeof(int), compar);                  // sort in place
    int
```


```c
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

// printf()-style wrapper using va_list
int logger(const char *format, ...) {
    va_list va;
    time_t now = time(NULL);
    struct tm *t = gmtime(&now);
    printf("%04d-%02d-%02d %02d:%02d:%02d : ",
        t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
    va_start(va, format);
    int result = vprintf(format, va);   // vprintf/vfprintf/vsprintf/vsnprintf all work the same way
    va_end(va);
    printf("\n");
    return result;
}

int main(void)
{
    FILE *fp;
    char s[128];
    int a, c;

    // ====== Opening / closing ======
    fp = fopen("spoon.txt", "w+");          // r, w, a, r+, w+, a+  (+ "b" for binary)
    if (fp == NULL) {
        perror("fopen");                     // human-readable error using errno
        return 1;
    }

    // ====== Writing (formatted, char, string) ======
    fprintf(fp, "Line %d: %s\n", 1, "hello"); // formatted write to file
    fputc('X', fp);                            // single char
    fputs("World\n", fp);                       // string (no formatting)
    fflush(fp);                                 // force buffered output to disk now

    // ====== Positioning ======
    fseek(fp, 0, SEEK_SET);     // SEEK_SET / SEEK_CUR / SEEK_END
    long pos = ftell(fp);       // current byte offset
    fpos_t fpos;
    fgetpos(fp, &fpos);         // opaque position (alt to ftell)
    fsetpos(fp, &fpos);         // restore opaque position
    rewind(fp);                 // same as fseek(fp, 0, SEEK_SET)

    // ====== Reading (formatted, char, string) ======
    fscanf(fp, "Line %d: %s", &a, s);   // formatted read
    c = fgetc(fp);                        // single char (returns int, check EOF)
    fgets(s, sizeof(s), fp);              // safe line read (use over gets()! gets() removed in C11)

    // ====== Console I/O (== file I/O on stdin/stdout/stderr) ======
    printf("Hello, world!\n");            // == fprintf(stdout, ...)
    // scanf("%d", &a);                   // == fscanf(stdin, "%d", &a)
    putchar('A');                          // == putc('A', stdout)
    puts("A string with auto newline");

    // ====== String-based formatting (no file involved) ======
    sprintf(s, "x=%d", 42);                // unsafe — no bounds check
    snprintf(s, sizeof(s), "x=%d", 42);    // SAFE — always NUL-terminates
    sscanf("42-7", "%d-%d", &a, &c);       // parse from a string

    // ====== printf format specifier cheat sheet ======
    printf("%d\n", 100);            // decimal int
    printf("%5d|\n", 100);          // field width, right-justified: "  100|"
    printf("%-5d|\n", 100);         // left-justified:                "100  |"
    printf("%05d\n", 100);          // zero-padded:                   "00100"
    printf("%.2f\n", 3.14159);      // 2 decimal places: "3.14"
    printf("%x %X\n", 255, 255);    // hex lower/upper: "ff FF"
    printf("%*d\n", 8, 42);         // dynamic field width via '*'

    // ====== scanf scanset / discard ======
    // scanf(" %[^\n]", s);          // read until newline
    // scanf("%d %*d %d", &a, &c);   // '*' discards a value without storing it

    // ====== Binary I/O ======
    int nums[5] = {1, 2, 3, 4, 5};
    FILE *bin = fopen("numbers.dat", "wb");
    fwrite(nums, sizeof(int), 5, bin);    // write raw binary block
    fclose(bin);

    bin = fopen("numbers.dat", "rb");
    fread(nums, sizeof(int), 5, bin);     // read raw binary block
    fclose(bin);

    // ====== Push a char back onto the stream ======
    int peek = fgetc(fp);
    ungetc(peek, fp);                      // "unread" it — shows up again on next read

    // ====== Status checks ======
    if (feof(fp))   printf("Reached EOF\n");
    if (ferror(fp)) printf("Stream error occurred\n");
    clearerr(fp);                          // reset both flags

    // ====== Buffering control ======
    setvbuf(fp, NULL, _IOFBF, 1024);       // _IOFBF full, _IOLBF line, _IONBF none
    // setbuf(fp, NULL);                   // shorthand for unbuffered

    // ====== Temp files ======
    FILE *tmp = tmpfile();                  // auto-deleted on close/exit
    fprintf(tmp, "scratch data");
    fclose(tmp);

    char tmpname[L_tmpnam];
    tmpnam(tmpname);                        // generates a unique filename (prefer mkstemp() if available)

    // ====== File management ======
    fclose(fp);
    rename("spoon.txt", "spoon_renamed.txt");  // rename/move
    remove("spoon_renamed.txt");                // delete from disk

    // ====== Custom va_list-based printf wrapper ======
    logger("x = %d", a);

    return 0;
}
```

### Standard definition
```c
#include <stdio.h>
#include <stddef.h>
#include <stdalign.h>
#include <uchar.h>
#include <string.h>

struct foo {
    int a;
    char b;
    char c;
    float d;
};

int main(void)
{
    // --- ptrdiff_t: signed difference between two pointers ---
    int cats[100];
    int *f = cats + 20;
    int *g = cats + 60;
    ptrdiff_t d = g - f;             // 40
    printf("ptrdiff (dec): %td\n", d);
    printf("ptrdiff (hex): %tX\n", d);

    // --- size_t: unsigned, returned by sizeof(), printed with %zu ---
    size_t x = sizeof(int);
    printf("sizeof(int): %zu\n", x);

    // Some functions (e.g. mbrtoc16) return negative error codes cast
    // to size_t — print those with %zd to see the signed value correctly:
    char16_t wc;
    mbstate_t mbs;
    memset(&mbs, 0, sizeof mbs);
    x = mbrtoc16(&wc, "b", 8, &mbs);
    printf("mbrtoc16 result (signed view): %zd\n", x);

    // --- max_align_t: largest fundamental alignment on this platform ---
    printf("Max fundamental alignment: %d\n", (int)alignof(max_align_t));

    // --- wchar_t: wide character type (just an int-family type, not shown directly) ---
    wchar_t wide_null = 0; // 0 is the wide NUL character

    // --- offsetof: byte offset of a field within a struct/union ---
    printf("offsetof a: %zu\n", offsetof(struct foo, a));
    printf("offsetof b: %zu\n", offsetof(struct foo, b));
    printf("offsetof c: %zu\n", offsetof(struct foo, c));
    printf("offsetof d: %zu\n", offsetof(struct foo, d));

    return 0;
}
```


### Setjump
```c
#include <stdio.h>
#include <setjmp.h>

jmp_buf env; // opaque type holding the "bookmark" to jump back to

void depth2(void)
{
    printf("Entering depth 2\n");
    longjmp(env, 3490);           // jump back to setjmp() — never returns
    printf("Leaving depth 2\n");  // never runs
}

void depth1(void)
{
    printf("Entering depth 1\n");
    depth2();
    printf("Leaving depth 1\n");  // never runs
}

int main(void)
{
    // setjmp() returns 0 the first time (setting the bookmark),
    // and returns the value passed to longjmp() when jumped back to.
    switch (setjmp(env)) {
        case 0:
            printf("setjmp() returned 0 (initial call)\n");
            depth1();
            printf("This never runs\n"); // skipped due to longjmp()
            break;

        case 3490:
            printf("Bailed back to main, setjmp() returned 3490\n");
            break;
    }

    return 0;
}
```
