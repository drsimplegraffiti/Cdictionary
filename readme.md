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
