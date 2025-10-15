
package fr.insarouen.iti.prog.compilation.interpreteur.configuration;

import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Affectation;
import fr.insarouen.iti.prog.compilation.interpreteur.analyseurs.ParseException;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;


public class Main {
    
    private static boolean parametresOK(String[] args) {
        if (args.length != 1)
            return false;
        File f = new File(args[0]);
        return true;
    }
    
    private static void traiterFichier(String nomFichierTexte) {
        try {
            BufferedReader fluxTexte = new BufferedReader(new FileReader(nomFichierTexte));
            System.out.println("contenu du fichier:");
            String texte = fluxTexte.lines().collect(Collectors.joining("\n"));
            Configuration configuration = new Configuration(texte);
            System.out.println(configuration);
            for(Affectation a : configuration.getAffectations()){
                System.out.println(a);
            }
            fluxTexte.close();
        } catch (ParseException e) {
            System.err.println(e);
        } catch (FileNotFoundException e) {         
        } catch (Throwable e) {        
        }
    }
    
    
    private static void afficherAide() {
        System.out.println("Mauvaise utilisation de l'interpreteur.");
    }
    
    public static void main(String[] args) throws ParseException {
        if (parametresOK(args)) 
            traiterFichier(args[0]);
        else
            afficherAide();
    }
}
