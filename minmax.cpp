#include "task.h"
#include "agent.h"
#include "minmax.h"
#include "board_info.h"
Board_info Minmax::run_min_max(Board_info &current_board, int depth, char tile)
{
	Board_info best_child, temp_child;
	vector<Board_info> children;
	vector<Board_info>::iterator child;

	children = get_new_boards_vector(your_tile, current_board, tile);
	if (depth == 0 || children.size()==0){
		current_board.visited = 1;
		log << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<endl;
		return current_board;
	}else{
		if(current_board.visited==0){
			current_board.visited = 1;
			log << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			log << (tile == your_tile ?"-":"")<<"Infinity"<<endl;
		}
	}

	children = get_new_boards_vector(your_tile, current_board, tile);
	// it's pologible get 0 child
	sort(children.begin(), children.end(), compare_order);

	if(tile == your_tile){
		best_child.weight = -INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, other_tile);
			best_child = choose_max_child(best_child, temp_child);
			log << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}		
	}else{
		best_child.weight = INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, your_tile);	
			best_child = choose_min_child(best_child, temp_child);
			log << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}
	}
	free_boards(children);
	//weight is the only var to save/to callee 
	current_board.weight = best_child.weight;
	current_board.best_child_x = best_child.x;	
	current_board.best_child_y = best_child.y;
	cout << xy2(current_board.x, current_board.y) << ","<<xy2(current_board.best_child_x, current_board.best_child_y)<<endl;	
	return current_board;
}

Board_info Minmax::choose_max_child(Board_info &board1, Board_info &board2)
{
	if(compare_max_min(board1, board2)==1)
		return board1;
	else
		return board2;
}


Board_info Minmax::choose_min_child(Board_info &board1, Board_info &board2)
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
	else if(x==PASS && y==PASS)
		return "pass";
	result.append(1, 'a'+y);
	result.append(1, '1'+x);
	return result;	
}

string Minmax::get_next_state(Task &task_info, int x, int y, int no_move_flag)
{
	vector<Board_info> new_board_vector;
	vector<Board_info>::iterator it;
	string result="";
	new_board_vector = get_new_boards_vector(your_tile, root_board, your_tile);
	for(it=new_board_vector.begin(); it!=new_board_vector.end(); ++it){
		if(it->x==x &&it->y==y){
			result = Board_info::get_board_cells(it->board);
			free_boards(new_board_vector);
			return result;
		}
	}
	free_boards(new_board_vector);
	return Board_info::get_board_cells(root_board.board);
}
