#include "task.h"
#include "agent.h"
#include "minmax.h"
// void get_new_boards(char current_board[][GAMESIZE], char tile, 
// 		coord &move, vector<board_info> &new_board_vector);
// vector<board_info> get_new_boards_vector(char current_board[][GAMESIZE], char tile);
// int is_on_board (int x, int y);
// void print_board(board_info &new_board);
// int cal_weight(char **board, char tile);
// string print_only_board(char **board);


Minmax::Minmax(Task $task_info)
{
	depth = task_info.cut_off_depth;
	tile = task_info.your_player;
	if (tile == 'X')
		other_tile = 'O';
	else
		other_tile = 'X';
}




