#ifndef MINMAX_H
#define MINMAX_H
#include "agent.h"
#include "greedy.h"
using namespace std;
class Minmax: public Greedy
{
	public:
		stringstream ss;
		Board_info choose_min_child(Board_info &board1, Board_info &board2);
		Board_info choose_max_child(Board_info &board1, Board_info &board2);
		Board_info run_min_max(Board_info &current_board, int depth, char tile);
		string xy2(int x, int y);
		string get_next_state(Task &task_info, int x, int y);
};
#endif
