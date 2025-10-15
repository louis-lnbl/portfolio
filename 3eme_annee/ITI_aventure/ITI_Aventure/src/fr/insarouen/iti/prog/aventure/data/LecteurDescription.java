package fr.insarouen.iti.prog.aventure.data;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.ITIAventureFactory;
import fr.insarouen.iti.prog.aventure.spaceopera.ITISpaceOperaFactory;
import fr.insarouen.iti.prog.aventure.data.Lecteur;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.elements.Entite;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.vivants.JoueurHumain;

import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFinVivantDansPiece;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFinVivantDansPieceEtPossedeObjets;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFinVivantMort;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFinVivantPossedeObjets;


import fr.insarouen.iti.prog.aventure.EtatDuJeu;
import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;


import java.io.Reader;
import java.io.IOException;
import java.util.Scanner;

import java.util.List;
import java.util.ArrayList;
import java.util.Collection;



/**
 * La classe LecteurDescription permet de lire la description textuelle d’un monde
 * et d’en construire dynamiquement les entités (monde, pièces, portes, joueurs, etc.)
 * à partir d’un flux de caractères.
 *
 *
 */

public class LecteurDescription implements Lecteur{

    private Monde monde = null;
    private Collection<ConditionDeFin> conditionsDeFin = new ArrayList<>();
    private ITIAventureFactory factory;

    public LecteurDescription(Reader reader)throws IOException,NomDEntiteDejaUtiliseDansLeMondeException{

        Scanner sc = new Scanner(reader);

        if (sc.hasNextLine()) {
            String ligne = sc.nextLine();
            switch (ligne) {
                case "ITISpaceOpera":
                    this.factory = new ITISpaceOperaFactory();
                    break;
                case "ITIAventure":
                default:
                    this.factory = new ITIAventureFactory();
                    break;
            }
        }
        while (sc.hasNextLine()) {
                String ligne = sc.nextLine();
                Scanner scLigne = new Scanner(ligne);
                String type = scLigne.next();

                switch (type){
                    case "Monde":
                        this.creerMonde(scLigne.next());
                        break;
                    case "Piece":
                        this.creerPiece(scLigne.next());
                        break;
                    case "PorteSerrure":
                        this.creerPorteSerrure(scLigne.next(),scLigne.next(),scLigne.next());
                        break;
                    case "Porte":
                        this.creerPorte(scLigne.next(),scLigne.next(),scLigne.next());
                        break;
                    case "Cle":
                        this.creerUneCle(scLigne.next(),scLigne.next());
                        break;
                    case "JoueurHumain":
                        this.creerJoueurHumain(scLigne.next(),scLigne.nextInt(),scLigne.nextInt(),scLigne.next());
                        break;
                    case "ConditionDeFinVivantDansPiece":
                        this.ajouterConditionVivantDansPiece(scLigne.next(), scLigne.next(), scLigne.next());
                        break;
                    case "ConditionDeFinVivantDansPieceEtPossedeObjets":
                        this.ajouterConditionVivantDansPieceEtPossedeObjets(scLigne);
                        break;
                    case "ConditionDeFinVivantMort":
                        this.ajouterConditionVivantMort(scLigne.next(), scLigne.next());
                        break;
                    case "ConditionDeFinVivantPossedeObjets":
                        this.ajouterConditionVivantPossedeObjets(scLigne);
                        break;
                    default:
                        break;
                }
        
        }
        sc.close();
    }

    /**
     * Retourne le monde construit à partir de la description.
     * 
     * @return le monde lu.
     */
    @Override
    public Monde getMonde(){
        return this.monde;
    }

    /**
     * crée le monde à partir du nom donné
     * 
     * @param nom du monde
     */
    private void creerMonde(String nom){
        this.monde = factory.creerMonde(nom);
    }

    /**
     * crée la pièce
     * 
     * @param nom de la pièce
     */
    private void creerPiece(String nom){
        try{
            Piece piece = factory.creerPiece(nom,this.getMonde());
        }catch (NomDEntiteDejaUtiliseDansLeMondeException e){
            e.printStackTrace();
        }
    }



    private void creerPorteSerrure(String nom, String pieceA, String pieceB){
        
        try{
            Serrure laSerrure = factory.creerSerrure(this.getMonde());
            Piece laPieceA = (Piece)(this.getMonde().getEntite(pieceA));
            Piece laPieceB = (Piece)(this.getMonde().getEntite(pieceB));
            Porte porteSerrure = factory.creerPorte(nom,this.getMonde(),laSerrure,laPieceA,laPieceB);
        }catch (NomDEntiteDejaUtiliseDansLeMondeException e){
            e.printStackTrace();
        }
    }


    /**
     * Crée une porte avec serrure entre deux pièces.
     * @param nom le nom de la porte
     *@param pieceA la première pièce
     * @param pieceB la deuxième pièce
    */ 
    private void creerPorte(String nom, String pieceA, String pieceB){
        
        try{
            Piece laPieceA = (Piece)(this.getMonde().getEntite(pieceA));
            Piece laPieceB = (Piece)(this.getMonde().getEntite(pieceB));
            Porte porte = factory.creerPorte(nom,this.getMonde(),laPieceA,laPieceB);
        }catch (NomDEntiteDejaUtiliseDansLeMondeException e){
            e.printStackTrace();
        }
    }

    /**
     * Crée une clé correspondant à une porte et la dépose dans une pièce.
     * @param nomPorte le nom de la porte
     * @param nomPiece le nom de la pièce où déposer la clé
    */

    private void creerUneCle(String nomPorte, String nomPiece){
        try{
            Porte laPorte = (Porte)(this.getMonde().getEntite(nomPorte));
            Serrure laSerrure = laPorte.getSerrure();
            Cle laCle = laSerrure.creerCle();
            Piece laPiece = (Piece)(this.getMonde().getEntite(nomPiece));
            laPiece.deposer(laCle);
        }catch (NomDEntiteDejaUtiliseDansLeMondeException e){
            e.printStackTrace();
        }
    }
    
    /**
     * Crée un joueur humain avec les paramètres donnés et l'ajoute au monde.
     * @param nomHumain le nom du joueur
     * @param lesPointsDeVie les points de vie
     * @param lesPointsDeForce les points de force
     * @param nomPiece le nom de la pièce où se trouve le joueur
    */
    private void creerJoueurHumain(String nomHumain, int lesPointsDeVie, int lesPointsDeForce,String nomPiece){
        try{
            Piece laPiece = (Piece)(this.getMonde().getEntite(nomPiece));
            JoueurHumain joueur = new JoueurHumain(nomHumain,this.getMonde(),lesPointsDeVie,lesPointsDeForce,laPiece);
        }catch (NomDEntiteDejaUtiliseDansLeMondeException e){
            e.printStackTrace();
        }
    }

    /**
     * retourne les conditions de fin.
     *
     * @return retourne une collection de ConditionsDeFin.
     * 
    */

    @Override
    public Collection<ConditionDeFin> getConditionsDeFin(){

        return this.conditionsDeFin;

    }

    /**
     * Renvoie l'état du jeu correspondant à une chaîne de caractères.
     * @param etatStr la chaîne représentant l'étaT
     * @return l'état du jeu correspondant, ou null si inconnu
    */

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

    /**
     * Ajoute une condition : un vivant doit être dans une pièce donnée.
     * @param etat l'état du jeu à associer à la condition
     * @param nomVivant le nom du vivant concerné
     * @param nomPiece le nom de la pièce concernée
    */
    private void ajouterConditionVivantDansPiece(String etat, String nomVivant, String nomPiece){
        Vivant leVivant = (Vivant)(this.getMonde().getEntite(nomVivant));
        Piece laPiece = (Piece)(this.getMonde().getEntite(nomPiece));
        EtatDuJeu lEtat = this.getEtat(etat);
        ConditionDeFinVivantDansPiece laCondition = new ConditionDeFinVivantDansPiece(lEtat, leVivant, laPiece);
        this.getConditionsDeFin().add(laCondition);
    }

    /**
     * Ajoute une condition  : un vivant doit être dans une pièce donnée et posséder certains objets.
     * @param ligneScanner le scanner contenant les paramètres de la condition
    */
    private void ajouterConditionVivantDansPieceEtPossedeObjets(Scanner ligneScanner){
        EtatDuJeu etat = this.getEtat(ligneScanner.next());
        Vivant vivant = (Vivant)this.monde.getEntite(ligneScanner.next());          
        Piece piece = (Piece)this.monde.getEntite(ligneScanner.next());
        List<Objet> lObj = new ArrayList<>();
        do{
            lObj.add((Objet)this.monde.getEntite(ligneScanner.next()));
        } while(ligneScanner.hasNext());
        Objet[] tabObj = lObj.toArray(new Objet[lObj.size()]);
        this.conditionsDeFin.add(new ConditionDeFinVivantDansPieceEtPossedeObjets(etat, vivant, piece, tabObj));
    }

    /**
     * Ajoute une condition de fin : un vivant doit être mort.
     * @param etatStr l'état du jeu à associer à la condition
     * @param vivantStr le nom du vivant concerné
    */
    private void ajouterConditionVivantMort(String etatStr, String vivantStr){
        EtatDuJeu etat = this.getEtat(etatStr);
        Vivant vivant = (Vivant)this.monde.getEntite(vivantStr);
        this.conditionsDeFin.add(new ConditionDeFinVivantMort(etat, vivant));
    }

    /**
     * Ajoute une condition de fin : un vivant doit posséder certains objets.
     * @param sc le scanner contenant les paramètres de la condition
    */
    private void ajouterConditionVivantPossedeObjets(Scanner ligneScanner){
        EtatDuJeu etat = this.getEtat(ligneScanner.next());
        Vivant vivant = (Vivant)this.monde.getEntite(ligneScanner.next());          
        List<Objet> lObj = new ArrayList<>();
        do{
            lObj.add((Objet)this.monde.getEntite(ligneScanner.next()));
        } while(ligneScanner.hasNext());
        Objet[] tabObj = lObj.toArray(new Objet[lObj.size()]);
        this.conditionsDeFin.add(new ConditionDeFinVivantPossedeObjets(etat, vivant, tabObj));
    }
}