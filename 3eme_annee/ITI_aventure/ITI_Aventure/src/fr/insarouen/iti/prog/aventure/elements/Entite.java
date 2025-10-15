package fr.insarouen.iti.prog.aventure.elements;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;

import java.io.Serializable;

/**
 * La classe {@code Entite} représente une entité dans un monde.
 * Chaque entité a un nom et est associée à un monde particulier.
 * Elle permet d'obtenir des informations sur cette entité et de la comparer à d'autres entités.
 */

public abstract class Entite implements Serializable{
   

    //attributs
     /**
     * Le nom de l'entité.
     */
    private String nom;
    /**
     * Le monde auquel appartient l'entité 
     */
    private Monde monde;

    //constructeurs
    /**
     * Crée une nouvelle entité
     * 
     * @param nom Le nom de l'entité
     * @param monde Le monde auquel appartient l'entite
     */
    public Entite( String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{
        this.monde = monde;
        this.nom = nom;
        try{
        this.monde.ajouterEntite(this);            
        }catch (EntiteDejaDansUnAutreMondeException e){
            throw new Error("Ne devrait pas arriver",e);
        }


        
    }

    //methodes
    /**
     * Retourne le nom de l'entité
     * 
     * @return Le nom de l'entité
     */
    public String getNom(){
        return this.nom;
    }

    /**
     * Retourne le monde auquel appartient l'entité
     * 
     * @return Le monde auquel appartient l'entité
     */
    public Monde getMonde(){
        return this.monde;
    }

    /**
     * Retourne l'entité sous forme de chaine de caractère 
     * 
     * @return Une chaine de cractère contenant le nom de l'entité
     */
    public String toString(){
        return String.format("%s",this.nom);
    }

    /**
     * Compare deux entités pour vérifier si elles sont égales
     * Deux entités sont considérées égales si elles ont le même nom et appartiennent au même monde.
     * 
     * @param o L'objet à comparer avec cette entité.
     * @return {@code true} si les deux entités sont égales, {@code false} sinon.
     */
    public boolean equals(Object o){
        if (o==this)
            return true;
        if (o==null || this.getClass() != o.getClass())
            return false;
        Entite e = (Entite) o;
        return (this.nom == e.nom) && (this.monde == e.monde);
    }

    /**
     * Calcule le code de hachage de l'entité en fonction de son nom et de son monde.
     * 
     * @return Le code de hachage de l'entité.
     */
    public int hashCode(){
        return 13*this.nom.hashCode() + 17*this.monde.hashCode();
    }

}
