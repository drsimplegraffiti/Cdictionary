#include <stdio.h>
#include <setjmp.h>

jmp_buf env; // opaque type holding the "bookmark" to jump back to

void depth2(void)
{
    printf("Entering depth 2\n");
    longjmp(env, 3490);           // jump back to setjmp() — never returns
    printf("Leaving depth 2\n");  // never runs
}

void depth1(void)
{
    printf("Entering depth 1\n");
    depth2();
    printf("Leaving depth 1\n");  // never runs
}

int main(void)
{
    // setjmp() returns 0 the first time (setting the bookmark),
    // and returns the value passed to longjmp() when jumped back to.
    switch (setjmp(env)) {
        case 0:
            printf("setjmp() returned 0 (initial call)\n");
            depth1();
            printf("This never runs\n"); // skipped due to longjmp()
            break;

        case 3490:
            printf("Bailed back to main, setjmp() returned 3490\n");
            break;
    }

    return 0;
}
