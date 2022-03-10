#include "a1.h"

// REMOVE THESE BEFORE SUBMISSION
#include <stdio.h>
#include <stdlib.h>


Menu* load_menu(char* fname){
	// *** Trim whitespace before and after menu items ***
	
	
	// Create new menu struct
	Menu* menu = (Menu*)malloc(sizeof(Menu));
	menu->num_items = 0;

	// Initialize arrays for menu items
	menu->item_codes = (char**)malloc(sizeof(char*)); // Allocate size of one pointer (for a string)
	menu->item_names = (char**)malloc(sizeof(char*)); // Allocate size of one pointer (for a string)
	menu->item_cost_per_unit = (double*)malloc(sizeof(double)); // Allocate size of one pointer (to a double)

	// Initialize getline parameters
	FILE* menu_file;
	char* line = NULL;	
	size_t len = 0;

	menu_file = fopen(fname, "r"); // Open menu file
	
	// Get each line from the menu file, one by one
	while (getline(&line, &len, menu_file) != -1){		
		// Split line into item code, item name, and item price
		char* token = strtok(line, MENU_DELIM);
		char* item_code = strdup(token); // Remember to free these, since they are allocated using malloc
		
		token = strtok(NULL, MENU_DELIM);
		char* item_name = strdup(token); // Remember to free these, since they are allocated using malloc
		
		token = strtok(NULL, "\n");
		char* item_price_str = strdup(token); // Remember to free these, since they are allocated using malloc
		double item_price = strtod(item_price_str+1, NULL); // strtod converts string to double value, item_price_str+1 to ignore the $

		// Increment number of items in the menu for each loop
		menu->num_items++;

		// First item already has spaced allocated for it, only need to realloc if there are 2+ items
		if (menu->num_items > 1) {
			// Make space for the new item in the menu
			menu->item_codes = (char**)realloc(menu->item_codes, (menu->num_items) * sizeof(char*));
			menu->item_names = (char**)realloc(menu->item_names, (menu->num_items) * sizeof(char*));
			menu->item_cost_per_unit = (double*)realloc(menu->item_cost_per_unit, (menu->num_items) * sizeof(double));
		}

		// Update menu with the new item
		menu->item_codes[menu->num_items-1] = item_code;
		menu->item_names[menu->num_items-1] = item_name;
		menu->item_cost_per_unit[menu->num_items-1] = item_price;	
		
		free(item_price_str); // Free the pointer that isn't used in the menu
	}
	
	free(line);
	fclose(menu_file);
	
	return menu;
}


Restaurant* initialize_restaurant(char* name){
	Restaurant* restaurant = malloc(sizeof(Restaurant));
	restaurant->name = name;
	restaurant->menu = load_menu(MENU_FNAME);
	restaurant->num_completed_orders = 0;
	restaurant->num_pending_orders = 0;
	
	// Create empty pending_orders queue
	Queue* pending_orders = malloc(sizeof(Queue));
	pending_orders->head = NULL;
	pending_orders->tail = NULL;
	
	restaurant->pending_orders = pending_orders;
	
	return restaurant;
}


Order* build_order(char* items, char* quantities){
	char* order_items = strdup(items); // Convert string literal to byte string w/malloc'd memory
	char* order_quantities = strdup(quantities); // Remember to free these!!!

	// Create new_order, pointer to an Order struct
	Order* new_order = malloc(sizeof(Order));
	new_order->num_items = strlen(items) / (ITEM_CODE_LENGTH-1);
	new_order->item_codes = (char**)malloc(sizeof(char*) * (new_order->num_items));
	new_order->item_quantities = (int*)malloc(sizeof(int) * (new_order->num_items));

	// Build item_codes from order_items
	int item_code_index;
	char* code = NULL;
	char* item_code;

	// Update num_order->item_codes for each item
	for (int j = 0; j < new_order->num_items; j++){
		code = (char*)malloc(sizeof(char) * ITEM_CODE_LENGTH);
		item_code_index = j * (ITEM_CODE_LENGTH-1);
		
		memcpy(code, (order_items+item_code_index), ITEM_CODE_LENGTH-1);
		code[ITEM_CODE_LENGTH-1] = '\0';
		item_code = strdup(code);
		
		new_order->item_codes[j] = item_code;
		free(code);
	}

	// Build item_quantities from order_quantities
	char* token; // Define token for strtok
	char* order_quantity; // To duplicate token
	
	// // Get each item's order_quantity, one by one using for loop and strtok (to separate by MENU_DELIM)
	for (int i = 0; i < new_order->num_items; i++){
		if (i == 0){ // First item, need to pass in order_quantities string to strtok
			token = strtok(order_quantities, MENU_DELIM);
			// printf("token: %s", token);
		}
		else if (i < new_order->num_items - 1){
			token = strtok(NULL, MENU_DELIM);
		}
		else { // Last item, order_quantities terminator is null character
			token = strtok(NULL, "\0");
		}
		order_quantity = strdup(token);
		int order_quant = atoi(order_quantity); // Convert string to integer
		new_order->item_quantities[i] = order_quant;
		free(order_quantity);
	}
	free(order_items);
	free(order_quantities);
		
	return new_order;
}


void enqueue_order(Order* order, Restaurant* restaurant){
	Queue* queue = restaurant->pending_orders;
	// Do we have to check if order is not NULL?
	QueueNode* new_node = malloc(sizeof(QueueNode));

	if (queue->head == NULL) { // Check if queue is empty
		queue->head = new_node;
		queue->tail = new_node;
	}
	else { // Queue is not empty
		queue->tail->next = new_node;
		queue->tail = new_node;
	}

	new_node->order = order;
	new_node->next = NULL;

	(restaurant->num_pending_orders)++; // Increment pending_orders
}


Order* dequeue_order(Restaurant* restaurant){
	Queue* queue = restaurant->pending_orders;
	Order* order = queue->head->order; // Order to dequeue, assuming queue is not empty
		 
	if (queue->head->next == NULL) { // Check if queue only has one item
		QueueNode* temp_node = queue->head; // Save current queue head
		queue->head = NULL; // Move head to next QueueNode
		queue->tail = NULL; 
		free(temp_node); // Free dequeue'd order head
	}

	else { // If queue has >1 item
		QueueNode* temp_node = queue->head; // Save current queue head
		queue->head = queue->head->next; // Move head to next QueueNode
		free(temp_node); // Free dequeue'd order head
	}
	
	(restaurant->num_pending_orders)--;
	(restaurant->num_completed_orders)++;

	return order;
}


/*
	Getting information about our orders and order status
*/
double get_item_cost(char* item_code, Menu* menu){	
	for (int i = 0; i<(menu->num_items); i++){
		if (strcmp(menu->item_codes[i], item_code) == 0){
			return menu->item_cost_per_unit[i];
		}
	}

	return 0.00;
}

double get_order_subtotal(Order* order, Menu* menu){
	double item_cost = 0.00;
	double subtotal = 0.00;
	
	for (int i = 0; i < order->num_items; i++){
		item_cost = get_item_cost(order->item_codes[i], menu);
		subtotal += item_cost * order->item_quantities[i];
	}
	return subtotal;
}

double get_order_total(Order* order, Menu* menu){
	double tax_rate = TAX_RATE; // TAX_RATE is a double for float division
	double order_subtotal = get_order_subtotal(order, menu);
	double order_total = order_subtotal * (1 + (tax_rate/100.0));

	return order_total;
}

int get_num_completed_orders(Restaurant* restaurant){
	return restaurant->num_completed_orders;
}

int get_num_pending_orders(Restaurant* restaurant){
	return restaurant->num_pending_orders;
}


/*
	Closing down and deallocating memory
*/
void clear_order(Order** order){
	for (int i = 0; i < (*order)->num_items; i++){
			free((*order)->item_codes[i]);
		}
		free((*order)->item_codes);
		free((*order)->item_quantities);
		free(*order);
}


void clear_menu(Menu** menu){

	for (int i = 0; i < (*menu)->num_items; i++){
		free((*menu)->item_codes[i]);
		free((*menu)->item_names[i]);
	}
	free((*menu)->item_codes);
	free((*menu)->item_names);
	free((*menu)->item_cost_per_unit);
	free(*menu);

}

// Seg fault, fine when there are no orders in the queue
void close_restaurant(Restaurant** restaurant){
	QueueNode* curr_node = NULL;
	QueueNode* temp_node = NULL;

	// // Free Orders
	if ((*restaurant)->pending_orders->head){ // Check that queue is not empty
		curr_node = (*restaurant)->pending_orders->head; // First QueueNode
		
		while (curr_node != NULL) { // Iterate through all QueueNodes
			clear_order(&(curr_node->order));
			temp_node = curr_node->next;
			free(curr_node);
			curr_node = temp_node->next;
		}
	}
	free((*restaurant)->pending_orders); // Free Queue
	clear_menu(&((*restaurant)->menu));
	free(*restaurant);
	*restaurant = NULL;
}


/*
	Helper Functions
*/
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