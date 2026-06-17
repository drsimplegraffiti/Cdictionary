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
