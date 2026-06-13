#include <stdio.h>

int main() {

  // strings are array of characters ending with a null character \0
  // so if you declare char name[11] , 10 letters  is needed + \0

  // j  a  m  e  s     l  e  o  n  \0
  // 1  2  3  4  5  6  7  8  9  10  11  <-- needs 11
  char name[11] = "james leon"; // 10 chars + \0

  // or just let the compiler figure out the size:
  char name_[] = "james leon"; // compiler sets it to 11 automatically

  // or
  char name__[5] = {'j', 'a', 'm', 'e', '\0'};

  printf("%s\n", name__);

  return 0;
}
