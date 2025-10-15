package fr.insarouen.iti.prog.aventure.elements.objets;

import fr.insarouen.iti.prog.aventure.Monde;

import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
/**
 * La classe {@code PiedDeBiche} représente un pied-de-biche dans le jeu. Elle hérite de la classe
 * {@link Objet} et redéfinit certaines fonctionnalités spécifiques à cet objet.
 * 
 * Un pied-de-biche est un objet déplaçable dans le jeu, contrairement aux objets de la classe {@link Objet}
 * qui ne sont pas déplaçables par défaut.
 */
public class PiedDeBiche extends Objet{

    //attributs

    //constructeurs
    /**
     * Crée un pied-de-biche avec un nom et un monde spécifiés.
     * 
     * @param nom Le nom du pied-de-biche.
     * @param monde Le monde auquel le pied-de-biche appartient.
     */
    public PiedDeBiche(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{
        super(nom,monde);
        
    }

    //méthodes
    /**
     * Vérifie si le pied-de-biche est déplaçable.
     * 
     * @return {@code true} car un pied-de-biche est déplaçable.
     */
    public boolean estDeplacable(){
        return true;
    }

}