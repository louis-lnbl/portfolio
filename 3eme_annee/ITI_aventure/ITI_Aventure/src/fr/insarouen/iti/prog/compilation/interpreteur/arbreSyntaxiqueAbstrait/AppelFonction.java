package fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait;

public class AppelFonction extends Parametre {
    private String idf;
    private Parametres params;

    public AppelFonction(String idfonction, Parametres parametres) {
        this.idf = idfonction;
        this.params = parametres;
    }

    public String getIDF() {
        return this.idf;
    }

    public Parametres getListeParametres() {
        return this.params;
    }

    public String getValeurParametre() {
        return this.idf;
    }
}