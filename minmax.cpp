#include "task.h"
#include "agent.h"
#include "minmax.h"

board_info Minmax::run_min_max(board_info &current_board, int depth, char tile)
{
	board_info best_child, temp_child;
	vector<board_info> children;
	vector<board_info>::iterator child;
	init_board_info(best_child);
	init_board_info(temp_child);

	if (depth == 0){
		current_board.visited = 1;
		ss << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<endl;
	}else{
		if(current_board.visited==0){
			current_board.visited = 1;
			ss << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			ss << (tile == your_tile ?"-":"")<<"Infinity"<<endl;
		}else{
			ss << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<endl;
		}
	}

	if(depth == 0) // or node is a terminal node
		return current_board;

	children = get_new_boards_vector(current_board, tile);
	// it's possible get 0 child
	sort(children.begin(), children.end(), compare_order);

	if(tile == your_tile){
		best_child.weight = -INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, other_tile);
			best_child = choose_max_child(best_child, temp_child);
			ss << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}		
	}else{
		best_child.weight = INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, your_tile);	
			best_child = choose_min_child(best_child, temp_child);
			ss << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}
	}
	free_boards(children);
	//weight is the only var to save/to callee 
	current_board.weight = best_child.weight;
	current_board.best_child_x = best_child.x;	
	current_board.best_child_y = best_child.y;
	cout << xy2(current_board.best_child_x, current_board.best_child_y)<<endl;	
	return current_board;
}

board_info Minmax::choose_max_child(board_info &board1, board_info &board2)
{
	if(compare_max_min(board1, board2)==1)
		return board1;
	else
		return board2;
}


board_info Minmax::choose_min_child(board_info &board1, board_info &board2)
{
	if(compare_min_max(board1, board2)==1)
		return board1;
	else
		return board2;
}

string Minmax::xy2(int x, int y)
{
	string result="";
	if(x==-1 && y==-1)
		return "root";
	result.append(1, 'a'+y);
	result.append(1, '1'+x);
	return result;	
}

string Minmax::get_next_state(Task &task_info, int x, int y)
{
	string output="";
	int j,k,m;
	char **board;
	board = new char*[GAMESIZE];
	if(!is_on_board(x,y))
		output="is not on board, root?";
	for(j=0; j<GAMESIZE; j++)
		board[j] = new char[GAMESIZE];
	for(k=0; k<8; k++)
		for(m=0; m<8; m++)
			board[k][m] = task_info.cells[k][m];
	board[x][y] = your_tile;
	output = print_only_board(board);
	free_board_mem(board);
	return output;
}
