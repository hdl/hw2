#include "task.h"
#include "agent.h"
#include "minmax.h"
#include "board_info.h"
Board_info Minmax::run_min_max(Board_info &current_board, int depth, char tile)
{
	Board_info best_child, temp_child, fake_node;
	vector<Board_info> children;
	vector<Board_info>::iterator child;

	children = get_new_boards_vector(your_tile, current_board, tile);
	cout<<"children::";
	for(child=children.begin(); child != children.end(); ++child){
		cout<<xy2(child->x, child->y)<<",";
	}
	cout<<endl;
	if (depth == 0 || game_end(current_board)==1){
		current_board.visited = 1;
		(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<endl;
		return current_board;
	}else{
		if(current_board.visited==0){
			current_board.visited = 1;
			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			(DEBUG?cout:log) << (tile == your_tile ?"-":"")<<"Infinity"<<endl;
		}
	}
	if (children.size()==0){
		//fake pass node
		pass2_flag.push_back(1);
		children.clear();
		fake_node = current_board.clone();
		fake_node.x=PASS;
		fake_node.y=PASS;
		fake_node.visited = 0;
		children.push_back(fake_node);
		cout <<"fake..."<<xy2(fake_node.x, fake_node.y);
	}else{
		pass2_flag.push_back(0);
		sort(children.begin(), children.end(), compare_order);
	}

	if(tile == your_tile){
		best_child.weight = -INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, other_tile);
			best_child = choose_max_child(best_child, temp_child);
			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}		
	}else{
		best_child.weight = INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, your_tile);	
			best_child = choose_min_child(best_child, temp_child);
			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< best_child.weight<<endl;
		}
	}
	free_boards(children);
	//weight is the only var to save/to callee 
	current_board.weight = best_child.weight;
	current_board.best_child_x = best_child.x;
	current_board.best_child_y = best_child.y;
	cout << xy2(current_board.x, current_board.y) << "::::"<<xy2(current_board.best_child_x, current_board.best_child_y)<<endl;	
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

string Minmax::get_next_state(Task &task_info, int x, int y)
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
