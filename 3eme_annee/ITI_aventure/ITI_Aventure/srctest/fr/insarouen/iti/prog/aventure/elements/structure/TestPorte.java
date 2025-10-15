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
import static org.hamcrest.CoreMatchers.nullValue;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.ITIAventureException;
import fr.insarouen.iti.prog.aventure.MondeException;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.objets.PiedDeBiche;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleAvecObjetException;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleException;
import fr.insarouen.iti.prog.aventure.elements.Etat;
import java.util.Collection;


public class TestPorte{
    private Monde monde;
    private Piece piece1;
    private Piece piece2;
    private Porte porte12;
    private Objet objet1;
    private PiedDeBiche piedDeBiche1;
    private Serrure serrure1;
    private Cle cle1;

    @Before
    public void avantTest(){
        try{
            monde = new Monde("monde");
            piece1 = new Piece("piece1", monde);
            piece2 = new Piece("piece2", monde);
            serrure1 = new Serrure("serrure1", monde);
            cle1 = serrure1.creerCle();
            porte12 = new Porte("porte12",monde,serrure1,piece1,piece2);
            objet1 = new Objet("objet1",monde){
                @Override
                public boolean estDeplacable(){
                    return false;
                }
            };
            piedDeBiche1 = new PiedDeBiche("piedDeBiche1", monde);

        }catch (NomDEntiteDejaUtiliseDansLeMondeException e) {
            e.printStackTrace();

        }
    }

    @Test
    public void testGetPieceAutreCote(){
        assertThat(porte12.getPieceAutreCote(piece1), equalTo(piece2));
        assertThat(porte12.getPieceAutreCote(piece2), equalTo(piece1));
    }

    @Test
    public void testActivableAvec(){
        assertThat(porte12.activableAvec(objet1), is(false));
    }

    @Test
    public void testGetEtat(){
        assertThat(porte12.getEtat(), equalTo(Etat.VERROUILLE));   
    }

    @Test
    public void testActiver() throws ActivationImpossibleException, ActivationImpossibleAvecObjetException{
        assertThat(porte12.getEtat(), equalTo(Etat.VERROUILLE));
        porte12.activerAvec(piedDeBiche1);
        assertThat(porte12.getEtat(), equalTo(Etat.OUVERT));
        porte12.activer();
        assertThat(porte12.getEtat(), equalTo(Etat.FERME));
        porte12.activer();
        assertThat(porte12.getEtat(), equalTo(Etat.OUVERT));
    }

    @Test(expected=ActivationImpossibleException.class)
    public void testActiverActivationImpossibleException() throws ActivationImpossibleException{
        assertThat(porte12.getEtat(), equalTo(Etat.VERROUILLE));
        porte12.activer();
    }

    @Test
    public void testActiverAvec() throws ActivationImpossibleAvecObjetException,  ActivationImpossibleException{
        assertThat(porte12.getEtat(), equalTo(Etat.VERROUILLE));
        porte12.activerAvec(cle1);
        assertThat(porte12.getEtat(), equalTo(Etat.OUVERT));
        assertThat(porte12.getSerrure(), not(nullValue()));
        porte12.activerAvec(cle1);
        assertThat(porte12.getEtat(), equalTo(Etat.VERROUILLE));
        assertThat(porte12.getSerrure(), not(nullValue()));
        porte12.activerAvec(piedDeBiche1);
        assertThat(porte12.getEtat(), equalTo(Etat.OUVERT));
        assertThat(porte12.getSerrure(), nullValue());

    }

    @Test(expected = ActivationImpossibleAvecObjetException.class)
    public void testActiverAvecActivationImpossibleAvecObjetException() throws ActivationImpossibleAvecObjetException,  ActivationImpossibleException{
        porte12.activerAvec(objet1);
    }


}


