#ifndef BOARD_INFO_H
#define BOARD_INFO_H
#include "agent.h"
using namespace std;
class Board_info
{
	public:
		int x;
		int y;
		char tile;
		char **board;
		int weight;
		int visited;
		int best_child_x;
		int best_child_y;
		int a;
		int b;
		int for_match;
		Board_info();
		Board_info clone();
		void cal_weight(char your_tile);
		static string get_board_cells(char **board);
		static int is_on_board (int x, int y);
		void print(void);
};
#endif
