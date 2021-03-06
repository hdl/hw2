#include "task.h"
#include "agent.h"
#include "greedy.h"
#include "board_info.h"

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
	no_move_flag =0;
	switch_player =0;
	pass2_flag.clear();
}
int Greedy::game_end(Board_info &current_board)
{
	int i,j;
	if(pass2_flag.size()>=2){
		if(pass2_flag.back()==1) {
			if(pass2_flag[pass2_flag.size()-2]==1){
				// cout<<"pass2_flag=2\n";
				return 1;
			}
		}
		else {
			pass2_flag.clear();
		}
	}

	for(i=0; i<GAMESIZE; i++)	
		for(j=0; j<GAMESIZE; j++){
			if(current_board.board[i][j]==other_tile)
				return 0;
		}
	// cout << "game end\n";
	return 1;
}

// get all new_boards for a possible move in his every direction
void Greedy::get_new_boards(char task_your_player, Board_info &current_board, char tile, coord &move, vector<Board_info> &new_board_vector)
{
	int i=0, j=0;
	int x=0, y=0;
	int k=0, m=0;
	int find_flag = 0;
	char other_tile;
	Board_info new_board;
	if (current_board.board[move.x][move.y] != '*'){
		return ;
	}

	if (tile == 'X')
		other_tile = 'O';
	else
		other_tile = 'X';
	new_board.board = new char*[GAMESIZE];
	for(j=0; j<GAMESIZE; j++)
		new_board.board[j] = new char[GAMESIZE];
	for(k=0; k<8; k++)
		for(m=0; m<8; m++)
			new_board.board[k][m] = current_board.board[k][m];

	// all the possible results of this move
	for(i = 0; i < 8; i++){
		x = move.x + move_dirc[i].x;
		y = move.y + move_dirc[i].y;
		// make sure neighbour on this direction is not your tile
		if (!Board_info::is_on_board(x, y) || new_board.board[x][y]!=other_tile){
			continue;		
		}
		// go foward from this direction
		// 1. reach your til  2. reach other tile  3. reach * 4. out of the board 
		while (Board_info::is_on_board(x,y) && new_board.board[x][y] == other_tile){
			x += move_dirc[i].x;
			y += move_dirc[i].y;
		}
		if (!Board_info::is_on_board(x, y) || new_board.board[x][y] == '*' ){
			continue;// this direction is not valid	
		}
		if (new_board.board[x][y] == tile){
			find_flag=1;
			while(1){
				x-= move_dirc[i].x;	
				y-= move_dirc[i].y;
				if ( x == move.x && y == move.y)
					break;
				else
					new_board.board[x][y] = tile;
			}
		}
	}
	if(find_flag==1){
		new_board.board[move.x][move.y] = tile;
		new_board.x=move.x;
		new_board.y=move.y;
		new_board.tile=tile;
		new_board.cal_weight(task_your_player);
		new_board_vector.push_back(new_board);
		return;
	}else{
		free_board_mem(new_board.board);	
		return;
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
	// cout<<"children:";	
	// for(vector<Board_info>::iterator child=new_board_vector.begin(); child != new_board_vector.end(); ++child){
	// 	cout<<child->x<<child->y<<",";
	// }
	// cout<<endl;
	return new_board_vector;
}

string Greedy::run_greedy(Board_info &current_board, char your_tile){
	vector<Board_info> new_board_vector;
	vector<Board_info>::iterator it;
	string result="";
	new_board_vector = get_new_boards_vector(your_tile, current_board, your_tile);
	if(new_board_vector.size() != 0){
		sort(new_board_vector.begin(), new_board_vector.end(), compare_max_min);
		result = Board_info::get_board_cells(new_board_vector[0].board);
	}else{
		//can move; do nothing, print old state
		result = Board_info::get_board_cells(current_board.board);
	}
	free_boards(new_board_vector);
	return result;
}

