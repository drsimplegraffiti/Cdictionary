#include <stdio.h>
#include <string.h>

struct Person {
  char name[50];
  float marks;
  int age;
};

int main() {
  struct Person s1;

  // automatic assignment
  s1.age = 90;
  s1.marks = 90.3f;
  strcpy(s1.name, "james");

  printf("name is %s and age is %d and mark is %.2f\n", s1.name, s1.age,
         s1.marks);

  // from scanf user input
  printf("Enter name: ");
  // gets(s1.name); deprecated
  fgets(s1.name, sizeof(s1.name), stdin);
  s1.name[strcspn(s1.name, "\n")] = '\0'; // remove trailing \n

  printf("Enter age: ");
  scanf("%d", &s1.age);

  printf("Enter marks: ");
  scanf("%f", &s1.marks);

  printf("name is %s and age is %d and mark is %.2f\n", s1.name, s1.age,
         s1.marks);

  return 0;
}
