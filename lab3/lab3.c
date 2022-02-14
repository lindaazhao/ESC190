#include "lab3.h"
#include <stdio.h>
#include <string.h>

//Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
    //to check if item is "IDE"
    char IDE[3];
    IDE[0] = 'I';
    IDE[1] = 'D';
    IDE[2] = 'E';
    
    item[3];
    int count = 0;
    for (int i = 0; i<3; i++){
        if (item[i] == IDE[i]){
            count++;
           }
        else{
            continue;
        }
    }
    if (count == 3){
        return 1;
        }
    else{
        struct party_node* new_head = (struct party_node*)malloc(sizeof(struct party_node));
            new_head->next = *head; 
            new_head->item = item;
            new_head->price = price;
            new_head->ta = ta;
            *head = new_head;
        return 0;
    }
}
//Remove the last item added
void remove_request(struct party_node **head){
    
    struct party_node *temp = *head;
    *head = (*head)->next;
    free(temp);

}
//Sort party item requests - in place?
void make_sorted(struct party_node **head){
   
}

//Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    //Add code here
}

//Print the current list - hope this is helpful!
void print_list(struct party_node *head){
    int count = 1;
    printf("The current list contains:\n");
    while(head!=NULL){
        printf("Item %d: %s, %.2lf, requested by %s\n",
            count, head->item, head->price, head->ta);
        count++;
        head = head->next;
    }
    printf("\n\n");
    return;
}