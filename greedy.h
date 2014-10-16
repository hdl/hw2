#ifndef GREEDY_H
#define GREEDY_H
#include "agent.h"
using namespace std;
#define GAMESIZE 8
class Greedy
{
	public:
	    coord move_dirc[8];	
		Greedy();
		~Greedy();
		void get_new_boards(char current_board[][GAMESIZE], char tile, coord &move, vector<board_info> &new_board_vector);
		vector<board_info> get_new_boards_vector(char current_board[][GAMESIZE], char tile);
		int is_on_board (int x, int y);
		void print_board(board_info &new_board);
		int cal_weight(char **board, char tile);
        string print_only_board(char **board);
};
#endif
