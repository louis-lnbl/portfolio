package fr.insarouen.iti.prog.aventure.elements;

import fr.insarouen.iti.prog.aventure.elements.objets.Objet;

import fr.insarouen.iti.prog.aventure.elements.ActivationException;



public interface Activable {

    public void activer() throws ActivationImpossibleException ;

    public void activerAvec(Objet objet) throws ActivationImpossibleAvecObjetException, ActivationImpossibleException;

    public boolean activableAvec(Objet objet); 
}