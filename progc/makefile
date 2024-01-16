OBJ_DIR := fichiers_o
CFLAGS = -g -Wall

all: Projet

$(OBJ_DIR)/AVL_S.o: AVL_S.c AVL_S.h
	gcc -c AVL_S.c -o $(OBJ_DIR)/AVL_S.o

$(OBJ_DIR)/S.o: S.c S.h
	gcc -c S.c -o $(OBJ_DIR)/S.o

#$(OBJ_DIR)/AVL_T.o: AVL_T.c AVL_T.h
#	gcc -c AVL_T.c -o $(OBJ_DIR)/AVL_T.o

#$(OBJ_DIR)/T.o: T.c T.h
#	gcc -c T.c -o $(OBJ_DIR)/T.o


Projet: $(OBJ_DIR)/AVL_S.o $(OBJ_DIR)/S.o #$(OBJ_DIR)/AVL_T.o $(OBJ_DIR)/T.o 
	gcc $(CFLAGS) $(OBJ_DIR)/AVL_S.o $(OBJ_DIR)/S.o -o Projet -lm 
#$(OBJ_DIR)/AVL_T.o $(OBJ_DIR)/T.o  
