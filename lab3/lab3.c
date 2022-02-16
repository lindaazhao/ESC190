#include "lab3.h"
#include <stdio.h>
#include <string.h>

// Helper functions
void delete_node(struct party_node *node_to_delete){
    free(node_to_delete->item);
    free(node_to_delete->ta);
    free(node_to_delete);
}


// Determine the length of a linked list
int length_of_list(struct party_node **head){
    int counter = 0;
    struct party_node* temp_node = *head;
    while (temp_node != NULL) {
        counter++;
        temp_node = temp_node->next;
    }
    return counter;
}

// ============================================================================

// Add TA party item request to the list
int add_request(struct party_node **head, char *item, double price, char *ta){
    // Check if item is "IDE"
    char* IDE = "IDE";

    int compare = strcmp(IDE, item);
    if (compare == 0) {
        return -1;
    }

    // Create new node otherwise
    struct party_node* new_head = (struct party_node*)malloc(sizeof(struct party_node));
        new_head->next = *head; 
        new_head->item = (char *)malloc((strlen(item)+1) * sizeof(char));
        strcpy(new_head->item, item);
        new_head->price = price;
        new_head->ta = (char *)malloc((strlen(ta)+1) * sizeof(char));
        strcpy(new_head->ta, ta);
        *head = new_head;
    return 0;
}


// Remove the last item added
void remove_request(struct party_node **head){
    if (*head != NULL){
        struct party_node *temp = *head;
        *head = (*head)->next;
        delete_node(temp);
    }
}


// Sort party item requests - in place?
void make_sorted(struct party_node **head){
    struct party_node previous; // Local "previous" node
    struct party_node* temp_node; // Temporary node to move along linked list
    int list_length = length_of_list(head);

    // Each loop moves the smallest element to the end of the list
    for (int i=0; i<list_length; i++){
        previous.next = *head; // Previous doesn't change; start sort here
        temp_node = &previous; // Start temp_node at the node (previous) before the actual linked list

        // Compares and swaps prices for first to last item
        while (temp_node->next != NULL && temp_node->next->next != NULL){
            if (temp_node->next->price < temp_node->next->next->price){
                
                struct party_node* swap = temp_node->next; // Store second node
                temp_node->next = swap->next; // Set first node to point to third; third is now second
                swap->next = temp_node->next->next; // Set original second node to point to fourth node
                temp_node->next->next = swap; // Set new second node (original third) to point to old second (now third)
            }
            temp_node = temp_node->next; // Iterate to next node
        }

        *head = previous.next; // Make head point to the top of the stack again
    }
}
    

// Trim list to fit the budget
double finalize_list(struct party_node **head, double budget){
    double remaining_budget = budget;
    
    struct party_node previous; // Local "previous" node
    struct party_node* temp_node;
    previous.next = *head; // Previous doesn't change; start iterating here
    temp_node = &previous;

    while (temp_node->next != NULL){
        if (remaining_budget - temp_node->next->price > 0){
            remaining_budget -= temp_node->next->price;
            temp_node = temp_node->next; // Iterate to consider next node            
        }
        else{
            struct party_node *node_to_delete = temp_node->next;
            temp_node->next = node_to_delete->next; // Automatically iterates to next node
            delete_node(node_to_delete);
        }
    }
    *head = previous.next;
    return remaining_budget;
}


// Print the current list - hope this is helpful!
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