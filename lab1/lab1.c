#include <stdio.h>

double split_bill(double base_amount, double tax_rate, double tip_rate, int num_people) {
    float bill = (base_amount * (1 + tax_rate)) * (1 + tip_rate);
    float split_amount = roundf((bill / num_people) * 100)/100;
    
    if (split_amount * num_people < bill) {
        split_amount += 0.01;
    }
    
    // i eat ass
    
    return split_amount;
}