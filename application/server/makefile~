Debug: server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp
	g++ -std=c++11 -g -O0 -D_DEBUG -Wall -o bin\Debug\server server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp

Release: server

server: server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp
	g++ -std=c++11 -Wall -o server server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp

run: server
	./server

clean:
	rm -f server

all: clean server run

.PHONY: run clean all Release
