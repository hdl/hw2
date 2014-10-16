#include "task.h"
#include "agent.h"
#include "greedy.h"

Greedy::Greedy(Task &task_info)
{
	your_tile = task_info.your_player;
	if (your_tile == 'X')
		other_tile = 'O';
	else
		other_tile = 'X';
}

Greedy::~Greedy()
{
}
int Greedy::is_on_board (int x, int y){
	return (x >=0 && x < GAMESIZE && y >= 0 && y < GAMESIZE);
}

// get all new_boards for a possible move
void Greedy::get_new_boards(char current_board[][GAMESIZE], char tile, coord &move, vector<board_info> &new_board_vector)
{
	int i=0, j=0;
	int x=0, y=0;
	int k=0, m=0;
	char other_tile;
	board_info new_board;
	if (current_board[move.x][move.y] != '*'){
		return ;
	}

	if (tile == 'X')
		other_tile = 'O';
	else
		other_tile = 'X';

	// all the possible results of this move
	for(i = 0; i < 8; i++){

		new_board.board = new char*[GAMESIZE];
		for(j=0; j<GAMESIZE; j++)
			new_board.board[j] = new char[GAMESIZE];
		for(k=0; k<8; k++)
			for(m=0; m<8; m++)
				new_board.board[k][m] = current_board[k][m];

		new_board.board[move.x][move.y] = tile;
		x = move.x + move_dirc[i].x;
		y = move.y + move_dirc[i].y;
		// make sure neighbour on this direction is not your tile
		if (!is_on_board(x, y) || new_board.board[x][y]!=other_tile){
			free_board_mem(new_board.board);
			continue;		
		}
		// go foward from this direction
		// 1. reach your til  2. reach other tile  3. reach * 4. out of the board 
		while (is_on_board(x,y) && new_board.board[x][y] == other_tile){
			x += move_dirc[i].x;
			y += move_dirc[i].y;
		}
		if (!is_on_board(x, y) || new_board.board[x][y] == '*' ){
			free_board_mem(new_board.board);
			continue;		
		}
		if (new_board.board[x][y] == tile){
			while(1){
				x-= move_dirc[i].x;	
				y-= move_dirc[i].y;
				if ( x == move.x && y == move.y)
					break;
				else
					new_board.board[x][y] = tile;
			}
			new_board.x=move.x;
			new_board.y=move.y;
			new_board.tile=tile;
			new_board.weight=cal_weight(new_board.board, new_board.tile);
			new_board_vector.push_back(new_board);
			if(DEBUG==1){
				print_board(new_board);
				cout << "-----------------------------"<<endl;
			}	
		}
	}
}
void Greedy::print_board(board_info &new_board)
{
	cout << "Tile:"<<new_board.tile<< " Move:(" << new_board.x << ","<<new_board.y << ") Weight:"<< new_board.weight<<endl; 
	cout << print_only_board(new_board.board);
}
int Greedy::cal_weight(char **board, char tile)
{
	int weight=0;
	for (int i=0; i< 8; i++){
		for (int j = 0; j < 8 ; j++){
			if(board[i][j]==your_tile)
				weight+=weights[i][j];		
			else if(board[i][j]==other_tile)
				weight-=weights[i][j];		
		}
	}

	return weight;
}

vector<board_info> Greedy::get_new_boards_vector(char current_board[][GAMESIZE], char tile)
{
	int i=0, j=0;
	coord move;
	vector<board_info> new_board_vector;
	new_board_vector.clear();
	for(i=0; i<GAMESIZE; i++){
		for(j=0; j<GAMESIZE; j++){
			move.x=i;
			move.y=j;
			get_new_boards(current_board, tile, move, new_board_vector);
		}
	}
	return new_board_vector;
}

string Greedy::print_only_board(char **board){
	int k,m;
	string output="";
	for(k=0; k<8; k++){
		for(m=0; m<8; m++)
			output+=board[k][m];
		output+='\n';
	}
	return output;
}

