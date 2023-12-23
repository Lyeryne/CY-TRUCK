OBJ_DIR := H

all: Projet

$(OBJ_DIR)/: .c .h
	gcc -c .c -o $(OBJ_DIR)/.o

$(OBJ_DIR)/: .c .h
	gcc -c .c -o $(OBJ_DIR)/.o


Projet: $(OBJ_DIR)/.o $(OBJ_DIR)/.o 
	gcc $(OBJ_DIR)/.o $(OBJ_DIR)/.o  -o Projet 
