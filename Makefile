agent: clean agent.o task.o greedy.o minmax.o
	g++ -g -o agent agent.o task.o greedy.o minmax.o
agent.o:
	g++ -g -Wall -c agent.cpp 
task.o:
	g++ -g -Wall -c task.cpp
greedy.o:
	g++ -g -Wall -c greedy.cpp
minmax.o:
	g++ -g -Wall -c minmax.cpp
run:
	./agent
	cat output.txt
clean:
	rm -rf agent *.o
