#include "task.h"
#include "agent.h"
#include "minmax.h"

void Minmax::init(Task &task_info)
{
	depth = task_info.cut_off_depth;

	Greedy::init(task_info);
}

board_info Minmax::run_min_max(board_info &current_board, int depth, char tile)
{
	board_info best_child, temp_child;
	char ** bt_save; //for backtrace, save best_child board
	vector<board_info> children;
	vector<board_info>::iterator child;

	if (depth == 0){
		current_board.visited = 1;
		cout << tile << ","<< xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<endl;
	}else{
		if(current_board.visited==0){
			current_board.visited = 1;
			cout << tile << ","<< xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< "Infinity"<<endl;
		}else{
			cout << tile << ","<< xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<endl;
		}
	}

	if(depth == 0) {// or node is a terminal node{
		return current_board;
	}

	children = get_new_boards_vector(current_board, tile);
	sort(children.begin(), children.end(), compare_order);

	if(tile == your_tile){
		best_child.weight = -INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, other_tile);	
			best_child = choose_max_child(best_child, temp_child);
			cout << tile << ","<< xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}		
	}else{
		best_child.weight = INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, your_tile);	
			best_child = choose_min_child(best_child, temp_child);
			cout << tile << ","<< xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}
	}

	//print_board(best_child);

	// allocate new mem for best board, then free children
	// the most important is to free the best childs in the end	
	bt_save = new char*[GAMESIZE];
	for(int j=0; j<GAMESIZE; j++)
		bt_save[j] = new char[GAMESIZE];
	for(int k=0; k<8; k++)
		for(int m=0; m<8; m++)
			bt_save[k][m] = best_child.board[k][m];
	//change best_child pointer
	best_child.board=bt_save;
	board_in_depth.insert(board_in_depth.begin(), best_child);	
	free_boards(children);		
	return best_child;
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
		if(x==0 && y==0)
			return "root";
		result.append(1, 'a'+y);
		result.append(1, '1'+x);
		return result;	
	}

