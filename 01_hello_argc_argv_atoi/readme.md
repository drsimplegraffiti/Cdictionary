#### Hello world
```c

#include <stdio.h>

int main(int argc, char const *argv[]) {
  // argc == argument count, argument vector
  printf("total input received: %d\n", argc); // if you run ./main hello world,
                                              // argc = 3


  for (int i = 0; i < argc; i++) {
    printf("argument [%d]: %s\n", i, argv[i]); // then argv[0] = ./main, argv[1]
                                               // hello ..
  }

  return 0;
}
```


![image](images/paste_1781250120.png)


```c

#include <stdio.h>
#include <stdlib.h>

#define TYPE_NAME(x)                                                           \
  _Generic((x),                                                                \
      int: "int",                                                              \
      char *: "char *",                                                        \
      const char *: "const char *",                                            \
      default: "unknown")

int main(int argc, char const *argv[]) {
  printf("ARG count is: %d\n", argc);

  if (argc < 1) {
    printf("please enter format like [./main something]\n");
    return -1;
  }

  // converts number string to int
  printf("number type before conversion is: %s\n", TYPE_NAME(argv[1]));
  int number = atoi(argv[1]);
  printf("number type before conversion is: %s\n", TYPE_NAME(number));

  if (number < 3) {
    printf("Please type a bigger number!! \n");
    return -1;
  }

  printf("Yay!!!!\n");

  return 0;
}
```

Run with:
```bash
gcc main.c -o main && ./main 3
```

