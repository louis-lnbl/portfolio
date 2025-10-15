package fr.insarouen.iti.prog.aventure.conditions;

import fr.insarouen.iti.prog.aventure.EtatDuJeu;

import java.io.Serializable;


/**
 * Classe abstraite représentant une condition de fin du jeu.
 *
 *
 */
public abstract class ConditionDeFin implements Serializable{


    private EtatDuJeu etat;

    public ConditionDeFin(EtatDuJeu etat){

        this.etat=etat;

    }

    /**
     * Retourne l'état de jeu associé à cette condition.
     * @return l'état de jeu (SUCCES, ECHEC, etc.)
     */
    public EtatDuJeu getEtatConditionDeFin(){
        return this.etat;
    }

    /**
     * Méthode abstraite à implémenter dans les sous-classes.
     * 
     * @return l'état de jeu à appliquer si la condition est remplie.
     * 
     */
    public abstract EtatDuJeu verifierCondition();
 
}