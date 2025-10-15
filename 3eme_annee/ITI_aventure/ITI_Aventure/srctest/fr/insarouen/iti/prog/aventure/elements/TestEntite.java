package fr.insarouen.iti.prog.aventure.elements;

import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;

import org.junit.Test;
import org.junit.Before;
import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.not;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;


public class TestEntite{

    private Monde monde1;
    private Monde monde2;
    private EntiteConcrete entite1;
    private EntiteConcrete entite2;
    private EntiteConcrete entite3;

    @Before
    public void avantTest(){
        try{
            monde1 = new Monde("monde1");

            monde2 = new Monde("monde2");

            entite1 = new EntiteConcrete("entite1",monde1);

            entite2 = new EntiteConcrete("entite2",monde2);

            entite3 = entite1;


        }catch (EntiteDejaDansUnAutreMondeException e) {
            e.printStackTrace();

        }catch (NomDEntiteDejaUtiliseDansLeMondeException e) {
            e.printStackTrace();

        }

    }

    @Test
    public void testGetNom(){
        assertThat(entite1.getNom(), equalTo("entite1"));
    }


    @Test
    public void testNonGetNom(){
        assertThat(entite1.getNom(), not(equalTo("entite2")) );
    }

    @Test
    public void testGetMonde(){
        assertThat(entite1.getMonde(), equalTo(monde1));
    }    

    @Test
    public void testNonGetMonde(){
        assertThat(entite1.getMonde(), not(equalTo(monde2)));
    }    

    @Test
    public void testEquals(){
        assertThat(entite1.equals(entite3), is(true));
    }  

    @Test
    public void testNonEquals(){
        assertThat(entite1.equals(entite2), not(is(true)));
    }  

    @Test(expected = NomDEntiteDejaUtiliseDansLeMondeException.class)
    public void testNomDEntiteDejaUtiliseDansLeMondeException() throws NomDEntiteDejaUtiliseDansLeMondeException{
        try{
            EntiteConcrete entite4 = new EntiteConcrete("entite1",monde1);
        }catch (EntiteDejaDansUnAutreMondeException e) {
            e.printStackTrace();
        }

    }

    @Test(expected = EntiteDejaDansUnAutreMondeException.class)
    public void testEntiteDejaDansUnAutreMondeException() throws EntiteDejaDansUnAutreMondeException{
        try{
            monde2.ajouterEntite(entite1);
        }catch (NomDEntiteDejaUtiliseDansLeMondeException e) {
            e.printStackTrace();
        }

    }      


}

class EntiteConcrete extends Entite{
    public EntiteConcrete(String nom, Monde monde) throws NomDEntiteDejaUtiliseDansLeMondeException, EntiteDejaDansUnAutreMondeException{
        super(nom,monde);
    }
}