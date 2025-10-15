#!/bin/bash

echo "Scipt Bash lancée "
echo ""

RESULTAT=0
nomTXT=$1

# reconnaissance du fichier txt a inclure dans le projet tant que on l'a pas détecté, on le cherche on demande a l'utilisateur de le retaper (cela ne compte pas pour le temps)
echo $nomTXT
(ls $nomTXT > /dev/null 2>&1) && echo "fichier trouvé, passage en argument pour la fonction main" && RESULTAT=1 #apres le pipe permet de masquer la commande dans le terminal uniquement si il n'y a pas d'erreur 
if [[ $RESULTAT -eq 0 ]] 
then
    echo fichier non trouvé arret du programme 
else
    ### Partie commande pour recompiler le projet de A a Z sans qu'on puisse voir avec > /dev/null 2>&1
    make clean  > /dev/null 2>&1
    make all  > /dev/null 2>&1

    # Fake un sudo pour retenir que l'on est en mode sudoeur pour ensuite economiser le temps d'un sudo lors du démarage du programme ! (les secondes c'est important !)
    sudo ls > /dev/null 2>&1



    ### Partie initialisation du temps 
    SECONDS=0                                   # temps en secondes incrementé de base par le script bash
    TEMPS_DEBUT=$(date +%s%N | cut -b1-13)      # temps en milisecondes



    ### Partie exécution du programme 
    echo Début du chrono ! 
    sudo ./bin/solution $nomTXT | sudo ./bin/main # sortie standart de 1 va dans entrée standart de 2 


    ### Partie affichage temps 

    TEMPS_FIN=$(date +%s%N | cut -b1-13) 
    # entre () pour définir une opération arythmétique
    TEMPS_TOT=$(($TEMPS_FIN - $TEMPS_DEBUT))

    echo "Le programme a mis :" $SECONDS "secondes a s'exécuter ! "
    echo "avec précision, le programme a mis " $TEMPS_TOT "milisecondes à s'exécuter"

fi
    


