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
		vector<char **> get_new_boards_vector(char current_board[][GAMESIZE], char tile);
		void get_new_boards(char current_board[][GAMESIZE], char tile, coord &move, vector<char **> &new_boards);
		int is_on_board (int x, int y);
		void print_board(char **board);
		void free_board_mem(char **board);
		void free_boards(vector<char **> new_boards);
};
#endif
