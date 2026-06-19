#include <stdio.h>
#include <complex.h>

/* ---- 1. FP_CONTRACT / CX_LIMITED_RANGE ---- */

#pragma STDC FP_CONTRACT OFF
#pragma STDC CX_LIMITED_RANGE ON

void fp_contract_example(void) {
    /* With FP_CONTRACT OFF, this is computed as two separate
       rounded operations (multiply, then add) instead of being
       fused into a single fused-multiply-add (FMA) instruction,
       which can give a different (less precise) result. */
    double a = 1.0000001, b = 2.0000001, c = 3.0000001;
    double result = a * b + c;
    printf("fp result: %.10f\n", result);
}

void cx_limited_range_example(void) {
    /* With CX_LIMITED_RANGE ON, the compiler is allowed to use the
       textbook complex multiply/divide formulas instead of the
       safer (but slower) ones that guard against overflow/NaN
       on huge or tiny magnitudes. Only safe if you know your
       values won't hit those edge cases. */
    double complex x = 3.0 + 4.0 * I;
    double complex y = 1.0 + 2.0 * I;
    double complex z = x * y;
    printf("cx result: %f + %fi\n", creal(z), cimag(z));
}

/* ---- 2. _Pragma operator ---- */

/* These two lines are equivalent: */
#pragma GCC diagnostic ignored "-Wunused-variable"
_Pragma("GCC diagnostic ignored \"-Wunused-variable\"")

/* Useful because _Pragma can be wrapped in a macro,
   while #pragma cannot. */
#define DISABLE_WARNING(x) _Pragma(#x)

void pragma_macro_example(void) {
    DISABLE_WARNING(GCC diagnostic ignored "-Wunused-variable")
    int unused_var = 42; /* warning suppressed */
}

/* ---- 3. #line directive ---- */

void line_example(void) {
    printf("Before: line %d, file %s\n", __LINE__, __FILE__);

#line 300
    printf("After #line 300: line %d, file %s\n", __LINE__, __FILE__);

#line 1 "generated_code.c"
    printf("After #line with filename: line %d, file %s\n", __LINE__, __FILE__);
}

/* ---- 4. Null directive ---- */

#define FOO

void null_directive_example(void) {
#ifdef FOO
    #            /* does nothing, purely cosmetic */
    printf("FOO is defined\n");
#else
    printf("Something\n");
#endif

    /* Same idea, used for visual block separation: */
#
#ifdef FOO
    int x = 2;
#endif
#
#if 0
    int x2 = 12;
#endif
#
}

int main(void) {
    fp_contract_example();
    cx_limited_range_example();
    pragma_macro_example();
    line_example();
    null_directive_example();
    return 0;
}
