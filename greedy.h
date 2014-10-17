#ifndef GREEDY_H
#define GREEDY_H
#include "agent.h"
using namespace std;
class Greedy
{
	public:
		char your_tile;
		char other_tile;
		int depth;
		board_info root_board;

		void init(Task &task_info);
		void init_board_info(board_info &board);
		void get_new_boards(board_info &current_board, char tile, coord &move, vector<board_info> &new_board_vector);
		vector<board_info> get_new_boards_vector(board_info &current_board, char tile);
		int is_on_board (int x, int y);
		void print_board(board_info &new_board);
		int cal_weight(char **board);
        string print_only_board(char **board);
};
#endif
