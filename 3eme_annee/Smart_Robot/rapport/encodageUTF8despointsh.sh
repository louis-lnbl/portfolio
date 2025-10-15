#!/bin/bash

# Répertoire contenant les fichiers .h originaux
source_dir="../Programme/include/Types"

# Répertoire où seront stockés les fichiers convertis
destination_dir="fichiersHUTF8/converted_headers"

# Créer le répertoire de destination s'il n'existe pas
mkdir -p "$destination_dir"

# Parcourir tous les fichiers .h dans le répertoire source
for file in "$source_dir"/*.h; do
    # Nom de fichier sans le chemin
    filename=$(basename "$file")
    
    # Convertir en UTF-8 et sauvegarder dans le répertoire de destination
    iconv -f ISO-8859-1 -t UTF-8 "$file" -o "$destination_dir/$filename"
    
    # Vérifier si la conversion a réussi
    if [ $? -eq 0 ]; then
        echo "Converti : $filename"
    else
        echo "Erreur de conversion : $filename"
    fi
done

echo "Tous les fichiers ont été convertis et déplacés vers $destination_dir."

