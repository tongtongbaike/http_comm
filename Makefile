ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
DATA_POOL=$(ROOT_PATH)/data_pool
JSON=$(ROOT_PATH)/lib/include/ 
LINK=$(ROOT_PATH)/lib/lib/
WINDOW=$(ROOT_PATH)/chat_window

SERVER_BIN=udp_server
CLIENT_BIN=udp_client

INCLUDE=-I$(COMM) -I$(DATA_POOL) -I$(WINDOW)
INCLUDE+=-I$(JSON)
CC=g++
FLAGS=-D_DEBUG_ 
LDFLAGS=-lpthread -ljson_cpp #-static
LFLAGS=-L$(LINK)

SER_SRC=$(shell ls -R $(SERVER) | grep -E '*.cpp')
SER_SRC+=$(shell ls -R $(COMM) | grep -E '*.cpp')
SER_SRC+=$(shell ls -R $(DATA_POOL) | grep -E '*.cpp')
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls -R $(CLIENT) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -R $(COMM) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -R $(WINDOW) | grep -E '*.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)
	
$(SERVER_BIN):$(SER_OBJ)
	$(CC) -o $@ $^  $(FLAGS) $(LDFLAGS) $(LFLAGS)  
	@echo "Linking [ $^ ] to [ $@ ] ...done"

$(CLIENT_BIN):$(CLI_OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LDFLAGS) $(LFLAGS) -lncurses 
	@echo "Linking [ $^ ] to [ $@ ] ...done"

%.o:$(COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"

%.o:$(SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"

%.o:$(CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"

%.o:$(DATA_POOL)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"

%.o:$(WINDOW)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [$(shell basename $<) ] to [ $@ ]...done"
.PHONY:clean
clean:
	@rm -f *.o $(SERVER_BIN) $(CLIENT_BIN)
	@echo "clean ... done"

.PHONY:debug
debug:
	@echo $(SER_SRC)
	@echo $(SER_OBJ)

.PHONY:output
output:all
	mkdir -p output/server
	mkdir -p output/server/lib
	mkdir -p output/server/log
	mkdir -p output/server/conf
	mkdir -p ouput/client
	cp -f $(SERVER_BIN) output/server/
	cp -f $(CLIENT_BIN) output/client/
	cp -f $(PLUGIN)/server_ctl.sh output/server/
	cp -f $(PLUGIN)/client_ctl.sh output/client/
	cp -f $(CONF)/server.conf output/server/conf/

#lib
#log
