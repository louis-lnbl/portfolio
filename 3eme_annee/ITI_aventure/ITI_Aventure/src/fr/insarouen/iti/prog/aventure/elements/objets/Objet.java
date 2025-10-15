package fr.insarouen.iti.prog.aventure.elements.objets;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.Entite;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;

import java.io.Serializable;

/**
 * La classe {@code Objet} représente un objet dans le monde du jeu. Elle hérite de la classe
 * {@link Entite} et ajoute des fonctionnalités spécifiques aux objets.
 * 
 * Cette classe permet de définir les caractéristiques d'un objet dans le jeu et de savoir s'il est
 * déplaçable ou non.
 */
public abstract class Objet extends Entite{

    //attributs

    //constructeurs
    /**
     * Crée un objet avec un nom et un monde spécifiés.
     * 
     * @param nom Le nom de l'objet.
     * @param monde Le monde auquel l'objet appartient.
     */
    public Objet(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{

        super(nom,monde);
    }

    //méthodes
    /**
     * Vérifie si l'objet est déplaçable.
     * 
     * @return {@code false} car par défaut les objets ne sont pas déplaçables.
     */
    public abstract boolean estDeplacable();
    

    /**
     * Retourne une représentation sous forme de chaîne de caractères de l'objet.
     * 
     * @return Le nom de l'objet sous forme de chaîne, en utilisant la méthode {@link Entite#toString()}.
     */
    public String toString(){
        
        return String.format("%s",super.toString());
    }

}