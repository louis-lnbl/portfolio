package fr.insarouen.iti.prog.aventure.spaceopera.elements;



import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.Monde;

public class Teleporteur extends Porte{

    public Teleporteur(String nom, Monde monde, Piece pieceA, Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException {

        super(nom, monde, pieceA, pieceB);
    }


    public Teleporteur(String nom, Monde monde, Serrure serrure, Piece pieceA, Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException {

        super(nom, monde, serrure, pieceA, pieceB);
    }
}