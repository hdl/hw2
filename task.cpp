#include "task.h"
#include "agent.h"
using namespace std;

Task::Task(const string &inputFileName)
{
	int i=0, j=0;
	string line;
	fstream inputFile;
	inputFile.open(inputFileName.c_str());

	getline(inputFile, line);
	task_no = atoi(line.c_str());
	getline(inputFile, line);
	your_player = line[0]; 
	getline(inputFile, line);
	cut_off_depth = atoi(line.c_str());
	for(i = 0; i < GAMESIZE; i++){
	    getline(inputFile, line);
		for(j = 0; j < GAMESIZE; j++){
			cells[i][j] = line.c_str()[j];
		}
	}
	inputFile.close();
}

void Task::PrintTaskInfo()
{
	int i, j;
	cout << task_no << endl;
	cout << your_player << endl;
	cout << cut_off_depth << endl;
	for(i = 0; i < GAMESIZE; i++){
		for(j = 0; j < GAMESIZE; j++){
			cout << cells[i][j];
		}
		cout << endl;
	}
}
