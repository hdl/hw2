#include "task.h"
#include "agent.h"
#include "board_info.h"

int Board_info::is_on_board (int x, int y){
	return (x >=0 && x < GAMESIZE && y >= 0 && y < GAMESIZE);
}
Board_info::Board_info()
{
	x=-1;
	y=-1;
	tile = '$'; // need change
	board = NULL; //need change
	//weight = 1;
	visited = 0;
	best_child_x = -1;
	best_child_y = -1;
}

void Board_info::cal_weight(char your_tile)
{
	char other_tile;
	if (your_tile == 'X')
		other_tile = 'O';
	else
		other_tile = 'X';
	for (int i=0; i< 8; i++){
		for (int j = 0; j < 8 ; j++){
			if(board[i][j]==your_tile)
				weight+=weights[i][j];		
			else if(board[i][j]==other_tile)
				weight-=weights[i][j];		
		}
	}
}

string Board_info::get_board_cells(){
	int k,m;
	string output="";
	if(board == NULL)
		output = "board is NULL, please check";
	for(k=0; k<8; k++){
		for(m=0; m<8; m++)
			output+=board[k][m];
		output+='\n';
	}
	return output;
}

