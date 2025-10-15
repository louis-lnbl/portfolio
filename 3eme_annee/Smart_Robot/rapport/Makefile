# pour les utilisateur du make file 
# commandes disponibles: 
#
#	all : génère le rapport Latex
#   doc : fait la même chose

all: rapport.pdf

doc: rapport.pdf

# on fait 2x la compilation vu que à la premiere compilation on créer le .out (definit les bookmark) et a la 2eme on l'utilise sinon on a pas de table des matière 
rapport.pdf : rapport.tex
	pdflatex rapport.tex
	pdflatex rapport.tex

clean:
	rm -f rapport.pdf
	rm -f rapport.aux
	rm -f rapport.log
	rm -f rapport.toc
	rm -f rapport.out
	
