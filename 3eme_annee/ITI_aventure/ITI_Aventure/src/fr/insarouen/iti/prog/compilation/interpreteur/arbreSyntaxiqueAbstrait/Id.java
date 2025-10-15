package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

public class Id extends Parametre {
    private String param;

    public Id(String parametre) {
        this.param = parametre;
    }

    public String getValeurParametre() {
        return this.param;
    }
}