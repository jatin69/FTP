CXX=g++
CFLAGS=-std=c++17 -Wall -Wextra -Wno-unused-variable -Wno-unused-but-set-variable

SRC_SERVER=$(shell find ./src/server -name "*.cpp")
SRC_CLIENT=$(shell find ./src/client -name "*.cpp")
SRC_UTILS=$(shell find ./src/utils -name "*.cpp")

OBJ_SERVER=$(subst .cpp,.o,$(SRC_SERVER))
OBJ_CLIENT=$(subst .cpp,.o,$(SRC_CLIENT))
OBJ_UTILS=$(subst .cpp,.o,$(SRC_UTILS))

all: server client

server: $(OBJ_SERVER) $(OBJ_UTILS) src/server/server.hpp
	$(CXX) $(CFLAGS) -c -o src/server/main.o src/server/main.cpp
	$(CXX) $(CFLAGS) -o server $(OBJ_SERVER) $(OBJ_UTILS)

client: $(OBJ_CLIENT) $(OBJ_UTILS) src/client/client.hpp
	$(CXX) $(CFLAGS) -o client $(OBJ_CLIENT) $(OBJ_UTILS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

clean: clean-client clean-server
	rm -rf $(shell find . -name "*.o")

clean-client:
	rm -rf $(shell find src/client -name "*.o")
	rm -f ./client

clean-server:
	rm -rf $(shell find src/server -name "*.o")
	rm -f ./server