package fr.insarouen.iti.prog.aventure.spaceopera.elements;


import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;

public class LecteurBadge extends Serrure{

    public LecteurBadge(String nom,Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException {

        super(nom, monde);
    }

    @Override
    public Cle creerCle() throws NomDEntiteDejaUtiliseDansLeMondeException{
        if (this.cle == null){
            Cle uneCle = new Badge(this.getMonde().genererNom("badge"), this.getMonde());
            this.cle = uneCle;
            return uneCle;
        }else{
            return null;
        }
    }


}