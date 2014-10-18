#include "task.h"
#include "agent.h"
#include "greedy.h"
#include "Board_info.h"

Greedy::~Greedy()
{
	free_board_mem(this->root_board.board);
}
void Greedy::init(Task &task_info){
	int j,k,m;
	depth = task_info.cut_off_depth;
	your_tile = task_info.your_player;
	if (your_tile == 'X')
		other_tile = 'O';
	else
		other_tile = 'X';

	root_board.board = new char*[GAMESIZE];
	for(j=0; j<GAMESIZE; j++)
		root_board.board[j] = new char[GAMESIZE];
	for(k=0; k<8; k++)
		for(m=0; m<8; m++)
			root_board.board[k][m] = task_info.cells[k][m];
	root_board.cal_weight(task_info.your_player);
	root_board.tile=your_tile;
}

// get all new_boards for a possible move in his every direction
void Greedy::get_new_boards(char task_your_player, Board_info &current_board, char tile, coord &move, vector<Board_info> &new_board_vector)
{
	int i=0, j=0;
	int x=0, y=0;
	int k=0, m=0;
	char other_tile;
	Board_info new_board;
	if (current_board.board[move.x][move.y] != '*'){
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
				new_board.board[k][m] = current_board.board[k][m];
		new_board.board[move.x][move.y] = tile;

		x = move.x + move_dirc[i].x;
		y = move.y + move_dirc[i].y;
		// make sure neighbour on this direction is not your tile
		if (!Board_info::is_on_board(x, y) || new_board.board[x][y]!=other_tile){
			free_board_mem(new_board.board);
			continue;		
		}
		// go foward from this direction
		// 1. reach your til  2. reach other tile  3. reach * 4. out of the board 
		while (Board_info::is_on_board(x,y) && new_board.board[x][y] == other_tile){
			x += move_dirc[i].x;
			y += move_dirc[i].y;
		}
		if (!Board_info::is_on_board(x, y) || new_board.board[x][y] == '*' ){
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
			new_board.cal_weight(task_your_player);
			//new_board.print();
			new_board_vector.push_back(new_board);
		}
	}
}

vector<Board_info> Greedy::get_new_boards_vector(char task_your_player, Board_info &current_board, char tile)
{
	int i=0, j=0;
	coord move;
	vector<Board_info> new_board_vector;
	new_board_vector.clear();
	for(i=0; i<GAMESIZE; i++){
		for(j=0; j<GAMESIZE; j++){
			move.x=i;
			move.y=j;
			get_new_boards(task_your_player, current_board, tile, move, new_board_vector);
		}
	}
	return new_board_vector;
}

