#include <stdio.h> // need this to use the printf () function
#include "lab1.h" // need this to link our Lab 1 functions

int main () {
    // Testing Part 1
    double test_p1 = split_bill(50.01 , 0.13 , 0.15 , 2);
    printf ("The split will be : $%.2f.\n " , test_p1);
    // $32.50
    // Add more tests here ...
    return 0;
}
