package fr.insarouen.iti.prog.aventure.elements.structure;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;

import java.util.Map;
import java.util.HashMap;
import java.util.Collection;
import java.util.Collections;
import java.io.Serializable;



/**
 * La classe Piece représente une pièce qui peut contenir des objets , des vivants et qui peut avoir des portes pour passage d'une pièce à une autre.
 * Une piece est un element structurel qui possède un nom et un monde.
 */

public class Piece extends ElementStructurel{

    private Map<String,Objet> objets;
    private Map<String,Vivant> vivants;
    private Map<String,Porte> portes;

    public Piece (String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{
        super(nom,monde);
        this.objets = new HashMap<>();
        this.vivants = new HashMap<>();
        this.portes = new HashMap<>();
    }

    /**
     * Vérifie si un objet est présent dans la pièce.
     *
     * @param objet L'objet à rechercher.
     * @return true si l'objet est présent, sinon false.
     */

    public boolean contientObjet(Objet objet){
        return this.objets.containsValue(objet);
    }

    /**
     * Vérifie si un objet portant un nom spécifique est présent dans la pièce.
     *
     * @param nomObjet Le nom de l'objet recherché.
     * @return true si un objet avec ce nom est présent, sinon false.
     */

    public boolean contientObjet(String nomObjet){
        return this.objets.containsKey(nomObjet);
    }

    /**
     * Dépose un objet dans la pièce.
     *
     * @param objet L'objet à déposer.
     */    

    public void deposer(Objet objet){
        this.objets.put(objet.getNom(),objet);
    }

    /**
     * Retire un objet de la pièce.
     *
     * @param objet L'objet à retirer.
     * @return L'objet retiré ou null s'il n'est pas trouvé.
     */

    public Objet retirer(Objet objet) throws ObjetAbsentDeLaPieceException{

        Objet objet_ret = null;
        if (!this.contientObjet(objet)){
            throw new ObjetAbsentDeLaPieceException("L'objet n'est pas présent dans la pièce.");
        }else{
            objet_ret = this.objets.get(objet.getNom());
            this.objets.remove(objet.getNom());
        }
        return objet_ret;  

    }

    /**
     * Retire un objet de la pièce par son nom.
     *
     * @param nom Le nom de l'objet à retirer.
     * @return L'objet retiré ou null s'il n'est pas trouvé.
     */

    public Objet retirer(String nom) throws ObjetAbsentDeLaPieceException{

        Objet objet_ret = null;
        if (!this.contientObjet(nom)){
            throw new ObjetAbsentDeLaPieceException("L'objet n'est pas présent dans la pièce.");
        }else{
            objet_ret = this.objets.get(nom);
            this.objets.remove(nom);
        }
        return objet_ret;  

    }

    /**
     * Retourne tous les objets présents dans la pièce.
     *
     * @return une collection d'objets
     */

    public Collection<Objet> getObjets(){
        
        Map<String,Objet> objetsTemp = new HashMap<>();
        for (Objet o : this.objets.values()){
            objetsTemp.put(o.getNom(),o);
        }
        return objetsTemp.values();
    }
    
    
    

    /**
     * Vérifie si un vivant est présent dans la pièce.
     *
     * @param vivant Le vivant à rechercher.
     * @return true si le vivant est présent, sinon false.
     */

    public boolean contientVivant (Vivant vivant){
        
        return this.vivants.containsValue(vivant);
    
    }

    /**
     * Vérifie si un vivant portant un nom spécifique est présent dans la pièce.
     *
     * @param nomVivant Le nom du vivant recherché.
     * @return true si un vivant avec ce nom est présent, sinon false.
     */

    public boolean contientVivant (String nomVivant){
        
        return this.vivants.containsKey(nomVivant);
    
    }

    /**
     * Ajoute un vivant à la pièce.
     *
     * @param vivant Le vivant à ajouter.
     */

    public void entrer(Vivant vivant){
        if (! this.contientVivant(vivant)){
            if (vivant.getPiece() != null){
                try{
                    vivant.getPiece().sortir(vivant);
                } catch (VivantAbsentDeLaPieceException e){
                    throw new Error("Ne devrait pas arriver", e);
                }
            }
            this.vivants.put(vivant.getNom(),vivant);
            vivant.setPiece(this);
        }

    }


    /**
     * Retire un vivant de la pièce.
     *
     * @param vivant Le vivant à retirer.
     * @return Le vivant retiré ou null s'il n'est pas trouvé.
     */

    public Vivant sortir(Vivant vivant) throws VivantAbsentDeLaPieceException{

        return this.sortir(vivant.getNom());
    }

    /**
     * Retire un vivant de la pièce par son nom.
     *
     * @param nomVivant Le nom du vivant à retirer.
     * @return Le vivant retiré ou null s'il n'est pas trouvé.
     */    

    public Vivant sortir(String nomVivant) throws VivantAbsentDeLaPieceException {

        Vivant vivant_ret = null;
        if (!this.contientVivant(nomVivant)){
            throw new VivantAbsentDeLaPieceException("le vivant n'est pas dans la pièce.");
        }

        vivant_ret = this.vivants.get(nomVivant);
        this.vivants.remove(nomVivant);


        vivant_ret.setPiece(null);
        return vivant_ret;  
    }



    /**
     * Retourne tous les vivants présents dans la pièce.
     *
     * @return une collection de vivants
     */

    public Collection<Vivant> getVivants(){
        Map<String,Vivant> vivantsTemp = new HashMap<>();
        for (Vivant v : this.vivants.values()){
            vivantsTemp.put(v.getNom(),v);
        }
        return vivantsTemp.values();
    }


    /**
     * Retourne une représentation textuelle de la pièce.
     *
     * @return Une chaîne décrivant la pièce.
     */

    public String toString(){

        String objetsStr="contenant les objets suivants :";
        if (this.getObjets().size()==0) objetsStr = "ne contenant aucun objet";
        else {
            for (String elt : this.objets.keySet()){
                objetsStr+=" "+elt;
            }
        }
        String vivantsStr;
        if (this.getVivants().size()==0) vivantsStr = "n'ayant aucun vivant";
        else {
            vivantsStr="avec les vivants suivants :";
            for (String elt : this.vivants.keySet()){
                vivantsStr+=" "+elt;
            }
        }

        String portesStr;
        if (this.getPortes().size()==0) portesStr = "n'ayant auncune porte";
        else {
            portesStr="avec les "+this.getPortes().iterator().next().getClass().getSimpleName()+"s suivantes :";
            for (Porte elt : this.portes.values()){
                portesStr+="\n   "+elt.toString();
            }
        }

        return String.format("\n---%s---\n%s : \n  %s \n  %s \n  %s",this.getClass().getSimpleName(),super.toString(),objetsStr,vivantsStr,portesStr);

    }

    /**
     * ajoute une porte à la pièce
     *
     * @param porte la porte à ajouter.
     * 
     */

    protected void addPorte(Porte porte){

        this.portes.put(porte.getNom(),porte);

    }
    
    /**
     * vérifie si la porte est existante parmi les portes de la pièce
     *
     * @param porte la porte en question.
     * @return true si la porte existe , false sinon
     */

    public boolean aLaPorte(Porte porte){
        return this.portes.containsValue(porte);
    }

    /**
     * vérifie si la porte est existante parmi les portes de la pièce
     *
     * @param nomPorte le nom de la porte en question.
     * @return true si la porte existe , false sinon
     */

    public boolean aLaPorte(String nomPorte){
        return this.portes.containsKey(nomPorte);
    }

    /**
     * permet d'obtenir la porte de la pièce 
     *
     * @param nomPorte le nom de la porte à obtenir.
     * @return retourne la porte 
     */

    public Porte getPorte(String nomPorte){
        return this.portes.get(nomPorte);
    }

    /**
     * permet d'obtenir toutes les portes de la pièce 
     *
     *
     * @return retourne une collection de portes
     */

    public Collection<Porte> getPortes(){
        Map<String,Porte> portesTemp = new HashMap<>();
        for (Porte p : this.portes.values()){
            portesTemp.put(p.getNom(),p);
        }
        return portesTemp.values();
    }
}