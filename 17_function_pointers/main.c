#include <stdio.h>

int add(int a, int b)      { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

// takes a function pointer as parameter
int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int main() {
    int a = 10, b = 5;

    // passing different functions as arguments
    printf("Add:      %d\n", calculate(a, b, add));
    printf("Subtract: %d\n", calculate(a, b, subtract));
    printf("Multiply: %d\n", calculate(a, b, multiply));

    // array of function pointers
    int (*ops[])(int, int) = {add, subtract, multiply};
    char *names[] = {"add", "subtract", "multiply"};

    for (int i = 0; i < 3; i++) {
        printf("%s: %d\n", names[i], ops[i](a, b));
    }

    return 0;
}
