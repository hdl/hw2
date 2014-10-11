#ifndef TASK_H
#define TASK_H
#include "agent.h"
using namespace std;
#define GAMESIZE 8
class Task
{
public: 
    int task_no;
    char your_player;
    int cut_off_depth;
    char cells[GAMESIZE][GAMESIZE];
    ofstream outputFile;
    Task(const string &inputFileName);
    void PrintTaskInfo();
};
extern Task * task_info_p;

#endif
