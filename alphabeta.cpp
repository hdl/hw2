#include "task.h"
#include "agent.h"
#include "alphabeta.h"
#include "board_info.h"
Board_info Alphabeta::run_alphabeta(Board_info &current_board, int depth, int a, int b, char tile)
{
	Board_info best_child, temp_child;
	vector<Board_info> children;
	vector<Board_info>::iterator child;

	if (depth == 0){
		current_board.visited = 1;
		if(tile == your_tile){
			current_board.a=a;
			current_board.b=current_board.weight;
		}
		else{
			current_board.a=current_board.weight;
			current_board.b=b;
		}
		cout << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< current_board.weight<<",";
		cout << ab2(a, b)<<"-------depth=0"<<endl;
	}else{
		if(current_board.visited==0){
			current_board.visited = 1;
			cout << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<",";
			cout << (tile == your_tile ?"-":"")<<"Infinity,";
			cout <<ab2(a,b) <<"-"<<endl;
		}
	}

	if(depth == 0){
		return current_board;
	}

	children = get_new_boards_vector(your_tile, current_board, tile);
	// it's pocoutible get 0 child
	if(children.size() == 0){
		cout<<"no children"<<endl;
		current_board.print();
		exit(0);
	}else{
		sort(children.begin(), children.end(), compare_order);
	}

	best_child.a = a;
	best_child.b = b;
	if(tile == your_tile){
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_alphabeta(*child, depth -1, best_child.a, best_child.b, other_tile);
			best_child = max_a(best_child, temp_child);
			cout << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< temp_child.weight<<",";
			cout <<ab2(best_child.a,best_child.b)<<"--"<<endl;
		}		
	}else{
		for(child=children.begin(); child != children.end(); ++child){
			temp_child = run_alphabeta(*child, depth -1, best_child.a, best_child.b, your_tile);	
			best_child = min_b(best_child, temp_child);
			cout << xy2(current_board.x, current_board.y)<<","<<this->depth - depth<<","<< temp_child.weight<<",";
			cout <<ab2(best_child.a,best_child.b)<<"---"<<endl;
		}
	}
	free_boards(children);
	//weight is the only var to save/to callee 
	current_board.weight = best_child.weight;
	current_board.best_child_x = best_child.x;	
	current_board.best_child_y = best_child.y;
	if(tile == your_tile)
		current_board.b = best_child.a;
	else
		current_board.a = best_child.b;
	cout << xy2(current_board.x, current_board.y) <<":"<< xy2(current_board.best_child_x, current_board.best_child_y)<<endl;	
	return current_board;
}

Board_info Alphabeta::max_a(Board_info &board1, Board_info &board2)
{
	if(compare_max_a(board1, board2)==1){
		cout <<"keep best_child:"<<xy2(board1.x, board1.y)<<endl;
		return board1;
	}
	else
		return board2;
}

Board_info Alphabeta::min_b(Board_info &board1, Board_info &board2)
{
	if(compare_min_b(board1, board2)==1){
		cout <<"keep best_child:"<<xy2(board1.x, board1.y)<<endl;
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


