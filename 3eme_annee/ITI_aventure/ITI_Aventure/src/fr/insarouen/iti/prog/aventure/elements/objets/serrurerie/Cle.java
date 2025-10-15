package fr.insarouen.iti.prog.aventure.elements.objets.serrurerie;

import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.Activable;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;

import java.io.Serializable;

public class Cle extends Objet{
    
    protected Cle(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{
        super(nom,monde);
    }

    public boolean estDeplacable(){
        return true;
    }

}