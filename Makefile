agent: clean agent.o task.o greedy.o minmax.o board_info.o alphabeta.o
	g++ -g -o agent agent.o task.o greedy.o minmax.o board_info.o alphabeta.o
agent.o:
	g++ -g -Wall -c agent.cpp 
task.o:
	g++ -g -Wall -c task.cpp
greedy.o:
	g++ -g -Wall -c greedy.cpp
minmax.o:
	g++ -g -Wall -c minmax.cpp
alphabeta.o:
	g++ -g -Wall -c alphabeta.cpp
board_info.o:
	g++ -g -Wall -c board_info.cpp
run:
	./agent
clean:
	rm -rf agent *.o
