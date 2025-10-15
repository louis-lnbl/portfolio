package fr.insarouen.iti.prog.aventure;

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
import fr.insarouen.iti.prog.aventure.elements.Entite;
import fr.insarouen.iti.prog.aventure.MondeException;



public class TestMonde{
    private Monde m1;
    private Monde m2;
    private Entite e1;
    private Entite e2;
    private Entite e3;

    @Before
    public void avant() throws MondeException{
        m1 = new Monde("monde1");
        m2 = new Monde("monde2");
        e1 = new EntiteTest("Nicolas1", m1);
        e2 = new EntiteTest("Michel", m1);
        e3 = new EntiteTest("Gerard", m2);
    }

    @Test
    public void testGetNom(){
        assertThat(m1.getNom(), equalTo("monde1"));
        assertThat(m1.getNom(), not(equalTo("monde2")));
    }

    @Test
    public void testGetEntite(){
        assertThat(m1.getEntite("Nicolas1"), equalTo(e1));
        assertThat(m1.getEntite("Michel"), not(equalTo(e1)));
    }

    @Test(expected = MondeException.class)
    public void testAjouterEntiteExceptionEntiteDans2Mondes() throws MondeException{
        m1.ajouterEntite(e3);
        //Entite e4 = new EntiteTest("Nicolas", m2);
    }

    @Test(expected = MondeException.class)
    public void testAjouterEntiteExceptionEntiteDejaPresente() throws MondeException{
        m1.ajouterEntite(e2);
    }

    @Test
    public void testAjouterEntite() throws MondeException{
        assertThat(m2.getEntite("Maxime"), equalTo(null));
        Entite e4 = new EntiteTest("Maxime", m2);
        assertThat(m2.getEntite("Maxime"), equalTo(e4));
        assertThat(m1.getEntite("Maxime"), not(equalTo(e4)));
    }

    @Test
    public void testGenererNom(){
        String nom1 = m1.genererNom("Nicolas");
        assertThat(m1.getEntite(nom1), is(nullValue()));
    }

}


class EntiteTest extends Entite {

    public EntiteTest(String nom, Monde monde) throws MondeException {
	    super(nom,monde);
    }

}    