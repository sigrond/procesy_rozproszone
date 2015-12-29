CXX = g++
FILES = server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp Slave.cpp Task.cpp ../protocol/Message.cpp ../protocol/Ip.cpp ../protocol/Connection.cpp ../protocol/ConnectionManager.cpp ../protocol/Socket.cpp ../protocol/SocketException.cpp
CFLAGS = -std=c++11 -Wall -pthread -MD -MP
LFLAGS = -lpthread
DFLAGS = -g -O0 -D_DEBUG -DDEBUG
OBJECTS = $(FILES:.cpp=.o)

Debug: $(FILES)
	$(CXX) $(DFLAGS) $(CFLAGS) $(LFLAGS) -o bin/Debug/server $(FILES)

cleanDebug:
	rm -f bin/Debug/server

Release: server

server: $(FILES)
	$(CXX) $(CFLAGS) -o server $(FILES)

# do szybszej kompilacji konieczne wygenerowanie listy zaleznosci
# %.o : %.cpp
# 	$(CXX) $(DFLAGS) $(CFLAGS) $<

run: server
	./server

clean:
	rm -f server

all: clean server run

.PHONY: run clean all Release cleanDebug
