# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC = gcc
FLAGS = -Wall -ansi 
SRC_DIR = src
HEADER_DIR = include
BIN_DIR = bin
OBJ = Main.o Stage.o Graphic.o Character.o Treasure.o Object.o Monster.o Inventory.o Save.o

dungeon: $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) -lMLV
	mv *o $(BIN_DIR)
	mv $@ $(BIN_DIR)

Main.o: $(SRC_DIR)/Main.c
	$(CC) -c $< $(FLAGS)

Stage.o: $(SRC_DIR)/Stage.c $(HEADER_DIR)/Stage.h
	$(CC) -c $< $(FLAGS)

Graphic.o: $(SRC_DIR)/Graphic.c $(HEADER_DIR)/Graphic.h
	$(CC) -c $< $(FLAGS)

Character.o: $(SRC_DIR)/Character.c $(HEADER_DIR)/Character.h
	$(CC) -c $< $(FLAGS)

Treasure.o: $(SRC_DIR)/Treasure.c $(HEADER_DIR)/Treasure.h
	$(CC) -c $< $(FLAGS)

Object.o: $(SRC_DIR)/Object.c $(HEADER_DIR)/Object.h
	$(CC) -c $< $(FLAGS)

Monster.o: $(SRC_DIR)/Monster.c $(HEADER_DIR)/Monster.h
	$(CC) -c $< $(FLAGS)	

Inventory.o: $(SRC_DIR)/Inventory.c $(HEADER_DIR)/Inventory.h
	$(CC) -c $< $(FLAGS)	

Save.o: $(SRC_DIR)/Save.c $(HEADER_DIR)/Save.h
	$(CC) -c $< $(FLAGS)
	
clean:
	rm bin/*.o

cleanall:
	rm bin/*