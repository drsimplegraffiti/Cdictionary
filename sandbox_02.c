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
