#include "a1_test.h"

// remove these after
#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>


Menu* load_menu(char* fname){
	
	// Create new menu struct
	struct Menu* menu = (struct Menu*)malloc(sizeof(struct Menu));
	
	// Initialize getline parameters
	FILE* menu_file;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	menu_file = fopen(fname, "r");

	// Get each line from the menu file, one by one
	while ((read = getline(&line, &len, menu_file)) != -1){
		// Initialize variables to retrieve from menu lines
		char item_code[ITEM_CODE_LENGTH];
		char item_name[MAX_ITEM_NAME_LENGTH];
		char* item_price_str;
		double item_price;

		strcpy(item_code, strtok(line, MENU_DELIM));
		strcpy(item_name, strtok(NULL, MENU_DELIM));
		strcpy(item_price_str, strtok(NULL, "\n"));
		item_price_str = item_price_str + 1; // Remove the "$" character from the string
		item_price = strtod(item_price_str, NULL); // strtod converts string to double value

        // fprintf(stdout, "Item Code: %s", item_code);
        // fprintf(stdout, "Item Code: %s", item_name);
        // fprintf(stdout, "Item Code: %s", item_price_str);
        // fprintf(stdout, "Item Code: %d", item_price);
	}
	
	fclose(menu_file);
	free(line);
}