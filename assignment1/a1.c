#include "a1.h"

/**
	Add your functions to this file.
	Make sure to review a1.h.
	Do NOT include a main() function in this file
	when you submit.
*/

//Helper Function to count items:
int item_counter(char* fname){
    FILE* fp = fopen(MENU_FNAME, "r");
    char chr;
    int item_count = 0;
    chr = getc(fp);
    if (fp == NULL){
        return 0;
    }
    else{
        while (chr != EOF){
            if (chr == '\n'){
                item_count++;
                }
            }
            fclose(fp);
        }
        return item_count;
    }

//Function 1 - Restaurant:

Restaurant* initialize_restaurant(char* name){
    //initializing parameters
    struct Restaurant *rest_code = (struct Restaurant*)malloc(sizeof(struct Restaurant));
    rest_code->name = name;
    rest_code->menu = load_menu(MENU_FNAME);
    rest_code->num_completed_orders = 0;
    rest_code->num_pending_orders = 0;
    
    struct Queue *orders = (struct Queue*)malloc(sizeof(struct Queue)); //creating a queue
    orders->head = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    orders->head->order = NULL;
    orders->tail = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    orders->tail->order = NULL;
    
    orders->head->next = orders->tail;
    rest_code->pending_orders = orders;
    return rest_code;
    }

//Function 2 - Menu:

Menu* load_menu(char* fname){
    int item_count;
    
    struct Menu *menu_code = (struct Menu*)malloc(sizeof(struct Menu));
    item_count = item_counter(MENU_FNAME); //Used helper function to count number of lines in .txt file
    menu_code->num_items = item_count;
    menu_code->item_codes = (char**)malloc(sizeof(char*) * item_count);
    for (int i = 0; i < item_count; i++){
        menu_code->item_codes[i] = (char*)malloc(sizeof(char) * ITEM_CODE_LENGTH);
        }
    menu_code->item_names = (char**)malloc(sizeof(char*) * item_count);
    for (int i = 0; i<item_count; i++){
        menu_code->item_names[i] = (char*)malloc(sizeof(char)* MAX_ITEM_NAME_LENGTH);
        }     
    menu_code->item_cost_per_unit = (double*)malloc(sizeof(double) * item_count);
    return menu_code;
    }

//Function 3 - Order:

Order* build_order(char* items, char* quantities){
    struct Order *order_code = (struct Order*)malloc(sizeof(struct Order));
    order_code->num_items = (strlen(items)/2);
    order_code->item_codes = (char**)malloc(sizeof(char*) * ((strlen(items) - 1)/2));
    order_code->item_quantities = (int*)malloc(sizeof(int) * (strlen(quantities)/3));
    return order_code;
    }
    /*char* quantity = strtok(quantities, MENU_DELIM);
    while (quantity != NULL){
        quantity = strtok(NULL, MENU_DELIM);
        strcpy(order_code->item_quantities, quantity);
        }*/
    
    
//Function 4 - Enqueuing:    

void enqueue_order(Order* order, Restaurant* restaurant){
    struct Queue* orders;
    
    }

void print_menu(Menu* menu){
	fprintf(stdout, "--- Menu ---\n");
	for (int i = 0; i < menu->num_items; i++){
		fprintf(stdout, "(%s) %s: %.2f\n", 
			menu->item_codes[i], 
			menu->item_names[i], 
			menu->item_cost_per_unit[i]	
		);
	}
}


void print_order(Order* order){
	for (int i = 0; i < order->num_items; i++){
		fprintf(
			stdout, 
			"%d x (%s)\n", 
			order->item_quantities[i], 
			order->item_codes[i]
		);
	}
}


void print_receipt(Order* order, Menu* menu){
	for (int i = 0; i < order->num_items; i++){
		double item_cost = get_item_cost(order->item_codes[i], menu);
		fprintf(
			stdout, 
			"%d x (%s)\n @$%.2f ea \t %.2f\n", 
			order->item_quantities[i],
			order->item_codes[i], 
			item_cost,
			item_cost * order->item_quantities[i]
		);
	}
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = get_order_total(order, menu);
	
	fprintf(stdout, "Subtotal: \t %.2f\n", order_subtotal);
	fprintf(stdout, "               -------\n");
	fprintf(stdout, "Tax %d%%: \t$%.2f\n", TAX_RATE, order_total);
	fprintf(stdout, "              ========\n");
}