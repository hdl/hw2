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
using namespace std;


extern int weights[GAMESIZE][GAMESIZE];

typedef struct coord_t{
	int x;
	int y;
}coord;

#endif
