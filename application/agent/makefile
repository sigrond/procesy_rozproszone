CXX = g++
FILES = Agent.cpp AgentClient.cpp Command.cpp MessageParser.cpp ../protocol/Message.cpp ../protocol/Ip.cpp ../protocol/Connection.cpp ../protocol/ConnectionManager.cpp ../protocol/Socket.cpp ../protocol/SocketException.cpp ../protocol/Address.cpp
LFLAGS = -lpthread -lboost_system
DFLAGS = -g -Og -D_DEBUG -DDEBUG -DDEBUG_M
CPPFLAGS = -std=c++11 -Wall -pthread -MMD -MP
OBJECTS = $(FILES:.cpp=.o)

Debug:
	mkdir -p ./bin/Debug
Debug: CPPFLAGS+=$(DFLAGS)
Debug: $(FILES:%.cpp=%.o)
	$(CXX) $(CPPFLAGS) $(LFLAGS) -o bin/Debug/agent $^

-include $(FILES:%.cpp=%.d)

cleanDebug:
	rm -f bin/Debug/server
	rm -f bin/Debug/konsola
	rm -f bin/Debug/agent
	rm -f bin/Debug/*.o
	rm -f bin/Debug/*.d
	rm -f *.o
	rm -f *.d
	rm -f ../protocol/*.o
	rm -f ../protocol/*.d

.PHONY: cleanDebug
