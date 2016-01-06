CXX=g++
CXXFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -pthread -g -I.
LFLAGS=-lboost_system -lpthread

RELATIVE=./

CMD=$(CXX) $(CXXFLAGS) $(LFLAGS) $^ -o

OBJS = ConnectionManager.o Connection.o Socket.o SocketException.o Message.o Ip.o Address.o

all: server client

debug_m: CXXFLAGS += -DDEBUG_M
debug_m: all

debug: CXXFLAGS += -DDEBUG
debug: all

server: server.o $(OBJS)
	mkdir -p stest
	$(CMD) ./stest/$@

client: client.o $(OBJS)
	mkdir -p ctest
	echo "ALL UR BASE ARE BELONG TO US" > ./ctest/testfile
	$(CMD) ./ctest/$@

clean:
	rm -f *.o
	rm -f ./stest/testfile

.PHONY: all clean
