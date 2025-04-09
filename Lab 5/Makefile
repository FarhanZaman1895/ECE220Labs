CC = g++
DEBUG_FLAGS = -ggdb
SRC = ./src
OBJ = ./obj

output: $(OBJ)/main.o
	$(CC) -o output $(OBJ)/main.o $(DEBUG_FLAGS)

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) -c $(SRC)/main.cpp -o $(OBJ)/main.o $(DEBUG_FLAGS)

clean:
	rm output
	rm $(OBJ)/*.o
