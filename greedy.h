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
		char no_move_flag;
		int depth;
		int switch_player;
		vector<int> pass2_flag;
		~Greedy();
		int game_end(Board_info &current_board);
		Board_info root_board;
		void init(Task &task_info);
		void get_new_boards(char task_your_player, Board_info &current_board, char tile, coord &move, vector<Board_info> &new_board_vector);
		vector<Board_info> get_new_boards_vector(char task_your_player, Board_info &current_board, char tile);
		string run_greedy(Board_info &current_board, char your_tile);
};
#endif
