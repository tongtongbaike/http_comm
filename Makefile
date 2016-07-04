ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm

SERVER_BIN=udp_server
CLIENT_BIN=udp_client

INCLUDE=-I$(COMM)
cc=g++
FLAGS=
LDFALGS=-static

SER_SRC=$(shell ls -R $(SERVER) | grep -E '*.cpp')
SER_SRC+=$(shell ls -R $(COMM) | grep -E '*.cpp')
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls -R $(CLIENT) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -R $(COMM) | grep -E '*.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)
	
$(SERVER_BIN):$(SER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Linking [ $^ ] to [ $@ ] ...done"

$(CLIENT_BIN):$(CLI_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Linking [ $^ ] to [ $@ ] ...done"

%.o:$(COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"

%.o:$(SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"

%.o:$(CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"

.PHONY:clean
clean:
	@rm -f *.o $(SERVER_BIN) $(CLIENT_BIN)
	@echo "clean ... done"

.PHONY:debug
debug:
	@echo $(SER_SRC)
	@echo $(SER_OBJ)
