#ifndef GREEDY_H
#define GREEDY_H
#include "agent.h"
#include "greedy.h"
using namespace std;
class Minmax: public Greedy
{
	public:
		int depth;
		char tile;
		char other_tile;
		Minmax(Task &task_info);
// get_new_boards(char current_board[][GAMESIZE], char tile, 
// get_new_boards_vector(char current_board[][GAMESIZE], char tile);
// int is_on_board (int x, int y);
// void print_board(board_info &new_board);
// int cal_weight(char **board, char tile);
// string print_only_board(char **board);


};
#endif
