# Nom du compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Liste de tous tes fichiers sources (.c)
SRC = main.c jeu.c pile.c matrice.c genAlgo.c

# Transformation automatique de la liste des .c en .o
OBJ = $(SRC:.c=.o)

# Nom du programme final
EXEC = othello

# Règle principale
all: $(EXEC)

# Règle d'édition de liens (création de l'exécutable)
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Règle de compilation des fichiers objets (.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers temporaires
clean:
	rm -f $(OBJ) $(EXEC)