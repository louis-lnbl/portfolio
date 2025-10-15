package fr.insarouen.iti.prog.aventure.data;

import java.io.ObjectOutputStream;
import fr.insarouen.iti.prog.aventure.Monde;
import java.io.IOException;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;
import java.util.Collection;


/**
 * La classe EnregistreurSerialisation permet de sauvegarder l'état
 * d'un Monde et ses ConditionsDeFin dans un fichier
 * à l'aide de la sérialisation Java.
 *
 */

public class EnregistreurSerialisation implements Enregistreur{


    private ObjectOutputStream oos;


    public EnregistreurSerialisation(ObjectOutputStream oos) throws IOException{
        
        this.oos=oos;
    }


    /**
     * Sérialise le Monde et les ConditionDeFin donnés
     * dans le flux de sortie.
     *
     * @param monde le monde à enregistrer.
     * @param conditionsDeFin les conditions de fin à enregistrer.
     * 
     */

    @Override
    public void enregistrer(Monde monde,  Collection<ConditionDeFin> conditionsDeFin) throws IOException{

        this.oos.writeObject(monde);
        this.oos.writeObject(conditionsDeFin);
        this.oos.close();
    }

}
