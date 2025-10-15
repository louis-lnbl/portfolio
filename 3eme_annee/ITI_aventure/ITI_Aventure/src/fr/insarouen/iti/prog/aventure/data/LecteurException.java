package fr.insarouen.iti.prog.aventure.data;

import fr.insarouen.iti.prog.aventure.ITIAventureException;

public class LecteurException extends ITIAventureException{
    public LecteurException (String message){
        super(message);
    }

    public LecteurException (String message, Throwable cause){
        super(message,cause);
    }
}