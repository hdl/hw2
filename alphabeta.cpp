#include "task.h"
#include "agent.h"
#include "alphabeta.h"
#include "board_info.h"
Board_info Alphabeta::run_alphabeta(Board_info &current_board, int depth, int a, int b, char tile)
{
	Board_info for_match, v, temp_child, fake_node;
	vector<Board_info> children;
	vector<Board_info>::iterator child;
	Board_info best_weight_child;
	children = get_new_boards_vector(your_tile, current_board, tile);
	cout<<xy2(current_board.x, current_board.y)<<"'s children:";
	for(child=children.begin(); child != children.end(); ++child){
		cout<<xy2(child->x,child->y)<<",";
	}
	cout<<endl;
	if (depth == 0 || game_end(current_board)){
		current_board.v=current_board.weight;
		(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.v<<",";
		(DEBUG?cout:log) << ab2(a, b)<<endl;
		return current_board;
	}else{
		if(current_board.visited==0){
			current_board.visited = 1;
			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			(DEBUG?cout:log) << (tile == your_tile ?"-":"")<<"Infinity,";
			(DEBUG?cout:log) <<ab2(a,b) <<endl;
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
	}else{
		pass2_flag.push_back(0);
		sort(children.begin(), children.end(), compare_order);
	}
	// if(current_board.x==PASS && current_board.y==PASS){
	// 	if(tile == your_tile)
	// 		tile = other_tile;
	// 	else
	// 		tile = your_tile;
	// }

	if(tile == your_tile){
		v.v= -INFI;
		for(child=children.begin(); child != children.end(); ++child){
			if(current_board.x==PASS && current_board.y==PASS)
				temp_child = run_alphabeta(*child, depth -1, a, b, your_tile);
			else //normally
				temp_child = run_alphabeta(*child, depth -1, a, b, other_tile);
			v = max_v(v, temp_child);
			if(v.v>=b){
			    (DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			    (DEBUG?cout:log) << v.v<<",";
			    (DEBUG?cout:log) <<ab2(a,b)<<endl;
				goto END;
			}
			a = max(a, v.v);

			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			(DEBUG?cout:log) << v.v<<",";
			(DEBUG?cout:log) <<ab2(a,b)<<endl;

		}
	}else{
		v.v= INFI;
		for(child=children.begin(); child != children.end(); ++child){
			if(current_board.x==PASS && current_board.y==PASS)
				temp_child = run_alphabeta(*child, depth -1, a, b, your_tile);
			else
				temp_child = run_alphabeta(*child, depth -1, a, b, other_tile);
			v = min_v(v, temp_child);
			if(v.v<=a){
				(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
				(DEBUG?cout:log) << v.v<<",";
				(DEBUG?cout:log) << ab2(a,b) <<endl;
				goto END;
			}
			b = min(b, v.v);

			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			(DEBUG?cout:log) << v.v<<",";
			(DEBUG?cout:log) <<ab2(a,b)<<endl;
			
		}
	}

END:
	free_boards(children);
	return v;
}

Board_info Alphabeta::max_v(Board_info &board1, Board_info &board2)
{
	if(compare_max_v(board1, board2)==1){
		cout<<"give up:"<<xy2(board2.x, board2.y)<<"keep best_child:"<<xy2(board1.x, board1.y)<<endl;
		return board1;
	}
	else
		return board2;
}

Board_info Alphabeta::min_v(Board_info &board1, Board_info &board2)
{
	if(compare_min_v(board1, board2)==1){
		cout<<"give up:"<<xy2(board2.x, board2.y)<<"keep best_child:"<<xy2(board1.x, board1.y)<<endl;

		return board1;
	}
	else
		return board2;
}


int Alphabeta::compare_max_v(const Board_info &board1, const Board_info &board2)
{
	if(board1.v > board2.v)
		return 1;
	else if(board1.v == board2.v)
		return compare_order(board1, board2);
	else
		return 0;
}

int Alphabeta::compare_min_v(const Board_info &board1, const Board_info &board2)
{
	if(board1.v < board2.v)
		return 1;
	else if(board1.v == board2.v)
		return compare_order(board1, board2);
	else
		return 0;
}

string Alphabeta::ab2(int a, int b)
{
	string result="";
	if(a==-INFI)
		result="-Infinity,";
	else if(a==INFI)
		result="Infinity,";
	else
		result=to_string(a)+",";

	if(b==-INFI)
		result+="-Infinity";
	else if(b==INFI)
		result+="Infinity";
	else
		result+=to_string(b);

	return result;
}

Board_info Alphabeta::run_min_max(Board_info &current_board, int depth, char tile)
{
	Board_info best_child, temp_child, fake_node;
	vector<Board_info> children;
	vector<Board_info>::iterator child;

	children = get_new_boards_vector(your_tile, current_board, tile);
	if (depth == 0 || game_end(current_board)==1){
		current_board.visited = 1;
		return current_board;
	}else{
		if(current_board.visited==0){
			current_board.visited = 1;
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
	}else{
		pass2_flag.push_back(0);
		sort(children.begin(), children.end(), compare_order);
	}

	if(tile == your_tile){
		best_child.weight = -INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, other_tile);
			best_child = choose_max_child(best_child, temp_child);
		}		
	}else{
		best_child.weight = INFI;
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_min_max(*child, depth -1, your_tile);	
			best_child = choose_min_child(best_child, temp_child);
		}
	}
	free_boards(children);
	//weight is the only var to save/to callee 
	current_board.weight = best_child.weight;
	current_board.best_child_x = best_child.x;
	current_board.best_child_y = best_child.y;
	return current_board;
}


