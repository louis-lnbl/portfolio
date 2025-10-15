package fr.insarouen.iti.prog.aventure.data;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;
import java.util.Collection;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.PiedDeBiche;
import fr.insarouen.iti.prog.aventure.elements.vivants.JoueurHumain;
import fr.insarouen.iti.prog.aventure.elements.Etat;

public class EnregistreurBD implements Enregistreur{

    private String base;

    public EnregistreurBD(String base) throws Throwable {
        this.base = base;
        Connection connection = connexionBD(base);
        PreparedStatement pst = null;

        String[] listeTable = {"MONDE", "PORTE", "PIEDDEBICHE", "JOUEURHUMAIN", "PIECE", "JOUEURPOSSEDEPDB", "PIECECONTIENTPDB"};
        for (String s : listeTable) {
            String res = String.format("DELETE FROM %s", s);
            pst = connection.prepareStatement(res);
            pst.executeUpdate();
            pst.close();
        }

        connection.close();
    }

    public void enregistrer(Monde monde, Collection<ConditionDeFin> conditionsDeFin) throws Throwable {
        Connection connection = connexionBD(this.base);

        PreparedStatement pstMonde = connection.prepareStatement("INSERT INTO MONDE VALUES (?)");
        pstMonde.setString(1, monde.getNom());
        pstMonde.executeUpdate();
        pstMonde.close();

        //TODO : mettre en méthode
        PreparedStatement pstPorte = null;
        for (Porte porte : monde.getEntites().stream().filter(elt -> elt instanceof Porte).map(elt -> (Porte) elt).toList()) {
                pstPorte = connection.prepareStatement("INSERT INTO PORTE VALUES (?, ?, ?)");
                pstPorte.setString(1, porte.getNom());
                if (porte.getEtat() == Etat.OUVERT || porte.getEtat() == Etat.FERME) {
                    pstPorte.setString(2, porte.getEtat().toString());
                }
                else {
                    pstPorte.setString(2, Etat.OUVERT.toString());
                }
                pstPorte.setString(3, monde.getNom());
                pstPorte.executeUpdate();
                pstPorte.close();
        }

        PreparedStatement pstPiece, pstPiedDeBiche, pstPiecePossedePDB, pstPiecePossedePorte = null;
        for (Piece piece : monde.getEntites().stream().filter(elt -> elt instanceof Piece).map(elt -> (Piece) elt).toList()) {
            pstPiece = connection.prepareStatement("INSERT INTO PIECE VALUES (?, ?)");
            pstPiece.setString(1, piece.getNom());
            pstPiece.setString(2, monde.getNom());
            pstPiece.executeUpdate();
            pstPiece.close();
            for (Porte porte : piece.getPortes()) {
                pstPiecePossedePorte = connection.prepareStatement("INSERT INTO PIECEPOSSEDEPORTE VALUES (?, ?)");
                pstPiecePossedePorte.setString(1, porte.getNom());
                pstPiecePossedePorte.setString(2, piece.getNom());
                pstPiecePossedePorte.executeUpdate();
                pstPiecePossedePorte.close();
            }
            for (PiedDeBiche pdb : piece.getObjets().stream().filter(elt -> elt instanceof PiedDeBiche).map(elt -> (PiedDeBiche) elt).toList()) {
                pstPiedDeBiche = connection.prepareStatement("INSERT INTO PIEDDEBICHE VALUES (?, ?, ?)");
                pstPiedDeBiche.setString(1, pdb.getNom());
                pstPiedDeBiche.setBoolean(2, pdb.estDeplacable());
                pstPiedDeBiche.setString(3, piece.getNom());
                pstPiedDeBiche.executeUpdate();
                pstPiedDeBiche.close();

                pstPiecePossedePDB = connection.prepareStatement("INSERT INTO PIECECONTIENTPDB VALUES (?, ?)");
                pstPiecePossedePDB.setString(1, pdb.getNom());
                pstPiecePossedePDB.setString(2, piece.getNom());
                pstPiecePossedePDB.executeUpdate();
                pstPiecePossedePDB.close();
            }
        }

        PreparedStatement pstJoueurHumain, pstJoueurPossedePDB = null;
        for (JoueurHumain jh : monde.getExecutables().stream().filter(elt -> elt instanceof JoueurHumain).map(elt -> (JoueurHumain) elt).toList()) {
            pstJoueurHumain = connection.prepareStatement("INSERT INTO JOUEURHUMAIN VALUES (?, ?, ?, ?, ?)");
            pstJoueurHumain.setString(1, jh.getNom());
            pstJoueurHumain.setInt(2, jh.getPointVie());
            pstJoueurHumain.setInt(3, jh.getPointForce());
            pstJoueurHumain.setString(4, monde.getNom());
            pstJoueurHumain.setString(5, jh.getPiece().getNom());
            pstJoueurHumain.executeUpdate();
            pstJoueurHumain.close();
            for (PiedDeBiche pdb : jh.getObjets().stream().filter(elt -> elt instanceof PiedDeBiche).map(elt -> (PiedDeBiche) elt).toList()) {
                pstJoueurPossedePDB = connection.prepareStatement("INSERT INTO JOUEURPOSSEDEPDB VALUES (?, ?)");
                pstJoueurPossedePDB.setString(1, pdb.getNom());
                pstJoueurPossedePDB.setString(2, jh.getNom());
                pstJoueurPossedePDB.executeUpdate();
                pstJoueurPossedePDB.close();
            }
        }

        connection.close();
    }

    private Connection connexionBD(String base) throws Throwable {
        Connection connection;
        String lien = String.format("jdbc:postgresql://iti-pg.insa-rouen.fr:5432/%s", base);
        connection = DriverManager.getConnection(lien, base, base);
        return connection;
    }
}