package fr.insarouen.iti.prog.aventure.spaceopera.elements;


import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.vivants.Monstre;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;


public class Alien extends Monstre{

    public Alien(String nom, Monde monde, int pV, int pF, Piece piece) throws NomDEntiteDejaUtiliseDansLeMondeException {

        super(nom, monde, pV, pF, piece);
    }
}