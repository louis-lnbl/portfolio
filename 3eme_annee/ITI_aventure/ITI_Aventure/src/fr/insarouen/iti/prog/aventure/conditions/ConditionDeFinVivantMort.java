package fr.insarouen.iti.prog.aventure.conditions;

import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;
import fr.insarouen.iti.prog.aventure.EtatDuJeu;

/**
 * Condition de fin vérifiant si un Vivant est mort.
 * Si le vivant est mort, l'état du jeu défini est retourné. Sinon, 
 * EtatDuJeu ENCOURS est renvoyé.
 */

public class ConditionDeFinVivantMort extends ConditionDeFin {

    private Vivant vivant;

    public ConditionDeFinVivantMort(EtatDuJeu etat, Vivant vivant){

        super(etat);
        this.vivant=vivant;

    }

    /**
     * Vérifie si le vivant est mort.
     *
     * @return l'état du jeu défini si le vivant est mort, sinon EtatDuJeu ENCOURS.
     */

    @Override
    public EtatDuJeu verifierCondition(){

        if (this.vivant.estMort()){
            return this.getEtatConditionDeFin();
        }else {
            return EtatDuJeu.ENCOURS;
        }
    }
}