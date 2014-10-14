#include "task.h"
#include "agent.h"
#include "greedy.h"

int wetights[GAMESIZE][GAMESIZE]={
	{99, -8, 8, 6, 6, 8, -8, 99},
	{-8, -24, -4, -3, -3, -4, -24, -8},
	{8, -4, 7, 4, 4, 7, -4, 8},
	{6, -3, 4, 0, 0, 4, -3, 6},
	{6, -3, 4, 0, 0, 4, -3, 6},
	{8, -4, 7, 4, 4, 7, -4, 8},
	{-8, -24, -4, -3, -3, -4, -24, -8},
	{99, -8, 8, 6, 6, 8, -8, 99}
};


int main()
{
	Task task_info("input.txt");
	task_info.PrintTaskInfo();
	// if (task_info.task_no == 1){
		Greedy greedy;
		greedy.get_new_boards_vector(task_info.cells, task_info.your_player);
	// }
	return (0); 
}
