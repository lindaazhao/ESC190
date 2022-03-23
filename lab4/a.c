#include "lab4.h"

int get_player_rank_helper(char player_id[], PlayerRecord* curr, int depth){
	int left_rank;
	int right_rank;
	
    if (curr == NULL){
        return -1;
    }

	if (curr->player->id == player_id){ // ******************
		return depth + 1;
	}

    left_rank = get_player_rank_helper(player_id, curr->left_child, depth+1);
    right_rank = get_player_rank_helper(player_id, curr->right_child, depth+1);



	if (left_rank == -1){
		return right_rank;
	}
	else{
		return left_rank;
	}

}