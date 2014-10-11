agent: clean agent.o task.o
	g++ -g -o agent agent.o task.o
agent.o:
	g++ -g -Wall -c agent.cpp 
task.o:
	g++ -g -Wall -c task.cpp
run:
	./agent
	cat output.txt
clean:
	rm -rf agent *.o
