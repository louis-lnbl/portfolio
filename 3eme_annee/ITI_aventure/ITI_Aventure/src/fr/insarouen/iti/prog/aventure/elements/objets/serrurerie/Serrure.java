package fr.insarouen.iti.prog.aventure.elements.objets.serrurerie;

import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.Activable;
import fr.insarouen.iti.prog.aventure.elements.Etat;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleAvecObjetException;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleException;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;

import java.io.Serializable;

public class Serrure extends Objet implements Activable{
    private Etat etat=Etat.VERROUILLE;
    protected Cle cle = null;

    public Serrure(String nom,Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{
        super(nom,monde);
    }

    public Serrure(Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException{
        super(monde.genererNom("serrure"),monde);
    }

    public Etat getEtat(){
        return this.etat;
    }

    @Override
    public boolean estDeplacable(){
        return false;
    }

    public Cle creerCle() throws NomDEntiteDejaUtiliseDansLeMondeException{
        if (this.cle == null){
            Cle uneCle = new Cle(this.getMonde().genererNom("cle"), this.getMonde());
            this.cle = uneCle;
            return uneCle;
        }else{
            return null;
        }
    }

    public void activer() throws ActivationImpossibleException{
        throw new ActivationImpossibleException("Impossible d'activer la serrure");
    }

    public void activerAvec(Objet obj) throws ActivationImpossibleAvecObjetException{
        if (!obj.equals(this.cle)){
            throw new ActivationImpossibleAvecObjetException("impossible de l'activer sans le bon objet");
        }else{
            this.etat = Etat.DEVERROUILLE;
        }
    }

    public boolean activableAvec(Objet obj){
        return (obj.equals(this.cle));
    }

}