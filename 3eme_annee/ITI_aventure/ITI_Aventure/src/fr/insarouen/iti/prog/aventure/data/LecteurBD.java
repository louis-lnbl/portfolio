package fr.insarouen.iti.prog.aventure.data;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.vivants.JoueurHumain;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.Etat;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.PiedDeBiche;
import fr.insarouen.iti.prog.aventure.ITIAventureException;


import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.lang.ClassNotFoundException;

import java.util.Collection;


public class LecteurBD implements Lecteur {
     private Monde monde;
     private Connection connection;


     //Lecture des Pieces
        private void lecturePieces() throws SQLException, ClassNotFoundException, ITIAventureException{
            PreparedStatement pstPiece = connection.prepareStatement( " SELECT * FROM PIECE");
            ResultSet tablePiece = pstPiece.executeQuery();
            while (tablePiece.next()){           
                String nomDePiece = tablePiece.getString( "nomPiece" );
                System.out.println(nomDePiece);            
                Piece piece = new Piece(nomDePiece, monde);     
            }
            pstPiece.close();
        }
        
        

        //Lecture des Joueurs
        private void lectureJoueurs() throws SQLException, ClassNotFoundException, ITIAventureException{
            PreparedStatement pstJoueur = connection.prepareStatement( " SELECT * FROM JOUEURHUMAIN");
            ResultSet tableJoueur = pstJoueur.executeQuery();
            while (tableJoueur.next()){
            
                String nomDuJoueur = tableJoueur.getString( "nomJoueur" );
                String pieceDuJoueur = tableJoueur.getString( "nomPiece" );
                int ptV = tableJoueur.getInt( "ptVie" );
                int ptF = tableJoueur.getInt( "ptForce" );
                System.out.println( nomDuJoueur +  pieceDuJoueur + ptV + ptF );
            
                JoueurHumain joueur = new JoueurHumain(nomDuJoueur, monde , ptV , ptF, (Piece)(this.getMonde().getEntite(pieceDuJoueur)));
            }
            pstJoueur.close();
        }

        //Lecture des Portes
        private void lecturePortes() throws SQLException, ClassNotFoundException, ITIAventureException{
            PreparedStatement pstPorte = connection.prepareStatement( " SELECT * FROM Porte");
            PreparedStatement pstAssociationPortePiece = connection.prepareStatement( " SELECT * FROM PiecePossedePorte WHERE nomPorte = ?");
            ResultSet tablePorte = pstPorte.executeQuery();
            while (tablePorte.next()){
            
                String nomPorte = tablePorte.getString( "nomPorte" );

                pstAssociationPortePiece.setString(1, nomPorte);
                ResultSet tableAssociationPiecePorte = pstAssociationPortePiece.executeQuery(); 

                tableAssociationPiecePorte.next();
                String pieceA = tableAssociationPiecePorte.getString("nomPiece");
                tableAssociationPiecePorte.next();
                String pieceB = tableAssociationPiecePorte.getString("nomPiece");


                Etat etat = Etat.valueOf(tablePorte.getString( "etat" ));
                Porte porte = new Porte(nomPorte, monde, (Piece)this.monde.getEntite(pieceA),(Piece)this.monde.getEntite(pieceB));    

                if (etat.equals(Etat.OUVERT)) {        
                    porte.activer();
                }

                System.out.println( nomPorte + pieceA + pieceB);

            }
            pstPorte.close();
            pstAssociationPortePiece.close();
        }
    

        //Lecture des Pieds De Biche
        private void lecturePDB() throws SQLException, ClassNotFoundException, ITIAventureException{
            PreparedStatement pstPDB = connection.prepareStatement( " SELECT * FROM PIEDDEBICHE");
            ResultSet tablePDB = pstPDB.executeQuery();
            while (tablePDB.next()){
            
                String nomPDB = tablePDB.getString( "nomPDB" );
                String estDeplacable = tablePDB.getString("estDeplacable");
                System.out.println(nomPDB + estDeplacable);
                PiedDeBiche pdb = new PiedDeBiche(nomPDB, monde);

            }
            pstPDB.close();
        }
        
        /* lecture de JoueurPossedePiedDeBiche */
        private void lecturePossedePiedDeBiche() throws SQLException, ClassNotFoundException, ITIAventureException{
            PreparedStatement pstJoueurPossedePDB = connection.prepareStatement( " SELECT * FROM JOUEURPOSSEDEPDB");
            ResultSet tableJPDB = pstJoueurPossedePDB.executeQuery();
            while (tableJPDB.next()){
            
                String nomPDB = tableJPDB.getString( "nomPDB" );
                String nomJoueur = tableJPDB.getString("nomJoueur");
                System.out.println(nomPDB + nomJoueur);
                JoueurHumain joueurHumain =(JoueurHumain) this.monde.getEntite(nomJoueur);
                PiedDeBiche piedDeBiche = (PiedDeBiche) this.monde.getEntite(nomPDB);
                joueurHumain.getPiece().deposer(piedDeBiche);
                joueurHumain.prendre(piedDeBiche);

            }
            pstJoueurPossedePDB.close();
        }


        /* lecture de PieceContientPDB */
        private void lectureContientPDB() throws SQLException, ClassNotFoundException, ITIAventureException{
            PreparedStatement pstPieceContientPDB = connection.prepareStatement( " SELECT * FROM PIECECONTIENTPDB");
            ResultSet tablePiececontientPDB = pstPieceContientPDB.executeQuery();
            while (tablePiececontientPDB.next()){
            
                String nomPDB = tablePiececontientPDB.getString( "nomPDB" );
                String nomPiece = tablePiececontientPDB.getString("nomPiece");
                System.out.println(nomPDB + nomPiece);
                Piece piece =(Piece) this.monde.getEntite(nomPiece);
                PiedDeBiche pdb  = (PiedDeBiche) this.monde.getEntite(nomPDB);
                piece.deposer(pdb);

            }
            pstPieceContientPDB.close();
        }



   
    public LecteurBD(String base) throws SQLException, ClassNotFoundException, ITIAventureException{
        String lien = String.format("jdbc:postgresql://iti-pg.insa-rouen.fr:5432/%s", base);
        connection = DriverManager.getConnection(lien, base, base);
        
        PreparedStatement pstMonde = connection.prepareStatement( " SELECT * FROM Monde");
        ResultSet tableMonde = pstMonde.executeQuery();
        tableMonde.next();
        this.monde = new Monde(tableMonde.getString("nomMonde"));
        pstMonde.close();
        lecturePieces();
        lectureJoueurs();
        lecturePortes();
        lecturePDB();
        lecturePossedePiedDeBiche();
        lectureContientPDB();
        

        connection.close();



    }

    public Monde getMonde(){
        return monde;
    }

    public Collection<ConditionDeFin> getConditionsDeFin(){
        return null;
    }
}

