package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

import fr.insarouen.iti.prog.patronsConception.visiteur.Visitable;

public class Affectation implements Visitable {
    private Id nom;
    private AppelFonction appel;

    public Affectation(Id nom, AppelFonction appelFct) {
        this.nom = nom;
        this.appel = appelFct;
    }

    public Id getNom() {
        return this.nom;
    }

    public AppelFonction getAppelFonction() {
        return this.appel;
    }
}
