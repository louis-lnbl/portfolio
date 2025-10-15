package fr.insarouen.iti.prog.aventure;

import java.util.Collection;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;
import java.util.Scanner;
import fr.insarouen.iti.prog.aventure.elements.vivants.JoueurHumain;
import fr.insarouen.iti.prog.aventure.elements.Executable;

/**
 * La classe Simulateur permet de gérer l'exécution d'une partie dans le monde du jeu.
 *
 */

public class Simulateur{

    private EtatDuJeu etat = EtatDuJeu.ENCOURS;
    private Monde monde = null;
    private Collection<ConditionDeFin> conditionsDeFin= null;

    /**
     * Constructeur du simulateur.
     *
     * @param monde Le monde dans lequel la simulation se déroule.
     * @param conditionsDeFin La liste des conditions de fin du jeu.
     */

    public Simulateur(Monde monde, Collection<ConditionDeFin> conditionsDeFin){
        this.monde = monde;
        this.conditionsDeFin = conditionsDeFin;
    }

    /**
     * Exécute un tour de jeu.
     * 
     *
     * @return L'état actuel du jeu après le tour (ENCOURS, SUCCES, ou ECHEC).
     */

    public EtatDuJeu executerUnTour(){
        if (this.etat.equals(EtatDuJeu.ENCOURS)){
            Scanner sc = null;
            String lOrdre = null;
            for (JoueurHumain unJoueurHumain : this.monde.getExecutables().stream().filter(elt -> elt instanceof JoueurHumain).map(elt -> (JoueurHumain) elt).toList()){
                System.out.println(unJoueurHumain.toString());
                System.out.println(unJoueurHumain.getPiece().toString());
                System.out.print("Donnez un ordre :");
                sc = new Scanner(System.in);
                lOrdre = sc.nextLine();
                unJoueurHumain.setOrdre(lOrdre);
            }
            for (Executable unExecutable : this.monde.getExecutables()){
                try{
                    unExecutable.executer();
                } catch (ITIAventureException e){
                    e.printStackTrace();
                }
                
            }
            if (this.conditionsDeFin != null) {
                for (ConditionDeFin uneCondition : this.conditionsDeFin){
                    if (uneCondition.verifierCondition() != EtatDuJeu.ENCOURS){
                        this.etat = uneCondition.verifierCondition();
                    }
                }
            }
            if(this.etat == EtatDuJeu.SUCCES){
                System.out.println("\nPartie terminée : Bravo, vous avez gagné!\n");
            }
            if(this.etat == EtatDuJeu.ECHEC){
                System.out.println("\nPartie terminée : Dommage, vous avez perdu!\n");
            }
        }
        return this.etat;
    }
    
    /**
     * Exécute la simulation complète du jeu jusqu'à ce qu'une condition de fin soit atteinte.
     */

    public void executerJusquALaFin(){
        while (this.etat.equals(EtatDuJeu.ENCOURS)){
            this.executerUnTour();
        }
    }
}