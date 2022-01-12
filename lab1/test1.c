#include <stdio.h> // need this to use the printf () function
#include "lab1.h" // need this to link our Lab 1 functions
#include <string.h>

int main () {
    // Testing Part 1
    double test_p1 = split_bill(50.01 , 0.13 , 0.15 , 2);
    printf ("The split will be : $%.2f.\n" , test_p1);
    // $32.50
    
    double test_p2 = split_bill(50.01 , 0.13 , 0.15 , 4);
    printf ("The split will be : $%.2f.\n" , test_p2);
    // $16.25
    
    
    // Testing Part 2
    double test_p3 = adjust_price(25.00);
    printf("The adjusted price is: $%.2f.\n", test_p3);
    // Should be $50.00
    
    double test_p4 = adjust_price(45.67);
    printf("The adjusted price is: $%.2f.\n", test_p4);
    // Should be $67.57
    
    
    // Testing Part 3
    char test_food[] = "Three Cheese Pizza";
    int test_p5 = sandy_eats(test_food);
    if (test_p5 == 0) {
        printf("Sandy would NOT eat '%s'.\n", test_food);
    }
    else {
        printf("Sandy would eat '%s'.\n", test_food);
    }
    
    char test_food2[] = "james";
    int test_p6 = sandy_eats(test_food2);
    if (test_p6 == 0) {
        printf("Sandy would NOT eat '%s'.\n", test_food2);
    }
    else {
        printf("Sandy would eat '%s'.\n", test_food2);
    }
    
    char test_food3[] = "fish pizzaz";
    int test_p7 = sandy_eats(test_food3);
    if (test_p7 == 0) {
        printf("Sandy would NOT eat '%s'.\n", test_food3);
    }
    else {
        printf("Sandy would eat '%s'.\n", test_food3);
    }
    
    
    // Testing Part 4
    char test_p8[30] = "zebra";
    imagine_fish(test_p8);
    printf("Just imagine, a %s!\n", test_p8);
    // Just imagine, a zebrafish!
    
    
    
    
    return 0;
}
