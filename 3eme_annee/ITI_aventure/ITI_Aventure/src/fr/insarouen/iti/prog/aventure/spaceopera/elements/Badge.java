package fr.insarouen.iti.prog.aventure.spaceopera.elements;


import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;


public class Badge extends Cle{

    public Badge(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException {
        super(nom, monde);
    }

    
}