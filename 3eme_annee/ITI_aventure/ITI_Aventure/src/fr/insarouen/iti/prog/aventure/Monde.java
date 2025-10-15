package fr.insarouen.iti.prog.aventure;

import fr.insarouen.iti.prog.aventure.elements.Entite;
import java.util.Map;
import java.util.HashMap;
import java.io.Serializable;
import java.util.Collection;
import fr.insarouen.iti.prog.aventure.elements.Executable;

/**
 * La classe Monde représente un monde dans lequel des entités peuvent exister.
 * Elle permet de gérer une collection d'entités et d'effectuer des opérations comme
 * ajouter une entité ou récupérer une entité par son nom.
 */
public class Monde implements Serializable{
    
    //attributs
    /**
     * Le nom du monde.
     */
    private String nom;

    /**
     * Le tableau d'entités présentes dans le monde.
     */   
    private Map<String,Entite> entites;

    //constructeurs
    /**
     * Crée un monde avec un nom spécifié et un tableau d'entités vide (sans entité).
     * 
     * @param nom Le nom du monde.
     */   
    public Monde(String nom){
        this.nom = nom;
        this.entites = new HashMap<>();
    }

    /**
     * Récupère le nom du monde.
     * 
     * @return Le nom du monde.
     */
    public String getNom(){
        return this.nom;
    }



    /**
     * Récupère une entité par son nom dans le monde.
     * 
     * @param nom Le nom de l'entité à rechercher.
     * @return L'entité correspondant au nom donné, ou {@code null} si elle n'existe pas.
     */
    public Entite getEntite(String nom){
        
        return this.entites.get(nom);
        
    }


    /**
     * Renvoie une nouvelle collection contenant toutes les entites du monde.
     *
     * @return Une collection contenant les entites du monde.
     */
    public Collection<Entite> getEntites(){
        Map<String,Entite> entitesTemp = new HashMap<>();
        for (Entite e : this.entites.values()){
            entitesTemp.put(e.getNom(),e);
        }
        return entitesTemp.values();
    }

    /**
     * Ajoute une nouvelle entité au monde.
     * 
     * @param entite L'entité à ajouter au monde (on cosidère que l'utilisateur n'ajoute pas deux fois la même entité).
     */
    public void ajouterEntite(Entite entite) throws NomDEntiteDejaUtiliseDansLeMondeException, EntiteDejaDansUnAutreMondeException{
        if (this.getEntite(entite.getNom()) != null){
            throw new NomDEntiteDejaUtiliseDansLeMondeException("L'entite existe deja dans le monde.");
        }
        if (entite.getMonde().getNom() != this.getNom()){
            throw new EntiteDejaDansUnAutreMondeException("L'entite existe deja dans un autre monde.");
        }
        this.entites.put(entite.getNom(),entite);
    }

    /**
     * Retourne une représentation sous forme de chaîne de caractères du monde et de ses entités.
     * Chaque entité est représentée par son nom, et elles sont séparées par des espaces.
     * 
     * @return Une chaîne de caractères représentant le monde et ses entités.
     */
    public String toString(){
        String ch = ""; 

        for (String elt : this.entites.keySet()){
            ch = ch + elt + " ";
        }

        return String.format("%s:%s",this.getNom(),ch);
    }

    /**
     * génère aléatoirement un nom préfixé qui n’existe pas dans le monde.
     * 
     * @param prefixe le prefixe du nom généré
     * @return retourne le nom après la vérification de son existence dans le monde.
     */

    public String genererNom(String prefixe){
        String nom = prefixe + (int)(100*Math.random());
        while (this.entites.containsKey(nom)){
            nom = prefixe + (int)(100*Math.random());
        }
        return nom;

    }

    public Collection<Executable> getExecutables() {
        return this.entites.values().stream().filter(a -> a instanceof Executable).map(elt -> (Executable) elt).toList();
    }


}