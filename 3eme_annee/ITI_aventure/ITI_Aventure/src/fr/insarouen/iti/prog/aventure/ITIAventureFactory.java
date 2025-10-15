package fr.insarouen.iti.prog.aventure;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.vivants.Monstre;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;


public class ITIAventureFactory {


    public Monde creerMonde(String nom)  {
        return new Monde(nom);
    }

    public Piece creerPiece(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Piece(nom, monde);
    }

    public Porte creerPorte(String nom, Monde monde, Piece pieceA, Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Porte(nom, monde, pieceA, pieceB);
    }

    public Porte creerPorte(String nom, Monde monde, Serrure serrure, Piece pieceA, Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Porte(nom, monde, serrure, pieceA, pieceB);
    }

    public Monstre creerMonstre(String nom, Monde monde, int pV, int pF, Piece piece) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Monstre(nom, monde, pV, pF, piece);
    }

    public Serrure creerSerrure(Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Serrure(monde);
    }

    public Cle creerCle(Serrure serrure) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return serrure.creerCle();

    }


}