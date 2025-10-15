package fr.insarouen.iti.prog.aventure.elements.vivants;

import fr.insarouen.iti.prog.aventure.ITIAventureException;
import fr.insarouen.iti.prog.aventure.Monde;
import fr.insarouen.iti.prog.aventure.NomDEntiteDejaUtiliseDansLeMondeException;
import fr.insarouen.iti.prog.aventure.elements.ActivationException;
import fr.insarouen.iti.prog.aventure.elements.objets.Objet;
import fr.insarouen.iti.prog.aventure.elements.objets.ObjetNonDeplacableException;
import fr.insarouen.iti.prog.aventure.elements.structure.ObjetAbsentDeLaPieceException;
import fr.insarouen.iti.prog.aventure.elements.structure.Piece;
import fr.insarouen.iti.prog.aventure.elements.structure.PorteFermeException;
import fr.insarouen.iti.prog.aventure.elements.structure.PorteInexistanteDansLaPieceException;
import java.util.List;
import java.util.Arrays;
import java.util.stream.Collectors;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;

/**
 * La classe JoueurHumain représente le joueur humain
 * Une porte  possède un nom, un monde, les points de vie, les points de force, les objets et les pièces ou il se trouve.
 */

public class JoueurHumain extends Vivant {

    private String ordre;

    public JoueurHumain(String nom, Monde monde, int pointsVie, int pointsForce, Piece piece, Objet... objets) throws NomDEntiteDejaUtiliseDansLeMondeException {
	    super(nom, monde, pointsVie, pointsForce, piece, objets);
    }

    /**
     * permet d'obtenir l'ordre du joueurHumain.
     *
     * @return retourne l'ordre.
     */

    public String getOrdre() {
	    return this.ordre;
    }

    /**
     * Définit l'ordre que le joueur humain doit exécuter.
     *
     * @param ordre l'ordre à exécuter sous forme de chaîne de caractères.
     */

    public void setOrdre(String ordre) {
	    this.ordre = ordre;
    }
    
    /**
     * Permet au joueur humain de prendre un objet dans la pièce.
     *
     * @param nomObjet le nom de l'objet à prendre.
     * @throws ObjetNonDeplacableException si l'objet ne peut pas être déplacé.
     * @throws ObjetAbsentDeLaPieceException si l'objet est absent de la pièce.
     */

    private void commandePrendre(String nomObjet) throws ObjetNonDeplacableException, ObjetAbsentDeLaPieceException {
	    this.prendre(nomObjet);
    }

    /**
     * Permet au joueur humain de poser un objet qu'il possède.
     *
     * @param nomObjet le nom de l'objet à poser.
     * @throws ObjetNonPossedeParLeVivantException si le joueur ne possède pas l'objet.
     */

    private void commandePoser(String nomObjet) throws ObjetNonPossedeParLeVivantException {
	    this.deposer(nomObjet);
    }

    /**
     * Permet au joueur humain de franchir une porte.
     *
     * @param nomPorte le nom de la porte à franchir.
     * @throws PorteFermeException si la porte est fermée.
     * @throws PorteInexistanteDansLaPieceException si la porte n'existe pas dans la pièce actuelle.
     */

    private void commandeFranchir(String nomPorte) throws PorteFermeException, PorteInexistanteDansLaPieceException {
	    this.franchir(nomPorte);
    }

    /**
     * Permet au joueur humain d’ouvrir une porte sans utiliser d'objet.
     *
     * @param nomPorte le nom de la porte à ouvrir.
     * @throws ActivationException si l'activation de la porte échoue.
     * @throws PorteInexistanteDansLaPieceException si la porte n'existe pas dans la pièce actuelle.
     */

    private void commandeOuvrirPorte(String nomPorte) throws ActivationException, PorteInexistanteDansLaPieceException {
        if (!this.getPiece().aLaPorte(nomPorte))
            throw new PorteInexistanteDansLaPieceException(String.format("%s ne possède pas %s", this.getPiece().getNom(), nomPorte));
        this.getPiece().getPorte(nomPorte).activer();
    }

    /**
     * Permet au joueur humain d’ouvrir une porte en utilisant un objet.
     *
     * @param nomPorte le nom de la porte à ouvrir.
     * @param nomObjet le nom de l'objet à utiliser pour ouvrir la porte.
     * @throws ActivationException si l'activation échoue.
     * @throws PorteInexistanteDansLaPieceException si la porte n'existe pas dans la pièce actuelle.
     * @throws ObjetNonPossedeParLeVivantException si le joueur ne possède pas l'objet.
     */

    private void commandeOuvrirPorte(String nomPorte, String nomObjet) throws ActivationException, PorteInexistanteDansLaPieceException, ObjetNonPossedeParLeVivantException {
        if (!this.possede(nomObjet))
            throw new ObjetNonPossedeParLeVivantException(String.format("%s ne possède pas %s", this.getNom(), nomObjet));
        if (!this.getPiece().aLaPorte(nomPorte))
            throw new PorteInexistanteDansLaPieceException(String.format("%s ne possède pas %s", this.getPiece().getNom(), nomPorte));
        this.getPiece().getPorte(nomPorte).activerAvec(this.getObjet(nomObjet));
    }

    /**
     * Exécute l'ordre donné au joueur humain.
     *
     * @throws ITIAventureException si une erreur survient lors de l'exécution de l'ordre.
     */
    @Override
    public void executer() throws ITIAventureException {
        String[] tokens = this.ordre.split(" ");
        String commande = "commande" + tokens[0];

        List<String> tokensFiltres = Arrays.stream(tokens)
                                        .filter(token -> !token.equalsIgnoreCase("avec"))
                                        .collect(Collectors.toList());

        String[] parametres = new String[tokensFiltres.size() - 1];
        tokensFiltres.subList(1, tokensFiltres.size()).toArray(parametres);

        Class<?>[] tabString = new Class[parametres.length];
        Arrays.fill(tabString, String.class);
        try {
            Method methode = this.getClass().getDeclaredMethod(commande, tabString);
            methode.invoke(this, (Object[]) parametres); 
        } catch (InvocationTargetException e) {
            throw (ITIAventureException) e.getCause();
        } catch (Exception e){
            throw new CommandeImpossiblePourLeVivantException("L'ordre est impossible à executer :" + this.ordre);
        }
    }

}