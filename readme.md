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

14. GDB to step through stdlib calls live
    gdb ./a.out
    break fgets
    run
    (lets you inspect what's actually happening at runtime)
