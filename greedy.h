#ifndef GREEDY_H
#define GREEDY_H
#include "agent.h"
#include "board_info.h"
using namespace std;
class Greedy
{
	public:
		char your_tile;
		char other_tile;
		int depth;
		~Greedy();
		Board_info root_board;
		void init(Task &task_info);
		void get_new_boards(char task_your_player, Board_info &current_board, char tile, coord &move, vector<Board_info> &new_board_vector);
		vector<Board_info> get_new_boards_vector(char task_your_player, Board_info &current_board, char tile);
};
#endif
