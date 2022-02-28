#include <stdlib.h>
#include <stdio.h>
#include "a1_test.h"
#include "a1_test.c"

int main(){
    char* menu_fname = "menu.txt";
	fprintf(stdout, "Loading menu from %s.\n",
			menu_fname);
	Menu* menu = load_menu(menu_fname);
}