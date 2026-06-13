
## GDB

```bash
gcc -g main.c -o main   # compile with debug symbols
gdb ./main              # launch with binary

# or inside gdb:
(gdb) file ./main
(gdb) break 11          # set breakpoint at line 11
(gdb) run               # start program
(gdb) next              # next line
(gdb) print x           # print variable
(gdb) quit

tui enable
```

---

