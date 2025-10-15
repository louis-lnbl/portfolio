package fr.insarouen.iti.prog.aventure.elements.structure;

import org.junit.After;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;
import java.awt.Color;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.CoreMatchers.not;
import static org.hamcrest.Matchers.arrayContainingInAnyOrder;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.ITIAventureException;
import fr.insarouen.iti.prog.aventure.MondeException;
import fr.insarouen.iti.prog.aventure.elements.objets.PiedDeBiche;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.vivants.Vivant;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import java.util.Collection;


public class TestPiece{
    private Monde monde;
    private Piece piece1;
    private Piece piece2;
    private Piece piece3;
    private PiedDeBiche objet1;
    private PiedDeBiche objet2;
    private PiedDeBiche objet3;
    private VivantConcret vivant1;
    private VivantConcret vivant2;
    private VivantConcret vivant3;
    private Porte porte12;
    private Porte porte23;

    @Before
    public void avantTest(){
        try{
            monde = new Monde("monde");

            piece1 = new Piece("piece1", monde);
            piece2 = new Piece("piece2", monde);
            piece3 = new Piece("piece3", monde);

            objet1 = new PiedDeBiche("objet1", monde);
            objet2 = new PiedDeBiche("objet2", monde);
            objet3 = new PiedDeBiche("objet3", monde);

            piece1.deposer(objet1);
            piece2.deposer(objet2);

            vivant1 = new VivantConcret("vivant1", monde, 150, 100, piece1, objet1, objet3);
            vivant2 = new VivantConcret("vivant2", monde, 150, 100, piece2);
            vivant3 = new VivantConcret("vivant3", monde, 150, 100, piece2);

            porte12 = new Porte("porte12", monde,piece1,piece2);
            porte23 = new Porte("porte23", monde,piece2,piece3);

        }catch (NomDEntiteDejaUtiliseDansLeMondeException e) {
            e.printStackTrace();

        }catch (EntiteDejaDansUnAutreMondeException e) {
            e.printStackTrace();

        }catch (VivantAbsentDeLaPieceException e) {
            e.printStackTrace();

        }
    }
    @Test
    public void testContientObjet(){
        assertThat(piece1.contientObjet(objet1), is(true));
        assertThat(piece1.contientObjet("objet1"), is(true));
        assertThat(piece1.contientObjet(objet2), is(false));
        assertThat(piece1.contientObjet("objet2"), is(false));

    }

    @Test
    public void testDeposerObjet(){
        assertThat(piece1.contientObjet(objet3), is(false));
        piece1.deposer(objet3);
        assertThat(piece1.contientObjet(objet3), is(true));
    }

    @Test
    public void testRetirerObjet() throws ObjetAbsentDeLaPieceException{
        assertThat(piece1.contientObjet(objet1), is(true));
        piece1.retirer(objet1);
        assertThat(piece1.contientObjet(objet1), is(false));
        assertThat(piece2.contientObjet(objet2), is(true));
        piece2.retirer("objet2");
        assertThat(piece2.contientObjet(objet2), is(false));
    }

    @Test(expected = ObjetAbsentDeLaPieceException.class)
    public void testRetirerObjetExceptionObjetAbsentDeLaPiece() throws ObjetAbsentDeLaPieceException{
        assertThat(piece1.contientObjet(objet3), is(false));
        piece1.retirer(objet3);
    }

    @Test
    public void testGetObjets(){
        piece1.deposer(objet3);
        assertThat(piece1.getObjets().toArray(), arrayContainingInAnyOrder(objet3, objet1));
        assertThat(piece1.getObjets().toArray(), not(arrayContainingInAnyOrder(objet2)));
    }

    @Test
    public void testContientVivant(){
        assertThat(piece1.contientVivant(vivant1), is(true));
        assertThat(piece1.contientVivant("vivant1"), is(true));
        assertThat(piece1.contientVivant(vivant2), is(false));
        assertThat(piece1.contientVivant("vivant2"), is(false));
    }

    @Test
    public void testEntrer(){
        assertThat(piece1.contientVivant(vivant2), is(false));
        assertThat(piece2.contientVivant(vivant2), is(true));
        piece1.entrer(vivant2);
        assertThat(piece1.contientVivant(vivant2), is(true));
        assertThat(piece2.contientVivant(vivant2), is(false));
    }

    @Test
    public void testSortir() throws VivantAbsentDeLaPieceException{
        assertThat(piece1.contientVivant(vivant1), is(true));
        piece1.sortir(vivant1);
        assertThat(piece1.contientVivant(vivant1), is(false));
        assertThat(piece2.contientVivant(vivant2), is(true));
        piece2.sortir("vivant2");
        assertThat(piece2.contientVivant(vivant2), is(false));
    }

    @Test(expected = VivantAbsentDeLaPieceException.class)
    public void testSortirVivantAbsentDeLaPieceExceptionVivant() throws VivantAbsentDeLaPieceException{
        assertThat(piece1.contientVivant(vivant2), is(false));
        piece1.sortir(vivant2);
    }

    @Test(expected = VivantAbsentDeLaPieceException.class)
    public void testSortirVivantAbsentDeLaPieceExceptionNom() throws VivantAbsentDeLaPieceException{
        assertThat(piece1.contientVivant("vivant2"), is(false));
        piece1.sortir("vivant2");
    }

    @Test
    public void testGetVivants(){
        piece1.entrer(vivant2);
        assertThat(piece1.getVivants().toArray(), arrayContainingInAnyOrder(vivant2, vivant1));
        assertThat(piece1.getVivants().toArray(), not(arrayContainingInAnyOrder(vivant3)));
    }

    @Test
    public void testAddPorte(){
        assertThat(piece1.getPortes().toArray(), arrayContainingInAnyOrder(porte12));
        assertThat(piece1.getPortes().toArray(), not(arrayContainingInAnyOrder(porte23)));
        assertThat(piece2.getPortes().toArray(), arrayContainingInAnyOrder(porte12,porte23));
        
    }

    @Test
    public void testALaPorte(){
        assertThat(piece1.aLaPorte(porte12), is(true));
        assertThat(piece1.aLaPorte(porte23), is(false));
        assertThat(piece1.aLaPorte("porte12"), is(true));
        assertThat(piece1.aLaPorte("porte23"), is(false));
    }

    @Test
    public void testGetPorte(){
        assertThat(piece1.getPorte("porte12"), equalTo(porte12));
        assertThat(piece1.getPorte("porte12"), not(equalTo(porte23)));
    }

    @Test
    public void testGetPortes(){
        assertThat(piece2.getPortes().toArray(), arrayContainingInAnyOrder(porte12,porte23));
    }

}


class VivantConcret extends Vivant{

    public VivantConcret(String nom, Monde monde, int pointVie, int pointForce, Piece piece, Objet... objet) throws NomDEntiteDejaUtiliseDansLeMondeException, EntiteDejaDansUnAutreMondeException, VivantAbsentDeLaPieceException{
        super(nom,monde,pointVie, pointForce, piece,objet);
    }

    public void executer() throws ITIAventureException{

    }
}