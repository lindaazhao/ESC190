#include "a1.h"

// remove these after
#include <stdio.h>
#include <stdlib.h>

Menu* load_menu(char* fname){
	
	struct Menu* menu = (struct Menu*)malloc(sizeof(struct Menu));
	
	FILE* menu_file;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	menu_file = fopen(fname, "r");

	while ((read = getline(&line, &len, menu_file)) != -1){
		char item_code[ITEM_CODE_LENGTH];
		char item_name[MAX_ITEM_NAME_LENGTH];
		char item_price_str;
		double item_price;

		strcpy(item_code, strok(line, MENU_DELIM));
		strcpy(item_name, strtok(NULL, MENU_DELIM));
		strcpy(item_price_str, strtok(NULL, "\n"));
		item_price = strtod(item_price_str, NULL);
	}
	
	fclose(menu_file);
	free(line);

	




	
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
	
	// Number of items in the order
	int num_items = strlen(items) / (ITEM_CODE_LENGTH-1);
	
	// Array for item codes
	// char** item_codes = ...

	// Array for item quantities =========================================================
	int item_quantities[num_items]; // Static array containing item quantities
	int counter = 0; // Used to index through item_quantities

	// Separate quantities by MENU_DELIM and add them one-by-one to item_quantities array
	char* item_quantity = strtok(quantities, MENU_DELIM);
	while (item_quantity != NULL){
		item_quantities[counter] = atoi(item_quantity); // atoi converts ASCII to int
		counter++;
		item_quantity = strtok(NULL, MENU_DELIM);
	}
	
	// Create new_order, pointer to an Order struct
	struct Order* new_order = (struct Order*)malloc(sizeof(struct Order));
	new_order->num_items = num_items;
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