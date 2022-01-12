#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Part 1: Splitting Bills
double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people) {
    float bill = (base_amount * (1 + tax_rate)) * (1 + tip_rate);
    float split_amount = roundf((bill / num_people) * 100)/100;
    
    if (split_amount * num_people < bill) {
        split_amount += 0.01;
    }
    
    return split_amount;
}

// Question 1: 
// The code truncates the number after the decimal point

// Question 2: 
/* First calculated raw split amount, then rounded it to nearest cent using roundf.
 * Used an if statement to only round up if the intial split amount did not cover the bill. */
 
 
 // Part 2: Adjust Pizza Prices
 double adjust_price(double original_price) {
     float new_price = 10 * pow(original_price, 0.5);
     return new_price;
 }
 
 
 // Part 3: Picky Eating
 int sandy_eats(char menu_item[]){   
     // Currently only works for lowercase menu items
     char *test_j;
     char *test_k;
     char *test_l;
     char *test_fish;
     
     test_j = strstr(menu_item, "j");
     test_k = strstr(menu_item, "k");
     test_l = strstr(menu_item, "l");
     test_fish = strstr(menu_item, "fish");
     
     int counter = 0;
     for(int i = 0; i < strlen(menu_item); i++) {
         if(menu_item[i] != ' ')
             counter++;
     }
     
     if(test_j || test_k || test_l || test_fish) {
         return 0;
     }
     else if (counter % 2 == 1) {
        return 0; 
     }
     else {
         return 1;
     }
 }
 
 
 // Part 4: Just Thinking About Fish
 void imagine_fish(char thing[]){
     char fish[] = "fish";
     strcat(thing, fish);
     return thing;
 }
 
 // Question 3
 /* Using string.h, can use strcat to concatenate two strings (i.e. strcat(thing, "fish"))
  * Without string.h, create a new string, then use a for/while loop to iterate through each 
  * character of both strings and add them to the new string. */
 