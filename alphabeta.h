#ifndef ALPHABETA_H
#define ALPHABETA_H
#include "agent.h"
#include "minmax.h"
using namespace std;
class Alphabeta: public Minmax
{
	public:
		Board_info run_alphabeta(Board_info &current_board, int depth, int a, int b, char tile);
		Board_info max_a(Board_info &board1, Board_info &board2);
			Board_info min_b(Board_info &board1, Board_info &board2);
			int compare_max_a(const Board_info &board1, const Board_info &board2);
			int compare_min_b(const Board_info &board1, const Board_info &board2);
};
#endif
