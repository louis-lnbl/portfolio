
package fr.insarouen.iti.prog.compilation.interpreteur.configuration;

import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Affectation;
import fr.insarouen.iti.prog.compilation.interpreteur.analyseurs.ParseException;
import fr.insarouen.iti.prog.compilation.interpreteur.analyseurs.AnalyseurSyntaxique;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Config;
import java.util.List;
import java.util.ArrayList;
import java.io.StringReader;


public class Configuration{
    private List<Affectation> lAffectation;

    public Configuration(String Configuration) throws ParseException{
        fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Config ast;

        AnalyseurSyntaxique as = new AnalyseurSyntaxique(new StringReader(Configuration));
        ast = as.config();
        this.lAffectation = ast.getAffectations();
    }

    public List<Affectation> getAffectations(){
        return this.lAffectation;
    }
}