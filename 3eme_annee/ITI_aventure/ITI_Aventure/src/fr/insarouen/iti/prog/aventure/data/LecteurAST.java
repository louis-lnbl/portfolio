package fr.insarouen.iti.prog.aventure.data;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EtatDuJeu;
import fr.insarouen.iti.prog.aventure.elements.Entite;
import fr.insarouen.iti.prog.aventure.elements.structure.ObjetAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.objets.ObjetNonDeplacableException;
import fr.insarouen.iti.prog.aventure.elements.objets.PiedDeBiche;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.vivants.JoueurHumain;
import fr.insarouen.iti.prog.aventure.elements.vivants.Monstre;
import fr.insarouen.iti.prog.aventure.elements.vivants.ObjetNonPossedeParLeVivantException;
import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFinVivantDansPiece;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFinVivantPossedeObjets;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Affectation;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.AppelFonction;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Chaine;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Config;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Constante;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Id;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.NbEntier;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Parametre;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Parametres;
import fr.insarouen.iti.prog.patronsConception.visiteur.Visiteur;
import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.HashMap;

public class LecteurAST implements Visiteur, Lecteur {
    private Config config;
    private Monde monde;
    private Collection<ConditionDeFin> conditions_de_fin = new ArrayList<>();
    private HashMap<String, String> tableDesNoms = new HashMap<>();

    public LecteurAST(Config unAST) throws Throwable {
        this.config = unAST;
        this.visiter();
    }

    public void visiter() throws Throwable  {
        for (Affectation uneAff : this.config.getAffectations()) {
            this.visiter(uneAff);  
        } 
    }   

    public void visiter(Affectation aff) throws Throwable  {
        this.visiter(aff.getNom());
        String id = aff.getNom().getValeurParametre();
        List<Parametre> params = aff.getAppelFonction().getListeParametres().getListeParametres();
        String nom = null;
        for (Parametre p : params) {
            if (p instanceof Chaine) {
                nom = ((Chaine)p).getValeurParametre();
                // On enlève les guillemets (juste pour la jouabilité)
                if (nom.length() >= 2 && nom.startsWith("\"") && nom.endsWith("\"")) {
                    nom = nom.substring(1, nom.length() - 1);
                }
                break;
            }
        }
        if (nom != null) {
            tableDesNoms.put(id, nom);
        }
        this.visiter(aff.getAppelFonction());
    }

    public void visiter(Id id) throws IdDejaUtiliseException {
        String idStr = id.getValeurParametre();
        if (tableDesNoms.containsKey(idStr)) {
            throw new IdDejaUtiliseException("Id déjà utilisé : " + idStr);
        }
    }

    public void visiter(AppelFonction appel) throws Throwable{
        List<Parametre> lstParams = appel.getListeParametres().getListeParametres();

        switch (appel.getIDF()){
            case "monde":
                creerMonde(lstParams);
                break;
            case "piece":
                creerPiece(lstParams);
                break;
            case "serrure" :
                creerSerrure(lstParams);
                break;           
            case "porte":
                creerPorte(lstParams);
                break;
            case "pied_de_biche":
                creerPiedDeBiche(lstParams);
                break; 
            case "cle":
                creerCle(lstParams);
                break;                  
            case "monstre":
                creerMonstre(lstParams);
                break;                  
            case "humain":
                creerHumain(lstParams);
                break;
            case "cdf_vivant_dans_piece":
                creerCdfVivantDansPiece(lstParams);
                break; 
            case "cdf_vivant_possede":
                creerCdfVivantPossede(lstParams);
                break; 
            case "cdf_conjonction":
                creerCdfConjonction(lstParams);
                break;
        }
    }    

    private void creerMonde(List<Parametre> lstParams) throws MauvaisParametreException {
        if (lstParams.size() != 1){
            throw new MauvaisParametreException("Mauvais nombre de parametres (monde)");
        }
        if (!(lstParams.get(0) instanceof Chaine)) {
            throw new MauvaisParametreException("Mauvais type de parametres (monde)");
        }
        else {
            String nomMonde = ((Chaine)lstParams.get(0)).getValeurParametre();
            if (nomMonde.length() >= 2 && nomMonde.startsWith("\"") && nomMonde.endsWith("\"")) {
                nomMonde = nomMonde.substring(1, nomMonde.length() - 1);
            }
            this.monde = new Monde(nomMonde);
        }
    }

    private void creerPiece(List<Parametre> lstParams) throws MauvaisParametreException, NomDEntiteDejaUtiliseDansLeMondeException {
        if (lstParams.size() < 2) {
            throw new MauvaisParametreException("Mauvais nombre de parametres (piece)");
        }
        if (!(lstParams.get(0) instanceof Id) || !(lstParams.get(1) instanceof Chaine)) {
            throw new MauvaisParametreException("Mauvais type de parametres (piece)");
        }
        String nomPiece = ((Chaine)lstParams.get(1)).getValeurParametre();
        if (nomPiece.length() >= 2 && nomPiece.startsWith("\"") && nomPiece.endsWith("\"")) {
            nomPiece = nomPiece.substring(1, nomPiece.length() - 1);
        }
        new Piece(nomPiece, this.getMonde());
    }

    private void creerSerrure(List<Parametre> lstParams) throws MauvaisParametreException, NomDEntiteDejaUtiliseDansLeMondeException {
        if (lstParams.size() != 1 && lstParams.size() != 2){
            throw new MauvaisParametreException("Mauvais nombre de parametres (serrure)");
        }
        if (!(lstParams.get(0) instanceof Id)) {
            throw new MauvaisParametreException("Mauvais type de parametres (serrure)");
        }
        if (lstParams.size() == 2 && !(lstParams.get(1) instanceof Chaine)) {
            throw new MauvaisParametreException("Mauvais type de parametres (serrure)");
        }
        if (lstParams.size() == 1) {
            new Serrure(this.getMonde());
        } else {
            String nomSerrure = lstParams.get(1).getValeurParametre();
            if (nomSerrure.length() >= 2 && nomSerrure.startsWith("\"") && nomSerrure.endsWith("\"")) {
                nomSerrure = nomSerrure.substring(1, nomSerrure.length() - 1);
            }
            new Serrure(nomSerrure, this.getMonde());
        }
    }

    private void creerPorte(List<Parametre> lstParams) throws MauvaisParametreException, NomDEntiteDejaUtiliseDansLeMondeException {
        if (lstParams.size() != 4 && lstParams.size() != 5){
            throw new MauvaisParametreException("Mauvais nombre de parametres (porte)");
        }
        if (!(lstParams.get(0) instanceof Id) ||
            !(lstParams.get(1) instanceof Chaine) ||
            !(lstParams.get(2) instanceof Id) ||
            !(lstParams.get(3) instanceof Id) ||
            (lstParams.size() == 5 && !(lstParams.get(4) instanceof AppelFonction))) {
            throw new MauvaisParametreException("Mauvais type de parametres (porte)");
        }
        String idA = ((Id)lstParams.get(2)).getValeurParametre();
        String idB = ((Id)lstParams.get(3)).getValeurParametre();
        Piece pieceA = (Piece)this.getMonde().getEntite(tableDesNoms.get(idA));
        Piece pieceB = (Piece)this.getMonde().getEntite(tableDesNoms.get(idB));

        if (lstParams.size() == 4){
            String nomPorte = ((Chaine)lstParams.get(1)).getValeurParametre();
            if (nomPorte.length() >= 2 && nomPorte.startsWith("\"") && nomPorte.endsWith("\"")) {
                nomPorte = nomPorte.substring(1, nomPorte.length() - 1);
            }
            new Porte(nomPorte, this.getMonde(), pieceA, pieceB);
        }
        else { 
            Serrure serrure = new Serrure(this.getMonde());
            String nomPorte = ((Chaine)lstParams.get(1)).getValeurParametre();
            if (nomPorte.length() >= 2 && nomPorte.startsWith("\"") && nomPorte.endsWith("\"")) {
                nomPorte = nomPorte.substring(1, nomPorte.length() - 1);
            }
            new Porte(nomPorte, this.getMonde(), serrure, pieceA, pieceB);
        }
    }

    private void creerPiedDeBiche(List<Parametre> lstParams) throws MauvaisParametreException, NomDEntiteDejaUtiliseDansLeMondeException {
        if (lstParams.size() != 2){
            throw new MauvaisParametreException("Mauvais nombre de parametres (pied_de_biche)");
        }
        if (!(lstParams.get(0) instanceof Id) || !(lstParams.get(1) instanceof Chaine)) {
            throw new MauvaisParametreException("Mauvais type de parametres (pied_de_biche)");
        }
        else {
            String nomPdb = lstParams.get(1).getValeurParametre();
            if (nomPdb.length() >= 2 && nomPdb.startsWith("\"") && nomPdb.endsWith("\"")) {
                nomPdb = nomPdb.substring(1, nomPdb.length() - 1);
            }
            new PiedDeBiche(nomPdb, this.getMonde());
        }
    }

    private void creerCle(List<Parametre> lstParams) throws MauvaisParametreException, NomDEntiteDejaUtiliseDansLeMondeException {
        if (lstParams.size() != 2){
            throw new MauvaisParametreException("Mauvais nombre de parametres (cle)");
        }
        if (!(lstParams.get(0) instanceof Id) || !(lstParams.get(1) instanceof Id)) {
            throw new MauvaisParametreException("Mauvais type de parametres (cle)");
        }
        else {
            Porte porte = (Porte)this.getMonde().getEntite(tableDesNoms.get(((Id)lstParams.get(0)).getValeurParametre()));
            Piece piece = (Piece)this.getMonde().getEntite(tableDesNoms.get(((Id)lstParams.get(1)).getValeurParametre()));

            Cle cle = porte.getSerrure().creerCle();
            piece.deposer(cle);
        }
    }

    private void creerMonstre(List<Parametre> lstParams) throws MauvaisParametreException, NomDEntiteDejaUtiliseDansLeMondeException, ObjetAbsentDeLaPieceException, ObjetNonDeplacableException {
        if (lstParams.size() < 5) {
            throw new MauvaisParametreException("Mauvais nombre de parametres (monstre)");
        }
        if (!(lstParams.get(0) instanceof Id) ||
            !(lstParams.get(1) instanceof Chaine) ||
            !(lstParams.get(2) instanceof NbEntier) ||
            !(lstParams.get(3) instanceof NbEntier) ||
            !(lstParams.get(4) instanceof Id)) {
            throw new MauvaisParametreException("Mauvais type de parametres (monstre)");
        }
        Piece pieceMonstre = (Piece)this.getMonde().getEntite(tableDesNoms.get(((Id)lstParams.get(4)).getValeurParametre()));
        String nomMonstre = ((Chaine)lstParams.get(1)).getValeurParametre();
        if (nomMonstre.length() >= 2 && nomMonstre.startsWith("\"") && nomMonstre.endsWith("\"")) {
            nomMonstre = nomMonstre.substring(1, nomMonstre.length() - 1);
        }
        Monstre monstre = new Monstre(nomMonstre, this.getMonde(),
            Integer.valueOf(((NbEntier)lstParams.get(2)).getValeurParametre()), Integer.valueOf(((NbEntier)lstParams.get(3)).getValeurParametre()), pieceMonstre);
        for (int i=5; i<lstParams.size(); i++) {
            if (!(lstParams.get(i) instanceof Id)) {
                throw new MauvaisParametreException("Mauvais type de parametres (monstre-objets)");
            }
            monstre.prendre(((Id)lstParams.get(i)).getValeurParametre());
        }
    }

    private void creerHumain(List<Parametre> lstParams) throws MauvaisParametreException, NomDEntiteDejaUtiliseDansLeMondeException, ObjetAbsentDeLaPieceException, ObjetNonDeplacableException {
        if (lstParams.size() < 5) {
            throw new MauvaisParametreException("Mauvais nombre de parametres (humain)");
        }
        if (!(lstParams.get(0) instanceof Id) ||
            !(lstParams.get(1) instanceof Chaine) ||
            !(lstParams.get(2) instanceof NbEntier) ||
            !(lstParams.get(3) instanceof NbEntier) ||
            !(lstParams.get(4) instanceof Id)) {
            throw new MauvaisParametreException("Mauvais type de parametres (humain)");
        }
        Piece pieceHumain = (Piece)this.getMonde().getEntite(tableDesNoms.get(((Id)lstParams.get(4)).getValeurParametre()));
        String nomHumain = ((Chaine)lstParams.get(1)).getValeurParametre();
        if (nomHumain.length() >= 2 && nomHumain.startsWith("\"") && nomHumain.endsWith("\"")) {
            nomHumain = nomHumain.substring(1, nomHumain.length() - 1);
        }
        JoueurHumain humain = new JoueurHumain(nomHumain, this.getMonde(),
            Integer.valueOf(((NbEntier)lstParams.get(2)).getValeurParametre()), Integer.valueOf(((NbEntier)lstParams.get(3)).getValeurParametre()), pieceHumain);
        for (int i=5; i<lstParams.size(); i++){
            if (!(lstParams.get(i) instanceof Id)) {
                throw new MauvaisParametreException("Mauvais type de parametres (humain-objets)");
            }
            humain.prendre(((Id)lstParams.get(i)).getValeurParametre());
        }
    }

    private void creerCdfVivantDansPiece(List<Parametre> lstParams) throws MauvaisParametreException {
        if (lstParams.size() != 3){
            throw new MauvaisParametreException("Mauvais nombre de parametres (cdf_vivant_dans_piece)");
        }
        if (!(lstParams.get(0) instanceof Constante) ||
            !(lstParams.get(1) instanceof Id) ||
            !(lstParams.get(2) instanceof Id)) {
            throw new MauvaisParametreException("Mauvais type de parametres (cdf_vivant_dans_piece)");
        }
        else {
            EtatDuJeu etatDuJeu = this.getEtat(((Constante)lstParams.get(0)).getValeurParametre());
            Vivant vivant = (Vivant)this.getMonde().getEntite(tableDesNoms.get(((Id)lstParams.get(1)).getValeurParametre()));
            Piece piece = (Piece)this.getMonde().getEntite(tableDesNoms.get(((Id)lstParams.get(2)).getValeurParametre()));
            ConditionDeFinVivantDansPiece cdf_vivant_dans_piece = new ConditionDeFinVivantDansPiece(etatDuJeu, vivant, piece);
            this.conditions_de_fin.add(cdf_vivant_dans_piece);
        }
    }

    private void creerCdfVivantPossede(List<Parametre> lstParams) throws MauvaisParametreException, ObjetNonPossedeParLeVivantException {
        if (lstParams.size() < 3){
            throw new MauvaisParametreException("Mauvais nombre de parametres (cdf_vivant_possede)");
        }
        if (!(lstParams.get(0) instanceof Constante) ||
            !(lstParams.get(1) instanceof Id)) {
            throw new MauvaisParametreException("Mauvais type de parametres (cdf_vivant_possede)");
        }
        for (int i=2; i<lstParams.size(); i++) {
            if (!(lstParams.get(i) instanceof Id)) {
                throw new MauvaisParametreException("Mauvais type de parametres (cdf_vivant_possede-objets)");
            }
        }
        EtatDuJeu etatDuJeuPossede = this.getEtat(((Constante)lstParams.get(0)).getValeurParametre());
        Vivant vivantPossede = (Vivant)this.getMonde().getEntite(tableDesNoms.get(((Id)lstParams.get(1)).getValeurParametre()));
        List<Objet> objets = new ArrayList<>();
        for (int i=2;i<lstParams.size();i++){
            Objet o = vivantPossede.getObjet(((Id)lstParams.get(i)).getValeurParametre());
            objets.add(o);
        }
        ConditionDeFinVivantPossedeObjets cdf_vivant_possede = new ConditionDeFinVivantPossedeObjets(etatDuJeuPossede, vivantPossede, objets.toArray(new Objet[0]));
        this.conditions_de_fin.add(cdf_vivant_possede);
    }

    private void creerCdfConjonction(List<Parametre> lstParams) throws MauvaisParametreException {
        if (lstParams.size() < 2){
            throw new MauvaisParametreException("Mauvais nombre de parametres (cdf_conjonction)");
        }
        EtatDuJeu etatDuJeuConj = this.getEtat(((Constante)lstParams.get(0)).getValeurParametre());
        for (int i=1; i<lstParams.size(); i++) {
            if (!(lstParams.get(i) instanceof Id)) {
                throw new MauvaisParametreException("Mauvais type de parametres (cdf_conjonction)");
            }
        }
        // TODO: Implémenter la logique de la conjonction si nécessaire
    }
    
    private EtatDuJeu getEtat(String etatStr){
        switch(etatStr){
            case "ECHEC":
                return EtatDuJeu.ECHEC;
            case "SUCCES":
                return EtatDuJeu.SUCCES;
            case "ENCOURS":
                return EtatDuJeu.ENCOURS;
            default:
                return null;
        }
    }

    public Monde getMonde() {
        return this.monde;
    }

    public Collection<ConditionDeFin> getConditionsDeFin(){
        return this.conditions_de_fin;
    }

}
