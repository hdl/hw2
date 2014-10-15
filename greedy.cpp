#include "task.h"
#include "agent.h"
#include "greedy.h"

Greedy::Greedy()
{
	move_dirc[0].x=0;
	move_dirc[0].y=1;
	move_dirc[1].x=1;
	move_dirc[1].y=1;
	move_dirc[2].x=1;
	move_dirc[2].y=0;
	move_dirc[3].x=1;
	move_dirc[3].y=-1;
	move_dirc[4].x=0;
	move_dirc[4].y=-1;
	move_dirc[5].x=-1;
	move_dirc[5].y=-1;
	move_dirc[6].x=-1;
	move_dirc[6].y=0;
	move_dirc[7].x=-1;
	move_dirc[7].y=1;
}

int Greedy::is_on_board (int x, int y){
	return (x >=0 && x < GAMESIZE && y >= 0 && y < GAMESIZE);
}

// get all new_boards for a possible move
void Greedy::get_new_boards(char current_board[][GAMESIZE], char tile, coord &move, vector<char *> &new_boards)
{
	int i=0, j=0;
	int x=0, y=0;
	int k=0, m=0;
	char other_tile;
	char **new_board;
	if (current_board[move.x][move.y] != '*'){
		return ;
	}

	if (tile == 'X')
		other_tile = 'O';
	else
		other_tile = 'X';

	// all the possible results of this move
	for(i = 0; i < 8; i++){

		new_board =(char **)malloc(sizeof(char *) * GAMESIZE);
		for(j=0; j<GAMESIZE; j++)
			new_board[j] = (char *)malloc(sizeof(char) * GAMESIZE);
		
		for(k=0; k<8; k++)
			for(m=0; m<8; m++)
				new_board[k][m] = current_board[k][m];

		new_board[move.x][move.y] = tile;
		x = move.x + move_dirc[i].x;
		y = move.y + move_dirc[i].y;
		// make sure neighbour on this direction is not your tile
		if (!is_on_board(x, y) || new_board[x][y]!=other_tile){
			// should free this new_board
			continue;		
		}
		// go foward from this direction
		// 1. reach your tile
		// 2. reach other tile
		// 3. reach *
		// 4. out of the board 
		while (is_on_board(x,y) && new_board[x][y] == other_tile){
			x += move_dirc[i].x;
			y += move_dirc[i].y;
		}
		if (!is_on_board(x, y) || new_board[x][y] == '*' ){
			// free the new_board	
			free_board_mem(new_board);
			continue;		
		}
		if (new_board[x][y] == tile){
			while(1){
				x-= move_dirc[i].x;	
				y-= move_dirc[i].y;
				if ( x == move.x && y == move.y)
					break;
				else
					new_board[x][y]	= tile;
			}
			new_boards.push_back((char *)new_board);
			print_board(new_board);	
		}
	}
}
void Greedy::print_board(char **board)
{
	int k=0, m=0;
	cout << "This board score is:"<<endl; 
	for(k=0; k<8; k++){
		for(m=0; m<8; m++)
			cout<<board[k][m];
		cout<<endl;
	}

}
void Greedy::free_board_mem(char **board)
{
	for (int j = 0; j < 8 ; j++)
	 	free(board[j]);
	free(board);
}
vector<char *> Greedy::get_new_boards_vector(char current_board[][GAMESIZE], char tile)
{
	int i=0, j=0;
	coord move;
	vector<char *> new_boards;
	new_boards.clear();
	for(i=0; i<GAMESIZE; i++){
		for(j=0; j<GAMESIZE; j++){
			move.x=i;
			move.y=j;
			get_new_boards(current_board, tile, move, new_boards);
		}
	}
	return new_boards;
}


