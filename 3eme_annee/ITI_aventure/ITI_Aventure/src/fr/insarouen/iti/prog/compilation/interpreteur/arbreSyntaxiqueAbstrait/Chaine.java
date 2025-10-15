package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

public class Chaine extends Parametre {
    private String param;

    public Chaine(String parametre) {
        this.param = parametre;
    }

    public String getValeurParametre() {
        return this.param;
    }
}