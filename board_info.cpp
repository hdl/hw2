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
	
	weight = 0;
	for (int i=0; i< 8; i++){
		for (int j = 0; j < 8 ; j++){
			if(board[i][j]==your_tile)
				weight+=weights[i][j];		
			else if(board[i][j]==other_tile)
				weight-=weights[i][j];		
		}
	}
}

string Board_info::get_board_cells(char **board){
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

void Board_info::print(void)
{
	cout<<"tile:"<<tile;
	cout<<" "<<x<<","<<y;
	cout<<" weight:"<<weight;
	cout<<" visited:"<<visited;
	cout<<" "<<best_child_x<<","<<best_child_y<<endl;
	cout<<get_board_cells(board);
	cout<<"-------------end---------------"<<endl;
}

