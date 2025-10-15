package fr.insarouen.iti.prog.aventure.elements.structure;

import fr.insarouen.iti.prog.aventure.elements.Entite;

import fr.insarouen.iti.prog.aventure.Monde;

import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;

/**
 * La classe {@code ElementStructurel} représente un élément structurel dans le monde du jeu.
 * Elle hérite de la classe {@link Entite}, ce qui signifie qu'un élément structurel a un nom et
 * appartient à un monde spécifique.
 * 
 * Un élément structurel peut représenter des objets dans le jeu qui font partie d'une structure,
 * comme des pièces, des portes, etc. Cependant, cette classe ne définit pas encore de
 * comportement spécifique pour ces éléments ; elle sert de base pour les sous-classes.
 */
public abstract class ElementStructurel extends Entite{

    //attributs

    //constructeurs
    /**
     * Crée un élément structurel avec un nom et un monde spécifiés.
     * 
     * @param nom Le nom de l'élément structurel.
     * @param monde Le monde auquel l'élément structurel appartient.
     */
    public ElementStructurel(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{

        super(nom,monde);
    }

    //méthodes
    /**
     * Retourne une représentation sous forme de chaîne de caractères de l'élément structurel.
     * 
     * @return Le nom de l'élément structurel sous forme de chaîne de caractères.
     */
    public String toString(){

        return String.format("%s",super.toString());
    }

}