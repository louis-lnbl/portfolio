package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

public class NbEntier extends Parametre {
    private String param;

    public NbEntier(String parametre) {
        this.param = parametre;
    }

    public String getValeurParametre() {
        return this.param;
    }
}