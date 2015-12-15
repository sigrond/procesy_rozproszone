Debug: server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp
	g++ -std=c++11 -g -O0 -D_DEBUG -Wall -pthread -lpthread -o bin/Debug/server server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp

cleanDebug:
	rm -f bin/Debug/server

Release: server

server: server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp
	g++ -std=c++11 -Wall -pthread -lpthread -o server server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp

run: server
	./server

clean:
	rm -f server

all: clean server run

.PHONY: run clean all Release cleanDebug
