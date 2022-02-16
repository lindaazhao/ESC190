#include "lab3.h"
#include <stdio.h>

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
        return -1;
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
    
    struct party_node *temp = *head;
    struct party_node *swap = temp;
    
    double tempPrice; //temp variable to store price data
    char* tempTA; //temp variable to store TA data
    char* tempItem; //temp variable to store item data
    
    //temp = node;//temp node to hold node data and next link
    while(*head != NULL)
    {
    swap = temp; 
        while ((temp->next) != NULL)//travel till the second last element 
        {
           if((swap->price) < (swap->next->price))// compare the data of the nodes 
            {
              tempPrice = swap->price;
              swap->price = swap->next->price;// swap the prices
              swap->next->price = tempPrice;
              
              tempTA = swap->ta;
              swap->ta = swap->next->ta;// swap the TAs
              swap->next->ta = tempTA;
              
              tempItem = swap->item;
              swap->item = swap->next->item;// swap the items
              swap->next->item = tempItem;
            }
        temp = temp->next;    // move to the next element 
        }
    *head = (*head)->next;    // move to the next node
    }
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