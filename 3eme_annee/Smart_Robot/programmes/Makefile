# pour les utilisateur du make file 
# commandes disponibles: 
#
#	all : génère le main (les programmes), les tests unitaires, la documentation 
#	tests : génère les tests unitaires 
#   doc : génère la documentation du projet 
#   prg : crée l'exécutable du fichier principal 
#   mainAlgo : compile le main de l'algo situé dans le répertoire Labyrinthe/main.c
#	compileTypes : génère les .o associés aux .c du dossier type
#   compileLaby : génère les .o associés aux .c du dossier Labyrinthe 
#   compilerElec : génère les .o associés aux .c du dossier elec
#   clean : supprime tous les fichiers crées 

# Répertoires sources du projet (ceux que l'on a defini dans larchtecture du programme)
SRCDIR = src
TYPESDIR = src/Types
LabyDIR = src/Labyrinthe
ElecDIR = FonctionsTestsRobot
TESTDIR = src/tests
INCLUDEDIR = include
DOCDIR = docs
ELECDIRSRC = src/elec

PRG = bin/main
BINDIR = bin
DOC = docs
TESTS = tests
algo = bin/algo
BINDIRELEC = bin/elec

# Compilateur gcc et options de debeugage et de warning obligatoires 
CC = gcc
AR = ar
CFLAGS = -Wall -pedantic -g
LDFLAGS = -lcunit -lm -lc -lwiringPi -lwiringPiDev
LDFLAG = -lm -lc -lwiringPi -lwiringPiDev
DOXYGEN = doxygen
INCLUDEALL = -Isrc/elec -Isrc/Types -Iinclude/Types -Iinclude/elec -Iinclude/Labyrinthe

# liste des commandes make : all (compilation totale du sys), tu (pour creer lestes unitaires), clean (pour supprimer les fichiers crees lors des autres étapes)
all: $(PRG) $(DOC)/%.% $(TESTS)/TuType

# sed pour remplacer le .c par .o 
$(PRG): $(shell ls $(ELECDIRSRC)/*.c | sed -e "s/\.c/.o/g" ) $(shell ls $(TYPESDIR)/*.c | sed -e "s/\.c/.o/g" ) $(shell ls $(LabyDIR)/*.c | grep -v main | sed -e "s/\.c/.o/g" ) $(SRCDIR)/main.o $(LabyDIR)/solution.o
	$(CC) -o $(PRG) $(SRCDIR)/main.o $(shell ls $(ELECDIRSRC)/*.c | sed -e "s/\.c/.o/g" ) $(shell ls $(TYPESDIR)/*.c | sed -e "s/\.c/.o/g" ) $(shell ls $(LabyDIR)/*.c | grep -v solution | grep -v main | sed -e "s/\.c/.o/g" ) $(CFLAGS) $(LDFLAG)
	$(CC) -o $(BINDIR)/solution $(LabyDIR)/solution.o $(shell ls $(ELECDIRSRC)/*.c | sed -e "s/\.c/.o/g" ) $(shell ls $(TYPESDIR)/*.c | sed -e "s/\.c/.o/g" ) $(shell ls $(LabyDIR)/*.c | grep -v solution | grep -v main | sed -e "s/\.c/.o/g" ) $(CFLAGS) $(LDFLAG) 

prg: $(PRG)

# généralisation de règle .C --> .o 
%.o : %.c 
	$(CC) $(CFLAGS) $(INCLUDEALL) -c $< -o $@

doc: $(DOC)/%.%


$(DOC)/%.% : $(DOCDIR)
	$(DOXYGEN)

elec : 
	for file in $(shell ls $(ElecDIR)/*.c | cut -d '/' -f "3");do \
		$(CC) -c $(ElecDIR)/$$file $(CFLAGS) -I$(INCLUDEDIR) -I$(INCLUDEDIR)/Types -I$(INCLUDEDIR)/Labyrinthe -I$(INCLUDEDIR)/elec -o $(ElecDIR)/$${file%.c}.o;\
	done 
	for file in $(shell ls $(ElecDIR)/*.c | cut -d '/' -f "3");do \
		$(CC) $(ElecDIR)/$${file%.o}.o $(LDFLAGS) -o $(BINDIRELEC)/$${file%.o};\
	done 




# Compilation des tests unitaires
tests: $(TESTS)/TuType

$(TESTS)/TuType: $(TESTDIR)/TuType.o $(shell ls $(TYPESDIR)/*.c | sed -e "s/\.c/.o/g" )
	$(CC) $(TESTDIR)/TuType.o $(LDFLAGS) $(TYPESDIR)/*.o -o $(TESTS)/TuType


$(TESTDIR)/TuType.o : $(TESTDIR)/TuType.c
	$(CC) -c $(TESTDIR)/TuType.c $(CFLAGS) -I$(INCLUDEDIR) -I$(INCLUDEDIR)/Types -o $(TESTDIR)/TuType.o




mainAlgo : $(algo)/*

$(algo)/* : $(LabyDIR)/main.o
	
	$(CC)  -o $(algo)/main  $(TYPESDIR)/*.o $(LabyDIR)/*.o $(LDFLAG)

$(LabyDIR)/main.o : $(LabyDIR)/main.c
	for file in $(shell ls $(TYPESDIR)/*.c | cut -d '/' -f "3");do \
		$(CC) -c $(TYPESDIR)/$$file $(CFLAGS) -I$(INCLUDEDIR) -I$(INCLUDEDIR)/Types -I$(INCLUDEDIR)/Labyrinthe -o $(TYPESDIR)/$${file%.c}.o;\
	done 
	for file in $(shell ls $(LabyDIR)/*.c | cut -d '/' -f "3" | grep -v 2);do \
		$(CC) -c $(LabyDIR)/$$file $(CFLAGS) -I$(INCLUDEDIR) -I$(INCLUDEDIR)/Types -I$(INCLUDEDIR)/Labyrinthe -o $(LabyDIR)/$${file%.c}.o;\
	done 
# grep -v 2 pour ne pas prendre en compte le fichier main2 sinon on a 2 fonctions main dans les fichier , le compilateur n'aime pas ça 


compileTypes: 
# obligé de faire une boucle dnas le language shell pour recuperer tous les fichiers de Types.c  
	for file in $(shell ls $(TYPESDIR)/*.c | cut -d '/' -f "3");do \
		$(CC) -c $(TYPESDIR)/$$file $(CFLAGS) -I$(INCLUDEDIR) -I$(INCLUDEDIR)/Types -I$(INCLUDEDIR)/Labyrinthe -o $(TYPESDIR)/$${file%.c}.o;\
	done 

compileLaby: 
# obligé de faire une boucle dnas le language shell pour recuperer tous les fichiers de Types.c  
	for file in $(shell ls $(LabyDIR)/*.c | cut -d '/' -f "3");do \
		$(CC) -c $(LabyDIR)/$$file $(CFLAGS) -I$(INCLUDEDIR) -I$(INCLUDEDIR)/Types -I$(INCLUDEDIR)/Labyrinthe -o $(LabyDIR)/$${file%.c}.o;\
	done 
# compilation generalisee cf derniere page de cours 

compileElec: 
# obligé de faire une boucle dnas le language shell pour recuperer tous les fichiers de Types.c  
	for file in $(shell ls $(ElecDIR)/*.c | cut -d '/' -f "3");do \
		$(CC) -c $(ElecDIR)/$$file $(CFLAGS) -I$(INCLUDEDIR) -I$(INCLUDEDIR)/Types -I$(INCLUDEDIR)/Labyrinthe -I$(INCLUDEDIR)/elec -o $(ElecDIR)/$${file%.c}.o;\
	done 
# compilation generalisee cf derniere page de cours 


clean:
	rm -f $(TESTDIR)/*.o
	rm -rf $(DOCDIR)/*
	rm -f bin/algo/main
	rm -f bin/elec/*
	rm -f tests/TuType
	rm -f bin/main
	rm -f src/*.o
	rm -f src/tests/*.o
	rm -f src/Types/*.o
	rm -f src/Labyrinthe/*.o
	rm -f src/elec/*.o
