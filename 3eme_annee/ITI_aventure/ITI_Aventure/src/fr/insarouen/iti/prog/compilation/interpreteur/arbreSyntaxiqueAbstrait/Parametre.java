package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

import fr.insarouen.iti.prog.patronsConception.visiteur.Visitable;

public abstract class Parametre implements Visitable {
    public abstract String getValeurParametre();
}