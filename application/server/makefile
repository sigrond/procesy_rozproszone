CXX = g++
FILES = server.cpp Controller.cpp AdminServer.cpp AgentServer.cpp Model.cpp Slave.cpp Task.cpp ../protocol/Message.cpp ../protocol/Ip.cpp ../protocol/Connection.cpp ../protocol/ConnectionManager.cpp ../protocol/Socket.cpp ../protocol/SocketException.cpp ../protocol/Address.cpp
LFLAGS = -lpthread
DFLAGS = -g -Og -D_DEBUG -DDEBUG
CPPFLAGS = -std=c++11 -Wall -pthread -MMD -MP
OBJECTS = $(FILES:.cpp=.o)

#Debug: $(FILES)
#	$(CXX) $(DFLAGS) $(CFLAGS) $(LFLAGS) -o bin/Debug/server $(FILES)

Debug:
	mkdir -p ./bin/Debug
Debug: CPPFLAGS+=$(DFLAGS)
Debug: $(FILES:%.cpp=%.o)
	$(CXX) $(CPPFLAGS) $(LFLAGS) -o bin/Debug/server $^

-include $(FILES:%.cpp=%.d)

#Debug: $(OBJECTS)
#	$(CXX) $(DFLAGS) $(CFLAGS) $(LFLAGS) -o bin/Debug/server $(OBJECTS)

cleanDebug:
	rm -f bin/Debug/server
	rm -f bin/Debug/*.o
	rm -f bin/Debug/*.d
	rm -f *.o
	rm -f *.d
	rm -f ../protocol/*.o
	rm -f ../protocol/*.d

#Release: server
#
#server: $(FILES)
#	$(CXX) $(CFLAGS) -o server $(FILES)

# do szybszej kompilacji konieczne wygenerowanie listy zaleznosci
#%.o : %.cpp
#	$(CXX) $(DFLAGS) $(CFLAGS) $< -o $@
#	$(CXX) $(DFLAGS) $(CFLAGS) -MD -MP bin/Debug/$*.d $<

#-include $(OBJECTS:)bin/Debug/$*.d

#run: server
#	./server

#clean:
#	rm -f server

#all: clean server run

.PHONY: run clean all Release cleanDebug
