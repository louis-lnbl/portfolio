package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

import fr.insarouen.iti.prog.patronsConception.visiteur.Visitable;
import java.util.ArrayList;
import java.util.List;

public class Config implements Visitable {
    private List<Affectation> liste;

    public Config(List<Affectation> lstAff) {
        this.liste = new ArrayList<>();
        this.liste.addAll(lstAff);
    }

    public List<Affectation> getAffectations() {
        return this.liste;
    } 
}
