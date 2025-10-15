package fr.insarouen.iti.prog.aventure.elements.vivants;


import fr.insarouen.iti.prog.aventure.elements.Entite;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.elements.structure.ObjetAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.objets.ObjetNonDeplacableException;
import fr.insarouen.iti.prog.aventure.elements.structure.VivantAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.Etat;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.structure.PorteFermeException;
import fr.insarouen.iti.prog.aventure.elements.structure.PorteInexistanteDansLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.Executable;

import java.util.HashMap;
import java.util.Map;
import java.util.Collection;
import java.util.Collections;

/**
 * La classe Vivant représente un être vivant dans le monde du jeu.
 * Un vivant possède des points de vie, des points de force, une position dans une pièce et peut porter des objets.
 */

public abstract class Vivant extends Entite implements Executable{

    private int pointVie;
    private int pointForce;
    private Piece piece;
    private Map<String,Objet> objet;

    /**
     * Constructeur de la classe Vivant. 
     * Ajoute le vivant dans la pièce où il se trouve.
     *
     * @param nom       Le nom du vivant.
     * @param monde     Le monde dans lequel le vivant existe.
     * @param pointVie  Les points de vie du vivant.
     * @param pointForce Les points de force du vivant.
     * @param piece     La pièce où se trouve le vivant.
     * @param objet     Les objets que le vivant possède.
     */

    public Vivant (String nom, Monde monde, int pointVie, int pointForce, Piece piece, Objet... objet) throws NomDEntiteDejaUtiliseDansLeMondeException{
        super(nom,monde);
        this.pointVie = pointVie;
        this.pointForce = pointForce;
        this.piece = null;
        piece.entrer(this);
        this.objet = new HashMap<>();

        for (Objet elt : objet){
            this.objet.put(elt.getNom(),elt);
        }
    }

    /**
     * Permet au vivant de prendre un objet présent dans la pièce.
     * Cet objet n'apparait plus dans la pièce.
     *
     * @param objet L'objet à prendre.
     */

    public void prendre(Objet objet) throws ObjetAbsentDeLaPieceException, ObjetNonDeplacableException{
        if (!objet.estDeplacable()){
            throw new ObjetNonDeplacableException(objet.getNom()+"ne peut pas etre déplacé.");
        }
        Objet new_objet = this.piece.retirer(objet);
        this.objet.put(new_objet.getNom(),new_objet);

    }

    /**
     * Permet au vivant de prendre un objet présent dans la pièce par son nom.
     * Cet objet n'apparait plus dans la pièce.
     *
     * @param nom Le nom de l'objet à prendre.
     */

    public void prendre(String nom) throws ObjetAbsentDeLaPieceException, ObjetNonDeplacableException{
    
        Objet new_objet = this.piece.retirer(nom);
        this.objet.put(new_objet.getNom(),new_objet);
        if (!new_objet.estDeplacable()){
            throw new ObjetNonDeplacableException(new_objet.getNom()+"ne peut pas etre déplacé.");
        }
    }

    /**
     * Permet au vivant de déposer un objet dans la pièce actuelle.
     * L'objet n'apparait plus sur le vivant mais apparait dans la pièce.
     *
     * @param objet L'objet à déposer.
     */    

    public void deposer(Objet objet) throws ObjetNonPossedeParLeVivantException{
        
        if (!this.possede(objet)){
            throw new ObjetNonPossedeParLeVivantException("le vivant ne possede pas l'objet en question.");
        }
        
        this.piece.deposer(objet);
        this.objet.remove(objet.getNom());

    }

    

    /**
     * Permet au vivant de déposer un objet dans la pièce actuelle par son nom.
     * L'objet n'apparait plus sur le vivant mais apparait dans la pièce.
     *
     * @param nom Le nom de l'objet à déposer.
     */    

    public void deposer(String nom) throws ObjetNonPossedeParLeVivantException{
        if (this.getObjet(nom)==null){
            throw new ObjetNonPossedeParLeVivantException("le vivant ne possede pas l'objet en question.");
        }
        this.piece.deposer(this.objet.get(nom));        
        this.objet.remove(nom);

    }

    /**
     * Retourne un objet possédé par le vivant à partir de son nom.
     *
     * @param nomObjet Le nom de l'objet recherché.
     * @return L'objet correspondant ou null s'il n'est pas trouvé.
     */

    public Objet getObjet( String nomObjet ) throws ObjetNonPossedeParLeVivantException{
        
        if (!this.objet.containsKey(nomObjet)){
            throw new ObjetNonPossedeParLeVivantException("le vivant n''a pas cet objet");
        }else{
            return this.objet.get(nomObjet);
        }
    }

    /**
     * Retourne la liste des objets possédés par le vivant.
     *
     * @return collection d'objets
     **/

    public Collection<Objet> getObjets(){
        Map<String,Objet> objetsTemp = new HashMap<>();
        for (Objet o : this.objet.values()){
            objetsTemp.put(o.getNom(),o);
        }
        return objetsTemp.values();
    }

    /**
     * Vérifie si le vivant possède un objet donné.
     *
     * @param objet L'objet à vérifier.
     * @return true si l'objet est possédé, sinon false.
     */

    public boolean possede(Objet objet){
        
        return this.objet.containsValue(objet);
    }

    public boolean possede(String nomObjet){
        return this.objet.containsKey(nomObjet);
    }

    public void setPiece(Piece piece){
        if (piece != null){
            piece.entrer(this);
        } else{
            Piece pieceCourante = this.piece;
            if (pieceCourante != null && pieceCourante.contientVivant(this)){
                try{
                    piece.sortir(this);
                } catch (VivantAbsentDeLaPieceException e){
                    throw new Error("ne devrait pas arriver", e);
                }
            }
        }
        this.piece = piece;
    } 

    public Piece getPiece(){
        return this.piece;
    }   

    /**
     * Retourne une représentation textuelle du vivant.
     *
     * @return Une chaîne décrivant le vivant.
     */
   
    public String toString(){
        if (this.getObjets().size()==0) {
            return String.format("\n---%s---\n%s (%d PV, %d PF) : \n  ne possédant rien, \n  est dans : %s", this.getClass().getSimpleName(),super.toString(),this.getPointVie(), this.getPointForce(), this.getPiece().getNom());
        }
        String objetsDuVivantStr="";
        for (Objet obj : this.getObjets()){
            objetsDuVivantStr +=" "+ obj.getNom() ;
        }
        return String.format("\n---%s---\n%s (%d PV, %d PF) : \n  possédant : %s \n  est dans : %s", this.getClass().getSimpleName(), super.toString(),this.getPointVie(), this.getPointForce(), objetsDuVivantStr,  this.getPiece().getNom());
    }

    /**
     * Permet au vivant de franchir une porte.
     *
     *
     * @param porte La porte à franchir.
     * @throws PorteInexistanteDansLaPieceException si la porte n'est pas présente dans la pièce actuelle.
     * @throws PorteFermeException si la porte est fermée.
     */

    public void franchir(Porte porte)throws PorteInexistanteDansLaPieceException,PorteFermeException{
        if (!this.piece.aLaPorte(porte)){
            throw new PorteInexistanteDansLaPieceException("la porte n'existe pas dans la pièce");
        }
        if (porte.getEtat()==Etat.FERME) {
            throw new PorteFermeException("la porte est fermée");
        }
        porte.getPieceAutreCote(this.piece).entrer(this);
    }


    /**
     * Permet au vivant de franchir une porte par son nom.
     * 
     *
     * @param nomPorte Le nom de la porte à franchir.
     * @throws PorteInexistanteDansLaPieceException si la porte n'est pas présente dans la pièce actuelle.
     * @throws PorteFermeException si la porte est fermée.
     */

    public void franchir(String nomPorte)throws PorteInexistanteDansLaPieceException, PorteFermeException{

        if (!this.piece.aLaPorte(nomPorte)){
            throw new PorteInexistanteDansLaPieceException("la porte n'existe pas dans la pièce");
        }
        if (this.piece.getPorte(nomPorte).getEtat()==Etat.FERME) {
            throw new PorteFermeException("la porte est fermée");
        }
        this.piece.getPorte(nomPorte).getPieceAutreCote(this.piece).entrer(this);
        
    }

    /**
     * Retourne le nombre de points de vie du vivant.
     *
     * @return Les points de vie.
     */

    public int getPointVie(){
        return this.pointVie;
    }

    /**
     * Modifie les points de vie du vivant.
     *
     * @param pv Le nouveau nombre de points de vie.
     */

    public void setPointVie(int pv){
        this.pointVie = pv;
    }

    /**
     * Retourne les points de force du vivant.
     *
     * @return Les points de force.
     */

    public int getPointForce(){
        return this.pointForce;
    }

    /**
     * Modifie les points de force du vivant.
     *
     * @param pf Le nouveau nombre de points de force.
     */

    public void setPointForce(int pf){
        this.pointForce = pf;
    }

    /**
     * Indique si le vivant est mort.
     *
     * @return true si les points de vie sont inférieurs ou égaux à 0, sinon false.
     */
    
    public boolean estMort(){
        return (this.getPointVie() <= 0);
    }



}