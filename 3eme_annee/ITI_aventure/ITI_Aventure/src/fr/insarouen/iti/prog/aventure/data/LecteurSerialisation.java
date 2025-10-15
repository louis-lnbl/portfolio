package fr.insarouen.iti.prog.aventure.data;


import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.data.Lecteur;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Serrure;
import fr.insarouen.iti.prog.aventure.elements.structure.Porte;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.Cle;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.EntiteDejaDansUnAutreMondeException;
import fr.insarouen.iti.prog.aventure.elements.Entite;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.vivants.JoueurHumain;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;

import java.io.Reader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.InputStream;

import java.util.List;
import java.util.ArrayList;
import java.util.Collection;



/**
 * La classe LecteurSerialisation permet de lire un monde et ses conditions de fin
 * 
 */

public class LecteurSerialisation implements Lecteur{


    private ObjectInputStream ois;
    private Monde monde;
    private List<ConditionDeFin> conditions;

    
    /**
     * Construit un LecteurSerialisation à partir d'un flux d'entrée d'objets sérialisés.
     * 
     *
     *
     * @param ois Le flux d'entrée contenant les objets sérialisés.
     * @throws ClassNotFoundException Si le contenu lu ne correspond pas aux classes attendues.
     * @throws IOException Si une erreur d'entrée/sortie survient lors de la lecture du flux.
     */
    public LecteurSerialisation(ObjectInputStream ois) throws ClassNotFoundException,IOException{    
        this.ois = ois;

        Object mondeObj = this.ois.readObject();
        if (!(mondeObj instanceof Monde)) {
            throw new ClassNotFoundException("L'objet lu n'est pas de type Monde");
        }
        this.monde = (Monde) mondeObj;
    
        Object conditionsObj = this.ois.readObject();
        if (!(conditionsObj instanceof List)) {
            throw new ClassNotFoundException("L'objet lu n'est pas une List");
        }
        List<?> lConditions = (List)conditionsObj;
        List<ConditionDeFin> lConditionsVerif = new ArrayList<>();
        for(Object o : lConditions){
            if(!(o instanceof ConditionDeFin)){
                throw new ClassNotFoundException("La liste lue ne contient pas des objets de type ConditionDeFin");
            } else{
                lConditionsVerif.add((ConditionDeFin)o);
            }
        }
        this.conditions = lConditionsVerif;

        ois.close();
    }

      /**
     * Retourne le monde chargé à partir du flux sérialisé.
     *
     * @return Le monde du jeu.
     */

    @Override
    public Monde getMonde(){
        return this.monde;
    }

     /**
     * Retourne les conditions de fin associées au monde.
     *
     * @return Une collection des conditions de fin du jeu.
     */
    
    @Override 
    public Collection<ConditionDeFin> getConditionsDeFin(){
        return this.conditions;
    }
}