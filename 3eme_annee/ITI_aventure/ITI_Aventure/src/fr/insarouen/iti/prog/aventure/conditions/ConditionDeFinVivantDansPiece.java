package fr.insarouen.iti.prog.aventure.conditions;


import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.EtatDuJeu;


/**
 * Condition de fin vérifiant si un Vivant se trouve dans une Piece.
 *
 * 
 */

public class ConditionDeFinVivantDansPiece extends ConditionDeFin {


    private Vivant vivant;
    private Piece piece;

    public ConditionDeFinVivantDansPiece(EtatDuJeu etat, Vivant vivant, Piece piece){

        super(etat);
        this.vivant=vivant;
        this.piece=piece;

    }

    /**
     * Vérifie si le vivant est dans la pièce spécifiée.
     *
     * @return l'état de jeu défini si la condition est remplie.
     */

    @Override
    public EtatDuJeu verifierCondition(){

        if (this.piece.contientVivant(this.vivant)){
            return this.getEtatConditionDeFin();
        }else {
            return EtatDuJeu.ENCOURS;
        }
    }
}