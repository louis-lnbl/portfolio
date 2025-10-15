package fr.insarouen.iti.prog.aventure.conditions;


import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;
import fr.insarouen.iti.prog.aventure.EtatDuJeu;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;



/**
 * Condition de fin vérifiant si un Vivant se trouve dans une Piece
 * et possède tous les objets spécifiés.
 * Si le vivant est bien dans la pièce et possède tous les objets, alors
 * l'état du jeu défini est retourné. Sinon, EtatDuJeu est renvoyé.
 */

public class ConditionDeFinVivantDansPieceEtPossedeObjets extends ConditionDeFin {

    private Vivant vivant;
    private Objet[] objets;
    private Piece piece;

    public ConditionDeFinVivantDansPieceEtPossedeObjets(EtatDuJeu etat, Vivant vivant, Piece piece, Objet ...objets){

        super(etat);
        this.vivant=vivant;
        this.piece=piece;
        this.objets=objets;

    }

    /**
     * Vérifie si le vivant est dans la pièce et possède tous les objets requis.
     *
     * @return l'état du jeu défini si la condition est remplie, sinon EtatDuJeu Encours.
     */

    @Override
    public EtatDuJeu verifierCondition(){

        boolean conditionVerifiee=true;
        for (Objet o:this.objets){
            if(!(this.vivant.possede(o))){
                conditionVerifiee=false;
            }
        }
        if (conditionVerifiee && this.piece.contientVivant(this.vivant)){
            return this.getEtatConditionDeFin();
        }else {
            return EtatDuJeu.ENCOURS;
        }
    }   
}