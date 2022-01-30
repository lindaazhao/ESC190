#include <stdlib.h>
#include "lab2_task7.c"
#include <stdio.h>

int main () {
    int z = 5;
    int *n = &z;
    int* x = (int *)malloc(*n * sizeof(int));
    int** pptr = &x;

    for (int i = 0; i < z; i++) {
        x[i] = i;
    }

    int val = 5;

    for (int i = 0; i < z; i++) {
        fprintf(stdout, "x at %d: %d\n", i, x[i]);
    }

    fprintf(stdout, "Value of *n: %d\n", *n);

    append(pptr, n, val);

    fprintf(stdout, "Value of *n: %d\n", *n);

    for (int i = 0; i < z; i++) {
        fprintf(stdout, "x at %d: %d\n", i, x[i]);
    }
}