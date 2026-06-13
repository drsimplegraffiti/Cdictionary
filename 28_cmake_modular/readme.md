## Compilation

```bash
# single file
gcc main.c -o main

# multiple files - one step
gcc main.c shapes.c -o shapes

# multiple files - separate compilation (faster rebuilds)
gcc -c main.c        # -> main.o
gcc -c shapes.c      # -> shapes.o
gcc main.o shapes.o -o shapes

# with math library
gcc main.c -o main -lm

# with debug symbols for gdb
gcc -g main.c -o main
```

### Makefile

```makefile
shapes: main.o shapes.o
        gcc main.o shapes.o -o shapes

main.o: main.c shapes.h
        gcc -c main.c

shapes.o: shapes.c shapes.h
        gcc -c shapes.c

clean:
        rm -f *.o shapes
```

Only recompiles files that changed — efficient for large projects.
