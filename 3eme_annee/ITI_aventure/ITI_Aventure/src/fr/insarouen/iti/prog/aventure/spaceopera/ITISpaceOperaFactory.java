package fr.insarouen.iti.prog.aventure.spaceopera;

import fr.insarouen.iti.prog.aventure.spaceopera.elements.Galaxie;
import fr.insarouen.iti.prog.aventure.spaceopera.elements.Alien;
import fr.insarouen.iti.prog.aventure.spaceopera.elements.Badge;
import fr.insarouen.iti.prog.aventure.spaceopera.elements.LecteurBadge;
import fr.insarouen.iti.prog.aventure.spaceopera.elements.VaisseauSpatial;
import fr.insarouen.iti.prog.aventure.spaceopera.elements.Teleporteur;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.vivants.Monstre;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;


import fr.insarouen.iti.prog.aventure.ITIAventureFactory;

public class ITISpaceOperaFactory extends ITIAventureFactory{

    @Override
    public Monde creerMonde(String nom)  {
        return new Galaxie(nom);
    }

    @Override
    public Piece creerPiece(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new VaisseauSpatial(nom, monde);
    }

    @Override
    public Porte creerPorte(String nom, Monde monde, Piece pieceA, Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Teleporteur(nom, monde, pieceA, pieceB);
    }

    @Override
    public Porte creerPorte(String nom, Monde monde, Serrure serrure, Piece pieceA, Piece pieceB) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Teleporteur(nom, monde, serrure, pieceA, pieceB);
    }

    @Override
    public Monstre creerMonstre(String nom, Monde monde, int pV, int pF, Piece piece) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new Alien(nom, monde, pV, pF, piece);
    }

    @Override
    public Serrure creerSerrure(Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return new LecteurBadge(monde.genererNom("lecteur_badge"), monde);
    }


    @Override
    public Cle creerCle(Serrure serrure) throws NomDEntiteDejaUtiliseDansLeMondeException {
        return serrure.creerCle();

    }


}