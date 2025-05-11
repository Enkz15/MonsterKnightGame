# Définition des variables
CC = gcc
CFLAGS = -c -Wall
EXEC = sae
TEST_EXEC = test 
SRC = src/
SRCTEST = src/Test/
OBJTEST = $(SRCTEST)main.o $(SRC)chevalier.o $(SRC)monstres.o $(SRC)jeu.o $(SRC)menu.o $(SRCTEST)test.o
OBJ = $(SRC)main.o $(SRC)chevalier.o $(SRC)monstres.o $(SRC)jeu.o $(SRC)menu.o

all : $(EXEC) $(TEST_EXEC)

# Cible pour compiler le programme principal
$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

# Cible pour compiler le programme de test
$(TEST_EXEC): $(OBJTEST)
	$(CC) -o $(TEST_EXEC) $(OBJTEST)

# Cible pour générer les fichiers objets
$(SRC)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ $<

# Cible pour générer les fichiers objets de test
$(SRCTEST)%.o: $(SRCTEST)%.c
	$(CC) $(CFLAGS) -o $@ $<


# Cible pour générer la documentation Doxygen
doc:
	@if [ ! -e Doxyfile ]; then doxygen -g; fi
	doxygen

# Cible pour nettoyer
clean:
	rm -rf $(SRC)*.o
	rm -rf $(SRCTEST)*.o
	rm -rf html latex
	rm -f $(EXEC) $(TEST_EXEC)


# Aide à la compréhension :
#% reviens à * mais avec un ordre de dépendance 
#-o $@ $< : placer dans un fichier le chemin complet de l'objet cible(.o) mais avec sa source (.c)
