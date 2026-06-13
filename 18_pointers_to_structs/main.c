#include <stdio.h>

struct Person {
  char name[50];
  int age;
};

int main() {

  // dot notation - direct access
  struct Person p1 = {"James", 19};
  printf("Person one: %s, %d\n", p1.name, p1.age);

  // arrow notation - access through pointer
  // -> is just shorthand for (*ptr).field — dereference the pointer then access
  // the field.
  struct Person *ptr = &p1;
  printf("Via pointer: %s, %d\n", ptr->name, ptr->age);

  return 0;
}
