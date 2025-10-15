package fr.insarouen.iti.prog.aventure.elements;

import fr.insarouen.iti.prog.aventure.ITIAventureException;

public class ActivationImpossibleException extends ActivationException{
    public ActivationImpossibleException (String message){
        super(message);
    }

    public ActivationImpossibleException (String message, Throwable cause){
        super(message,cause);
    }
}