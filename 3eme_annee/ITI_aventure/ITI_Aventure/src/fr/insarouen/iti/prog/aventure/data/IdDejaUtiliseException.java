package fr.insarouen.iti.prog.aventure.data;

public class IdDejaUtiliseException extends LecteurException{
    public IdDejaUtiliseException (String message){
        super(message);
    }

    public IdDejaUtiliseException (String message, Throwable cause){
        super(message,cause);
    }
}