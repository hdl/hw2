#ifndef MINMAX_H
#define MINMAX_H
#include "agent.h"
#include "greedy.h"
using namespace std;
class Minmax: public Greedy
{
	public:
		int depth;
		vector <board_info>board_in_depth;
		void init(Task &task_info);
		board_info choose_min_child(board_info &board1, board_info &board2);
		board_info choose_max_child(board_info &board1, board_info &board2);
		board_info run_min_max(board_info current_board, int depth, char tile);
		string xy2board_number(int x, int y);

};
#endif
