#include "task.h"
#include "agent.h"
#include "alphabeta.h"
#include "board_info.h"
Board_info Alphabeta::run_alphabeta(Board_info &current_board, int depth, int a, int b, char tile)
{
	Board_info for_match, best_child, temp_child, fake_node;
	vector<Board_info> children;
	vector<Board_info>::iterator child;
	int flip_flag=1;
	Board_info best_weight_child;
	children = get_new_boards_vector(your_tile, current_board, tile);
	if (depth == 0 || game_end(current_board)){
		current_board.visited = 1;
		if(tile == your_tile){
			current_board.a=a;
			current_board.b=current_board.weight;
		}
		else{
			current_board.a=current_board.weight;
			current_board.b=b;
		}
		(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<",";
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

	best_child.a = a;
	best_child.b = b;
	if(tile == your_tile){
		best_weight_child.weight = -INFI;
		for(child=children.begin(); child != children.end(); ++child){
			for_match = best_child;
			temp_child = run_alphabeta(*child, depth -1, best_child.a, best_child.b, other_tile);
			best_child = max_a(best_child, temp_child);
			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			best_weight_child = choose_max_child(best_weight_child, temp_child);
			(DEBUG?cout:log) << best_weight_child.weight<<",";
			if(best_child.b<=best_child.a){
				cout<<"prune form:"<<xy2(best_child.x, best_child.y)<<" ";
				flip_flag = 0;
				(DEBUG?cout:log) <<ab2(for_match.a,for_match.b)<<endl;
				break;
			}else{
				(DEBUG?cout:log) <<ab2(best_child.a,best_child.b)<<endl;
			}
		}
	}else{
		best_weight_child.weight = INFI;
		for(child=children.begin(); child != children.end(); ++child){
			for_match = best_child;
			temp_child = run_alphabeta(*child, depth -1, best_child.a, best_child.b, your_tile);	
			best_child = min_b(best_child, temp_child);
			(DEBUG?cout:log) << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			best_weight_child = choose_min_child(best_weight_child, temp_child);
			(DEBUG?cout:log) << best_weight_child.weight<<",";
			if(best_child.b<=best_child.a){
				cout<<"prune form:"<<xy2(best_child.x, best_child.y)<<" ";
				flip_flag = 0;
				(DEBUG?cout:log) <<ab2(for_match.a,for_match.b)<<endl;
				break;
			}else{
				(DEBUG?cout:log) <<ab2(best_child.a,best_child.b)<<endl;
			}
		}
	}
	free_boards(children);
	//weight is the only var to save/to callee 
	current_board.weight = best_weight_child.weight;
	current_board.best_child_x = best_weight_child.x;	
	current_board.best_child_y = best_weight_child.y;
	if(flip_flag==1){
		if(tile == your_tile)
			current_board.b = best_child.a;
		else
			current_board.a = best_child.b;
	}
	cout << xy2(current_board.x, current_board.y) <<":"<< xy2(current_board.best_child_x, current_board.best_child_y)<<endl;	
	return current_board;
}

Board_info Alphabeta::max_a(Board_info &board1, Board_info &board2)
{
	if(compare_max_a(board1, board2)==1){
		cout<<"give up:"<<xy2(board2.x, board2.y)<<"keep best_child:"<<xy2(board1.x, board1.y)<<endl;
		return board1;
	}
	else
		return board2;
}

Board_info Alphabeta::min_b(Board_info &board1, Board_info &board2)
{
	if(compare_min_b(board1, board2)==1){
		cout<<"give up:"<<xy2(board2.x, board2.y)<<"keep best_child:"<<xy2(board1.x, board1.y)<<endl;
		return board1;
	}
	else
		return board2;
}


int Alphabeta::compare_max_a(const Board_info &board1, const Board_info &board2)
{
	if(board1.a > board2.a)
		return 1;
	else if(board1.a == board2.a)
		return compare_order(board1, board2);
	else
		return 0;
}

int Alphabeta::compare_min_b(const Board_info &board1, const Board_info &board2)
{
	if(board1.b < board2.b)
		return 1;
	else if(board1.b == board2.b)
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


