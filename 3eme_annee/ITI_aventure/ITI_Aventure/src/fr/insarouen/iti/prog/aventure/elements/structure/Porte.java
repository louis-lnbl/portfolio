package fr.insarouen.iti.prog.aventure.elements.structure;

import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.Etat;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.Activable;
import fr.insarouen.iti.prog.aventure.elements.objets.PiedDeBiche;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleAvecObjetException;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleException;

import java.io.Serializable;

/**
 * La classe Porte représente une porte qui sépare deux pièces.
 * Une porte  possède un nom, un monde, sépare deux pièces et peut possèder une serrure si elle est verouillée.
 */

public class Porte extends ElementStructurel implements Activable{

    private Piece pieceA;
    private Piece pieceB;
    private Etat etat = Etat.FERME;
    private Serrure serrure = null;

    public Porte(String nom, Monde m, Piece pieceA, Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException{
        super(nom,m);
        this.pieceA=pieceA;
        this.pieceB=pieceB;
        this.pieceA.addPorte(this);
        this.pieceB.addPorte(this);
    }

    public Porte(String nom,Monde m,Serrure serrure,Piece pieceA,Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException{
        this(nom,m,pieceA,pieceB);
        this.serrure = serrure;
        if (this.serrure.getEtat() == Etat.VERROUILLE){
            this.etat = etat.VERROUILLE;
        }
    }

    /**
     * permet d'obtenir la pièce de l'autre coté de la porte 
     *
     * @param piece la piece du premier coté de la porte
     * @return retourne la pièce de l'autre coté de la porte
     */

    public Piece getPieceAutreCote(Piece piece){
        if (piece.getNom().equals(this.pieceA.getNom())){
            return this.pieceB;
        }else {
            return this.pieceA;
        }
    }

    /**
     * Vérifie si la porte est activable avec un objet .
     *
     * @param objet L'objet en question.
     * @return true si l'objet peut activer la porte, sinon false.
     */

    @Override 
    public boolean activableAvec(Objet objet){
        if (this.serrure != null){
            if (objet instanceof PiedDeBiche pdb){
                if (this.etat == Etat.VERROUILLE){
                    return true;
                }
            }
            if (this.serrure.activableAvec(objet)){
                return true;
            }
        }
        return false;
    }

    /**
     * permet de changer l'état de la porte.
     * 
     * 
     */

    public void activer() throws ActivationImpossibleException{ 
       if (this.getEtat() == Etat.FERME){
            this.etat = Etat.OUVERT;
       }else{
            if (this.getEtat() == Etat.OUVERT){
                this.etat = Etat.FERME;                
            }else{
                throw new ActivationImpossibleException("la porte ne peut pas etre activée quand la porte est verouillée");
            }
       }
    }

    /**
     * permet d'activer la porte avec un objet spécifique.
     * 
     *@param l'objet qu'on active la porte avec.
     * 
     */

    public void activerAvec(Objet objet) throws ActivationImpossibleAvecObjetException,ActivationImpossibleException{
        if (!(this.activableAvec(objet))){
            throw new ActivationImpossibleAvecObjetException("impossible d'activer la porte avec cet objet");
        }
        if (!(this.serrure == null)){
            if ((objet instanceof PiedDeBiche pbd) && (this.getEtat() == Etat.VERROUILLE)){
                this.serrure = null;
                this.etat = Etat.OUVERT;
            }else{
                if ((this.serrure.activableAvec(objet)) && (this.getEtat() == etat.VERROUILLE)){
                    this.etat = Etat.OUVERT;
                }else{
                    if((this.serrure.activableAvec(objet)) && !(this.getEtat() == etat.VERROUILLE)){
                        this.etat = Etat.VERROUILLE;
                    }
                }
            }
        }else{
            throw new ActivationImpossibleException("impossible d'activer la porte car pas de serrure");
        }
            
    }

    /**
     * permet d'obtenir l'état de la porte
     * 
     * 
     *@return retourne l'état de la porte.
     */

    public Etat getEtat(){
        return this.etat;
    }

    /**
     * permet d'obtenir la serrure.
     * 
     * 
     *@return retourne la serrure.
     */
    

    public Serrure getSerrure(){
        return this.serrure;
    }

    public String toString(){
        String etatStr = null;
        switch (this.getEtat()){
            case Etat.FERME : 
                etatStr = "fermée";
                break;
            case Etat.OUVERT : 
                etatStr = "ouverte";
                break;
            case Etat.VERROUILLE : 
                etatStr = "verrouillée";
                break;
            default:
                break;   
        }
        return String.format("%s, etat : %s", super.toString(),etatStr);
    } 

}

