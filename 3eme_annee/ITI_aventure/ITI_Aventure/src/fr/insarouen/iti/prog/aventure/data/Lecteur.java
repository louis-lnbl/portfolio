package fr.insarouen.iti.prog.aventure.data;

import fr.insarouen.iti.prog.aventure.Monde;
import java.util.Collection;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;

public interface Lecteur{

    public Monde getMonde();

    public Collection<ConditionDeFin> getConditionsDeFin();
}