SRC=Flood-It.c API_Gene_instance.c API_Grille.c Liste_case.c Sequence_aleatoire.c Bordure.c Strategies_pilotees.c Graphe_zone.c
GCC_FLAGS = -lSDL 
CFLAGS=-g -Wall

CC=gcc


all : Flood-It 

Flood-It : $(SRC:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^ $(GCC_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(GCC_FLAGS)






Sequence_aleatoire.o : Sequence_aleatoire.c Sequence_aleatoire.h API_Grille.h Liste_case.h

API_Gene_instance.o : API_Gene_instance.c API_Gene_instance.h

Liste_case.o : Liste_case.c Liste_case.h

API_Grille.o : API_Grille.c API_Grille.h

Flood-It.o : Flood-It.c API_Gene_instance.h API_Grille.h Sequence_aleatoire.h Liste_case.h Strategies_pilotees.h Bordure.h Graphe_zone.h
		
Bordure.o : Bordure.c Bordure.h Liste_case.h

Strategies_pilotees.o : Strategies_pilotees.c Strategies_pilotees.h API_Grille.h Liste_case.h

Graphe_zone.o : Graphe_zone.c Graphe_zone.h 

clean : 
	rm -f *.o Flood-It *~ *#

