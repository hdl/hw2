#include "task.h"
#include "agent.h"
#include "greedy.h"
#include "minmax.h"
#include "alphabeta.h"

int DEBUG=0;
int weights[GAMESIZE][GAMESIZE]={
	{99, -8, 8, 6, 6, 8, -8, 99},
	{-8, -24, -4, -3, -3, -4, -24, -8},
	{8, -4, 7, 4, 4, 7, -4, 8},
	{6, -3, 4, 0, 0, 4, -3, 6},
	{6, -3, 4, 0, 0, 4, -3, 6},
	{8, -4, 7, 4, 4, 7, -4, 8},
	{-8, -24, -4, -3, -3, -4, -24, -8},
	{99, -8, 8, 6, 6, 8, -8, 99}
};

coord move_dirc[8] = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};
string minmax_prompt="Node,Depth,Value\n";
string alphabeta_prompt="Node,Depth,Value,Alpha,Beta\n";

int main()
{
	Task task_info("input.txt");
	ofstream output_file("output.txt",ofstream::out);
	task_info.PrintTaskInfo();
	Board_info next_state;
	if (task_info.task_no == 1){
		Greedy greedy;
		greedy.init(task_info);
		output_file<<greedy.run_greedy(greedy.root_board, task_info.your_player);
	}else if(task_info.task_no==2){
		Minmax minmax;
		minmax.init(task_info);
	    next_state=minmax.run_min_max(minmax.root_board, minmax.depth, minmax.your_tile);
		output_file<<minmax.get_next_state(task_info, next_state.best_child_x, next_state.best_child_y);
		output_file<<minmax_prompt;
		output_file<<minmax.log.str();
	}else if(task_info.task_no==3){
		Alphabeta alphabeta;
		alphabeta.init(task_info);
	    next_state=alphabeta.run_alphabeta(alphabeta.root_board, alphabeta.depth, -INFI, INFI, alphabeta.your_tile);
		output_file<<alphabeta.get_next_state(task_info, next_state.best_child_x, next_state.best_child_y);
		output_file<<alphabeta_prompt;
		output_file<<alphabeta.log.str();
	}
	output_file.close();
	// while(1);
	return (0); 
}


int compare_max_min(const Board_info &board1, const Board_info &board2)
{
	if(board1.weight > board2.weight)
		return 1;
	else if(board1.weight == board2.weight)
		return compare_order(board1, board2);
	else
		return 0;
}

int compare_min_max(const Board_info &board1, const Board_info &board2)
{
	if(board1.weight < board2.weight)
		return 1;
	else if(board1.weight == board2.weight)
		return compare_order(board1, board2);
	else
		return 0;
}

int compare_order(const Board_info &board1, const Board_info &board2)
{
	if(board1.x<board2.x)
		return 1;
	else if(board1.x==board2.x){
		if(board1.y<=board2.y)
			return 1;
		else
			return 0;	
	}else
		return 0;
}

void free_board_mem(char **board)
{
	for (int j = 0; j < 8 ; j++)
		delete[] board[j];
	delete[] board;
}

void free_boards(vector<Board_info> &new_board_vector)
{
	int count = 0;
	for(vector<Board_info>::iterator it=new_board_vector.begin(); it!=new_board_vector.end(); ++it){
		free_board_mem(it->board);
		count++;
	}
	cout << count << "boards are freed"<<endl;
}
