#ifndef ALPHABETA_H
#define ALPHABETA_H
#include "agent.h"
#include "minmax.h"
using namespace std;
class Alphabeta: public Minmax
{
	public:
		Board_info run_alphabeta(Board_info &current_board, int depth, int a, int b, char tile);
};
#endif
