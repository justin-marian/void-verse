CC = gcc
CFLAGS = -Wall -g

BIN_DIR = BIN
SRC_DIR = ../src

OBJ_DIR = $(BIN_DIR)/OBJECT
DATA_OPERATIONS = $(SRC_DIR)/data_operations
UTILS_DIR = $(SRC_DIR)/utils

.PHONY: clean check checker run build create_dirs

build: create_dirs $(BIN_DIR)/main

create_dirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

$(BIN_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/add.o $(OBJ_DIR)/delete.o $(OBJ_DIR)/find.o
	$(CC) -o $@ $^

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/utils.o: $(UTILS_DIR)/utils.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/add.o: $(DATA_OPERATIONS)/add.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/delete.o: $(DATA_OPERATIONS)/delete.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/find.o: $(DATA_OPERATIONS)/find.c
	$(CC) $(CFLAGS) -c $< -o $@

run: build
	./$(BIN_DIR)/main

checker:
	./checker.py

check: build
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./$(BIN_DIR)/main

clean:
	rm -rf valgrind-out.txt
	rm -rf $(BIN_DIR)
