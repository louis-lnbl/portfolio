package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

public class Constante extends Parametre {
    private String param;

    public Constante(String parametre) {
        this.param = parametre;
    }

    public String getValeurParametre() {
        return this.param;
    }
}