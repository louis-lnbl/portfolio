package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

import fr.insarouen.iti.prog.patronsConception.visiteur.Visitable;
import java.util.ArrayList;
import java.util.List;

public class Parametres implements Visitable {
    private List<Parametre> liste;

    public Parametres(List<Parametre> lstParams) {
        this.liste = new ArrayList<>();
        this.liste.addAll(lstParams);
    }

    public List<Parametre> getListeParametres() {
        return this.liste;
    } 
}
