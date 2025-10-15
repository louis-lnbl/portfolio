package fr.insarouen.iti.prog.aventure.elements.vivants;

import java.util.Collection;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;


import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.elements.structure.VivantAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.structure.ObjetAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.objets.ObjetNonDeplacableException;
import fr.insarouen.iti.prog.aventure.ITIAventureException;

import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleException;

import fr.insarouen.iti.prog.aventure.elements.structure.PorteFermeException;
import fr.insarouen.iti.prog.aventure.elements.structure.PorteInexistanteDansLaPieceException;

import org.junit.Test;
import org.junit.Before;
import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.not;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.arrayContainingInAnyOrder;


public class TestVivant{

    private VivantConcret vivant1;
    private VivantConcret vivant2;
    private Objet objet1;
    private Objet objet2;
    private Objet objet3;
    private Objet objet4;
    private Monde monde1;
    private Piece piece1;
    private Piece piece2;
    private Piece piece3;
    private Porte porte12;
    private Porte porte23;
    @Before
    public void avantTest(){
        try{

            monde1 = new Monde("monde1");

            piece1 = new Piece("piece1", monde1);
            piece2 = new Piece("piece2", monde1);
            piece3 = new Piece("piece3", monde1);

            objet1 = new Objet("objet1", monde1){
                public boolean estDeplacable(){
                return true;
                }
            };

            objet2 = new Objet("objet2", monde1){
                public boolean estDeplacable(){
                return true;
                }
            };

            objet3 = new Objet("objet3", monde1){
                public boolean estDeplacable(){
                return true;
                }
            };

            objet4 = new Objet("objet4", monde1){
                public boolean estDeplacable(){
                return false;
                }
            };

            piece1.deposer(objet1);
            piece1.deposer(objet2);

            vivant1 = new VivantConcret("vivant1",monde1,100,100,piece1,objet1);
            vivant2 = new VivantConcret("vivant2", monde1, 100, 100, piece1);

            porte12 = new Porte("porte12", monde1, piece1, piece2);
            porte23 = new Porte("porte23", monde1, piece2, piece3);


        }catch (NomDEntiteDejaUtiliseDansLeMondeException e) {
            e.printStackTrace();

        }catch (EntiteDejaDansUnAutreMondeException e) {
            e.printStackTrace();

        }catch (VivantAbsentDeLaPieceException e) {
            e.printStackTrace();

        }

    }

    @Test
    public void testGetObjet() throws ObjetNonPossedeParLeVivantException{
        assertThat(vivant1.getObjet("objet1"),equalTo(objet1));
        assertThat(vivant1.getObjet("objet1"),not(equalTo(objet3)));

    }

    //erreur non comprehensible  (demander au prof)
    @Test(expected = ObjetNonPossedeParLeVivantException.class)
    public void testGetObjetObjetNonPossedeParLeVivantException() throws ObjetNonPossedeParLeVivantException{
        vivant1.getObjet("objet2");
    }

    @Test
    public void testGetObjets(){
        assertThat(vivant1.getObjets().toArray(),arrayContainingInAnyOrder(objet1));
    }

    @Test
    public void testPrendre() throws ObjetAbsentDeLaPieceException, ObjetNonDeplacableException, ObjetNonPossedeParLeVivantException{
        assertThat(vivant1.possede(objet2), is(false));
        vivant1.prendre(objet2);
        assertThat(vivant1.possede(objet2), is(true));
        vivant1.deposer(objet2);
        assertThat(vivant2.possede(objet2), is(false));
        vivant2.prendre("objet2");
        assertThat(vivant2.possede(objet2), is(true));
    }

    @Test(expected = ObjetAbsentDeLaPieceException.class)
    public void testPrendreObjetAbsentDeLaPieceExceptionObjet() throws ObjetAbsentDeLaPieceException, ObjetNonDeplacableException{
        piece2.deposer(objet3);
        vivant1.prendre(objet3);
    }

    @Test(expected = ObjetNonDeplacableException.class)
    public void testPrendreObjetNonDeplacableExceptionObjet() throws ObjetAbsentDeLaPieceException, ObjetNonDeplacableException{
        piece1.deposer(objet4);
        vivant1.prendre(objet4);
    }

    @Test(expected = ObjetAbsentDeLaPieceException.class)
    public void testPrendreObjetAbsentDeLaPieceExceptionNom() throws ObjetAbsentDeLaPieceException, ObjetNonDeplacableException,ObjetNonPossedeParLeVivantException{
        piece2.deposer(objet3);
        vivant1.prendre("objet3");
    }

    @Test(expected = ObjetNonDeplacableException.class)
    public void testPrendreObjetNonDeplacableExceptionNom() throws ObjetAbsentDeLaPieceException, ObjetNonDeplacableException, ObjetNonPossedeParLeVivantException{
        piece1.deposer(objet4);
        vivant1.prendre("objet4");
    }

    @Test
    public void testDeposer() throws ObjetNonPossedeParLeVivantException, ObjetAbsentDeLaPieceException, ObjetNonDeplacableException{
        assertThat(vivant1.possede(objet1), is(true));
        vivant1.deposer(objet1);
        assertThat(vivant1.possede(objet1), is(false));
        vivant1.prendre(objet1);
        assertThat(vivant1.possede(objet1), is(true));
        vivant1.deposer("objet1");
        assertThat(vivant1.possede(objet1), is(false));
    }

    @Test(expected = ObjetNonPossedeParLeVivantException.class)
    public void testDeposerObjetNonPossedeParLeVivantExceptionObjet() throws ObjetNonPossedeParLeVivantException{
        assertThat(vivant1.possede(objet2), is(false));
        vivant1.deposer(objet2);
    }

    @Test(expected = ObjetNonPossedeParLeVivantException.class)
    public void testDeposerObjetNonPossedeParLeVivantExceptionNom() throws ObjetNonPossedeParLeVivantException{
        assertThat(vivant1.possede(objet2), is(false));
        vivant1.deposer("objet2");
    }

    @Test
    public void testPossede(){
        assertThat(vivant1.possede(objet1), is(true));
        assertThat(vivant1.possede(objet2), is(false));
    }

    @Test
    public void testSetPiece(){
        assertThat(piece1.contientVivant(vivant1), is(true));
        assertThat(piece2.contientVivant(vivant1), is(false));
        vivant1.setPiece(piece2);
        assertThat(piece1.contientVivant(vivant1), is(false));
        assertThat(piece2.contientVivant(vivant1), is(true));
    }

    @Test
    public void testGetPiece(){
        assertThat(vivant1.getPiece(), equalTo(piece1));
        assertThat(vivant1.getPiece(), not(equalTo(piece2)));
    }

    @Test
    public void testFranchir() throws PorteFermeException, PorteInexistanteDansLaPieceException ,ActivationImpossibleException{
        assertThat(vivant1.getPiece(), equalTo(piece1));
        assertThat(vivant1.getPiece(), not(equalTo(piece2)));
        porte12.activer();
        vivant1.franchir(porte12);
        assertThat(vivant1.getPiece(), equalTo(piece2));
        assertThat(vivant1.getPiece(), not(equalTo(piece1)));
        vivant1.franchir("porte12");
        assertThat(vivant1.getPiece(), equalTo(piece1));
        assertThat(vivant1.getPiece(), not(equalTo(piece2)));
    }

    @Test(expected = PorteFermeException.class)
    public void testFranchirPorteFermeException() throws PorteFermeException, PorteInexistanteDansLaPieceException{
        assertThat(vivant1.getPiece(), equalTo(piece1));
        assertThat(vivant1.getPiece(), not(equalTo(piece2)));
        vivant1.franchir(porte12);
    }

    @Test(expected = PorteInexistanteDansLaPieceException.class)
    public void testFranchirPorteInexistanteDansLaPieceException() throws PorteFermeException, PorteInexistanteDansLaPieceException{
        assertThat(vivant1.getPiece(), equalTo(piece1));
        assertThat(vivant1.getPiece(), not(equalTo(piece2)));
        vivant1.franchir(porte23);
    }

}

class VivantConcret extends Vivant{

    public VivantConcret(String nom, Monde monde, int pointVie, int pointForce, Piece piece, Objet... objet) throws NomDEntiteDejaUtiliseDansLeMondeException, EntiteDejaDansUnAutreMondeException, VivantAbsentDeLaPieceException{
        super(nom,monde,pointVie, pointForce, piece,objet);
    }

    public void executer() throws ITIAventureException{

    }
}