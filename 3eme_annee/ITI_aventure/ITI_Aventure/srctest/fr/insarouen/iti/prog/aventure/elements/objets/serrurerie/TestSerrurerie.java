package fr.insarouen.iti.prog.aventure.elements.objets.serrurerie;

import fr.insarouen.iti.prog.aventure.Monde;



import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.ITIAventureException;
import fr.insarouen.iti.prog.aventure.MondeException;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleException;
import fr.insarouen.iti.prog.aventure.elements.ActivationImpossibleAvecObjetException;
import fr.insarouen.iti.prog.aventure.elements.Etat;


import org.junit.Test;
import org.junit.Before;
import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.not;
import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.CoreMatchers.nullValue;


public class TestSerrurerie{

    private Monde monde1;
    private Serrure serrure1;



    @Before
    public void avantTest(){
        try{
            monde1 = new Monde("monde1");

            serrure1 = new Serrure(monde1);


        }catch (NomDEntiteDejaUtiliseDansLeMondeException e) {
            e.printStackTrace();

        }

    }

    @Test
    public void testGetEtat(){
        assertThat(serrure1.getEtat(), is(Etat.VERROUILLE));
    }

    @Test
    public void testEstDeplacable(){
        assertThat(serrure1.estDeplacable(), is(false));
    }

    @Test
    public void testCreerCle() throws NomDEntiteDejaUtiliseDansLeMondeException,EntiteDejaDansUnAutreMondeException{
        Cle uneCle1 = serrure1.creerCle();
        assertThat(uneCle1, is(not(nullValue())));
        Cle uneCle2 = serrure1.creerCle();
        assertThat(uneCle2, is(nullValue()));
    }

    @Test(expected = ActivationImpossibleException.class)
    public void testActiver() throws ActivationImpossibleException{
        assertThat(serrure1.getEtat(), equalTo(Etat.VERROUILLE));
        serrure1.activer();    
    }
    
    @Test
    public void testActiverAvec() throws ActivationImpossibleAvecObjetException, EntiteDejaDansUnAutreMondeException, NomDEntiteDejaUtiliseDansLeMondeException{
        Cle uneCle = serrure1.creerCle();
        assertThat(serrure1.getEtat(), equalTo(Etat.VERROUILLE));
        serrure1.activerAvec(uneCle);
        assertThat(serrure1.getEtat(), equalTo(Etat.DEVERROUILLE));
    }
    
    @Test(expected = ActivationImpossibleAvecObjetException.class)
    public void testActiverAvecActivationImpossibleAvecObjetException() throws ActivationImpossibleAvecObjetException, NomDEntiteDejaUtiliseDansLeMondeException, EntiteDejaDansUnAutreMondeException{
        Objet unObjet = new Objet("unObjet", monde1){
            public boolean estDeplacable(){
                return false;
            }
        };
        serrure1.activerAvec(unObjet);    
    }

    @Test
    public void testActivableAvec() throws NomDEntiteDejaUtiliseDansLeMondeException, EntiteDejaDansUnAutreMondeException{
        Cle uneCle = serrure1.creerCle();
        assertThat(serrure1.activableAvec(uneCle), is(true));
        Objet unObjet = new Objet("unObjet", monde1){
            public boolean estDeplacable(){
                return false;
            }
        };
        assertThat(serrure1.activableAvec(unObjet), is(false));
    }


}
