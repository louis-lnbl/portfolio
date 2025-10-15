package fr.insarouen.iti.prog.aventure.conditions;


import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;
import fr.insarouen.iti.prog.aventure.EtatDuJeu;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;


/**
 * Condition de fin vérifiant si un Vivant possède tous les objets spécifiés.
 * Si le vivant possède tous les objets, l'état du jeu défini est retourné. Sinon, 
 * EtatDuJeu est renvoyé.
 */

public class ConditionDeFinVivantPossedeObjets extends ConditionDeFin {

    private Vivant vivant;
    private Objet[] objets;

    public ConditionDeFinVivantPossedeObjets(EtatDuJeu etat, Vivant vivant, Objet ...objets){

        super(etat);
        this.vivant=vivant;
        this.objets=objets;

    }

    /**
     * Vérifie si le vivant possède tous les objets spécifiés.
     *
     * @return l'état du jeu défini si la condition est remplie (le vivant possède tous les objets).
     * 
     */

    @Override
    public EtatDuJeu verifierCondition(){

        boolean conditionVerifiee=true;
        for (Objet o:this.objets){
            if(!(this.vivant.possede(o))){
                conditionVerifiee=false;
            }
        }
        if (conditionVerifiee){
            return this.getEtatConditionDeFin();
        }else {
            return EtatDuJeu.ENCOURS;
        }
    }
}