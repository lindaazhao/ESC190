#include "a1.h"

// remove these after
#include <stdio.h>
#include <stdlib.h>

Menu* load_menu(char* fname){
	
	// Create new menu struct
	struct Menu* menu = (struct Menu*)malloc(sizeof(struct Menu));
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
	struct Restaurant* restaurant = (struct Restaurant*)malloc(sizeof(struct Restaurant));
	restaurant->name = name;
	restaurant->menu = load_menu(MENU_FNAME);
	restaurant->num_completed_orders = 0;
	restaurant->num_pending_orders = 0;
	
	// Create empty pending_orders queue
	struct Queue* pending_orders = (struct Queue*)malloc(sizeof(struct Queue));
	pending_orders->head = NULL;
	pending_orders->tail = NULL;
	
	restaurant->pending_orders = pending_orders;
	
	return restaurant;
}

Order* build_order(char* items, char* quantities){

	char* order_items = strdup(items); // Convert string literal to byte string w/allocated memory
	char* order_quantities = strdup(quantities);

	// Create new_order, pointer to an Order struct
	struct Order* new_order = (struct Order*)malloc(sizeof(struct Order));
	new_order->num_items = strlen(items) / (ITEM_CODE_LENGTH-1);
	new_order->item_codes = (char**)malloc(sizeof(char*) * (new_order->num_items));
	new_order->item_quantities = (int*)malloc(sizeof(int) * (new_order->num_items));
	
	// Build item_codes from order_items


	// Build item_quantities from order_quantities
	char* token; // Define token for strtok
	
	for (int i = 0; i < new_order->num_items; i++){
		if (i == 0){ // First item, need to pass in order_quantities string to strtok
			token = strtok(order_quantities, MENU_DELIM);
		}
		else if (i == new_order->num_items - 1){
			token = strtok(NULL, MENU_DELIM);
		}
		else{ // Last item, string terminator is NULL
			token = strtok(NULL, NULL);
		}
			

		new_order->item_quantities;
	}

	// Array for item quantities =========================================================
	// int item_quantities[num_items]; // Static array containing item quantities
	// int counter = 0; // Used to index through item_quantities

	// // Separate quantities by MENU_DELIM and add them one-by-one to item_quantities array
	// char* token = strtok(quantities, MENU_DELIM);
	// char* item_quantity = strdup(token);
	// while (item_quantity != NULL){
	// 	item_quantities[counter] = atoi(item_quantity); // atoi converts ASCII to int
	// 	counter++;
	// 	token = strtok(NULL, MENU_DELIM);
	// }
	
	
}



void enqueue_order(Order* order, Restaurant* restaurant){

}
Order* dequeue_order(Restaurant* restaurant){

}

/*
	Getting information about our orders and order status
*/
double get_item_cost(char* item_code, Menu* menu){

}

double get_order_subtotal(Order* order, Menu* menu){

}

double get_order_total(Order* order, Menu* menu){

}

int get_num_completed_orders(Restaurant* restaurant){

}

int get_num_pending_orders(Restaurant* restaurant){

}

/*
	Closing down and deallocating memory
*/
void clear_order(Order** order){

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

void close_restaurant(Restaurant** restaurant){

}


// Helper functions
// ================================================================================================


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