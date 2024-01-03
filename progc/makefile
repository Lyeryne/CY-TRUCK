OBJ_DIR := fichiers_o

all: Projet

$(OBJ_DIR)/AVL.o: AVL.c AVL.h
	gcc -c AVL.c -o $(OBJ_DIR)/AVL.o

$(OBJ_DIR)/S.o: S.c S.h
	gcc -c S.c -o $(OBJ_DIR)/S.o


Projet: $(OBJ_DIR)/AVL.o $(OBJ_DIR)/S.o 
	gcc $(OBJ_DIR)/AVL.o $(OBJ_DIR)/S.o  -o Projet 
