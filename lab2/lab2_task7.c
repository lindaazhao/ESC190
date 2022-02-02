#include <stdlib.h>

void append(int** x, int* n, int val) {
    *x = realloc(*x, ((*n) + 1) * sizeof(int));
    (*x)[*n] = val;
    *n += 1;
}