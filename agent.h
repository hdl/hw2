#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#define GAMESIZE 8
#define INFI 888888
using namespace std;

typedef struct coord_t{
	int x;
	int y;
}coord;

typedef struct board_info_t{
	int x;
	int y;
	char tile;
	char **board;
	int weight;
	int visited;
	int best_child_x;
	int best_child_y;
}board_info;
extern int DEBUG;
extern coord move_dirc[8];
extern int weights[GAMESIZE][GAMESIZE];
extern int compare_order(board_info &board1, board_info &board2);
extern int compare_min_max(board_info &board1, board_info &board2);
extern int compare_max_min(board_info &board1, board_info &board2);
extern void free_board_mem(char **board);
extern void free_boards(vector<board_info> &new_board_vector);
#endif
