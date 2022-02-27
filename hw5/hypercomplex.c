#include <stdlib.h>
#include "hypercomplex.h"

// Two-dimensional hypercomplex numbers.
//
// Each number is of the form a + b*u, where
// u*u == a for some real number a.
//
// Examples:
//
// If u*u == -1, we get the complex numbers.
// If u*u == 0, we get the dual numbers.
// If u*u == 1, we get the split numbers.
//
// Since we can't compute with reals, we will represent
// coordinates as doubles.

// User is politely requested not to access fields
// of this struct directly; use hPack and hUnpack.

// Construct a hypercomplex number a+b*u from the given coordinates.
// Argument u2 gives the value of u*u.
// The effect of operations on numbers with different values of u2
// is undefined.
struct h hPack(double a, double b, double u2){
    struct h z = {
        .a = a,
        .b = b,
        .u2 = u2
    };
    return z;
}

// Return the coordinates of a hypercomplex number
// through the given pointers.
void hUnpack(struct h z, double *a, double *b){
    *a = z.a;
    *b = z.b;
}

// Return z1 + z2.
struct h hAdd(struct h z1, struct h z2){
    double sum_a = z1.a + z2.a;
    double sum_b = z1.b + z2.b;
    return hPack(sum_a, sum_b, z1.u2);
}

// Return z1 - z2.
struct h hSubtract(struct h z1, struct h z2){
    double diff_a = z1.a - z2.a;
    double diff_b = z1.b - z2.b;
    return hPack(diff_a, diff_b, z1.u2);
}

// Return z1 * z2.
struct h hMultiply(struct h z1, struct h z2){
    double a = z1.a;
    double b = z1.b;
    double c = z2.a;
    double d = z2.b;
    double product_a = a * c + b * d * z1.u2;
    double product_b = b * c + a * d;
    return hPack(product_a, product_b, z1.u2);
}

// Given z == a + b*u, return its conjugate a - b*u.
struct h hConjugate(struct h z){
    return hPack(z.a, -1 * z.b, z.u2);
}

// Return q such that q*z2 == z1.
// If z2 is a zero divisor, behavior is undefined.
struct h hDivide(struct h z1, struct h z2){
    struct h conjugate = hConjugate(z2);
    struct h numerator = hMultiply(z1, conjugate);
    double denominator = z2.a * z2.a - z2.b * z2.b * z2.u2;
    return hPack(numerator.a / denominator, numerator.b / denominator, z1.u2);
}
