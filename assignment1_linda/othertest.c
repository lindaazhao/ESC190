#include "../a1.h"
#include "a1_starter_tests.h"

int main(){
	Restaurant * restaurant = initialize_restaurant("McBonalbs");
	double l1_cost = get_item_cost("D1", restaurant->menu);
	print_menu(restaurant->menu);
	printf("\nL1 Cost: %f\n", l1_cost);

	Order * order_1 = build_order("L1B1" , "12,13");

	printf("Order 1, Item Code 1: %s\n", order_1->item_codes[0]);
	printf("Order 1, Item Code 2: %s\n", order_1->item_codes[1]);

	Order * order_2 = build_order("L1B1D1" , "12,10,9");
	printf("Order 1\n");
	print_order(order_1);
	printf("Order 2\n");
	print_order(order_2);

	printf("Enqueue Orders ======================\n");
	enqueue_order(order_1 , restaurant);
	enqueue_order(order_2 , restaurant);

	printf("Dequeue Orders ======================\n");
	Order * dq_order_1 = dequeue_order(restaurant);
	Order * dq_order_2 = dequeue_order(restaurant);
	printf("Order 1\n");
	print_order(dq_order_1);
	printf("Order 2\n");
	print_order(dq_order_2);

	return 0;

}
