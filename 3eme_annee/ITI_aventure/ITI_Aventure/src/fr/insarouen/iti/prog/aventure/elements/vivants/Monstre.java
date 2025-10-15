package fr.insarouen.iti.prog.aventure.elements.vivants;


import fr.insarouen.iti.prog.aventure.elements.Entite;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.Executable;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.elements.structure.ObjetAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.objets.ObjetNonDeplacableException;
//import fr.insarouen.iti.prog.aventure.elements.structure.VivantAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.ITIAventureException;
import fr.insarouen.iti.prog.aventure.elements.Etat;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.structure.PorteFermeException;
import fr.insarouen.iti.prog.aventure.elements.structure.PorteInexistanteDansLaPieceException;

import java.util.List;
import java.util.ArrayList;
import java.util.Optional;
import java.util.Collection;

/**
 * La classe Monstre représente un monstre qui est un vivant.
 */

public class Monstre extends Vivant implements Executable{

    /**
     * Construit un monstre avec un nom, un monde, des points de vie et de force,
     * et une pièce de départ.
     *
     * @param nom le nom du monstre
     * @param monde le monde dans lequel le monstre évolue
     * @param pointVie les points de vie du monstre
     * @param pointForce les points de force du monstre
     * @param piece la pièce dans laquelle le monstre est initialement situé
     * @throws VivantAbsentDeLaPieceException si le monstre ne peut pas être placé dans la pièce
     * @throws NomDEntiteDejaUtiliseDansLeMondeException si le nom du monstre est déjà utilisé dans le monde
     */

    public Monstre(String nom, Monde monde, int pointVie, int pointForce, Piece piece) throws /*VivantAbsentDeLaPieceException,*/ NomDEntiteDejaUtiliseDansLeMondeException{
        super(nom,monde,pointVie,pointForce,piece);
    }


    /**
     * Définit le comportement du monstre.
     *
     *
     * @throws ITIAventureException si une erreur liée à l'aventure survient (porte, objet, etc.)
     */

    public void executer()throws ITIAventureException{

        if (!(this.estMort())){
            this.setPointVie((this.getPointVie()-1));
            Optional<Porte> premierePorteOuverteOuFermee = this.getPiece().getPortes().stream().filter(p->((p.getEtat() == Etat.OUVERT) || (p.getEtat() == Etat.FERME))).findFirst();

            //Cherche la premiere porte à partir du flux. On applique un filter pour que la porte soit soit ouverte, soit fermée. Le find first permet de s'arreter à la permiere porte trouvée

            if(premierePorteOuverteOuFermee.isPresent()){
                Porte porteFranchissable = premierePorteOuverteOuFermee.get();
                if (porteFranchissable.getEtat() == Etat.FERME){
                    porteFranchissable.activer();
                }
                this.franchir(porteFranchissable);
                Collection<Objet> inventaireMonstreTemp = this.getObjets();
                for(Objet o : this.getPiece().getObjets()){
                    this.prendre(o);
                }
                for(Objet o : inventaireMonstreTemp){
                    this.deposer(o);
                }
            }
        }
    }


}