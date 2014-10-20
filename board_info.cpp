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
	a = -INFI;
	b = INFI;
}
Board_info Board_info::clone()
{
	int m,j,k;
	Board_info new_board;
	new_board.x = this->x;
	new_board.y = this->y;
	new_board.tile = this->tile;
	new_board.weight = this->weight;
	new_board.visited = this->visited;
	new_board.best_child_x= this->best_child_y;
	new_board.a = this->a;
	new_board.b = this->b;
	new_board.board = new char*[GAMESIZE];
	for(j=0; j<GAMESIZE; j++)
		new_board.board[j] = new char[GAMESIZE];
	for(k=0; k<8; k++)
		for(m=0; m<8; m++)
			new_board.board[k][m] = this->board[k][m];
	return new_board;
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
	cout<<"---------------------------begin"<<endl;
	cout<<"tile:"<<tile;
	cout<<" "<<x<<","<<y;
	cout<<" weight:"<<weight;
	cout<<" visited:"<<visited;
	cout<<" "<<best_child_x<<","<<best_child_y<<endl;
	//cout<<get_board_cells(board);
	cout<<"---------------------------end"<<endl;
}

