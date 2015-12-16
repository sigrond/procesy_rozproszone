FILES = server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp Slave.cpp Task.cpp ../protocol/Message.cpp
Debug: $(FILES)
	g++ -std=c++11 -g -O0 -D_DEBUG -Wall -pthread -lpthread -o bin/Debug/server $(FILES)

cleanDebug:
	rm -f bin/Debug/server

Release: server

server: $(FILES)
	g++ -std=c++11 -Wall -pthread -lpthread -o server $(FILES)

run: server
	./server

clean:
	rm -f server

all: clean server run

.PHONY: run clean all Release cleanDebug
