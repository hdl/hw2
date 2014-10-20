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
#include "board_info.h"
#define GAMESIZE 8
#define INFI 835586925 
#define PASS -2
using namespace std;

typedef struct coord_t{
	int x;
	int y;
}coord;

extern int DEBUG;
extern coord move_dirc[8];
extern int weights[GAMESIZE][GAMESIZE];
extern int compare_order(const Board_info &board1, const Board_info &board2);
extern int compare_min_max(const Board_info &board1, const Board_info &board2);
extern int compare_max_min(const Board_info &board1, const Board_info &board2);
extern void free_board_mem(char **board);
extern void free_boards(vector<Board_info> &new_board_vector);
#endif
