package fr.insarouen.iti.prog.aventure.elements.vivants;

import fr.insarouen.iti.prog.aventure.ITIAventureException;

public class CommandeImpossiblePourLeVivantException extends ITIAventureException{
    public CommandeImpossiblePourLeVivantException (String message){
        super(message);
    }

    public CommandeImpossiblePourLeVivantException (String message, Throwable cause){
        super(message,cause);
    }
}