package fr.insarouen.iti.prog.aventure.data;

public class MauvaisParametreException extends LecteurException{
    public MauvaisParametreException (String message){
        super(message);
    }

    public MauvaisParametreException (String message, Throwable cause){
        super(message,cause);
    }
}