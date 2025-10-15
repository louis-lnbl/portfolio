package fr.insarouen.iti.prog.aventure;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Collection;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.StringReader;
import java.util.stream.Collectors;

import fr.insarouen.iti.prog.compilation.interpreteur.analyseurs.AnalyseurSyntaxique;
import fr.insarouen.iti.prog.aventure.conditions.ConditionDeFin;
import fr.insarouen.iti.prog.aventure.data.Enregistreur;
import fr.insarouen.iti.prog.aventure.data.EnregistreurSerialisation;
import fr.insarouen.iti.prog.aventure.data.EnregistreurBD;
import fr.insarouen.iti.prog.aventure.data.Lecteur;
import fr.insarouen.iti.prog.aventure.data.LecteurBD;
import fr.insarouen.iti.prog.aventure.data.LecteurDescription;
import fr.insarouen.iti.prog.aventure.data.LecteurSerialisation;
import fr.insarouen.iti.prog.aventure.data.LecteurAST;
import fr.insarouen.iti.prog.compilation.interpreteur.arbreSyntaxiqueAbstrait.Config;

public class Main {
    private static String nomFichier, nomBase;
    private static Lecteur lecteur=null;
    private static Enregistreur enregistreur=null;
    private static Simulateur simulateur=null;
    private static Monde monde=null;
    private static Collection<ConditionDeFin> conditionsDeFin=null;
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
	while (true) {
	    System.out.println();
	    System.out.println();
	    System.out.println("0/ jouer un tour");
	    System.out.println("1/ jouer jusqu'à la fin sans possibilité d'arrêter");
	    System.out.println("2/ Charger fichier de description");
	    System.out.println("3/ Sauvegarder une partie");
	    System.out.println("4/ Charger une sauvegarde");
	    System.out.println("5/ Quitter");
	    System.out.println("6/ Sauvegarder une partie dans une BD");
	    System.out.println("7/ Charger une partie depuis une BD");
	    System.out.println("8/ Charger une partie depuis l'AST");

	    try {
		switch (scanner.nextInt()) {
		case 0:
		    if (simulateur == null) {
			System.out.println("Vous n'avez pas de partie en cours");
		    } else {
			simulateur.executerUnTour();
		    }
		    break;
		case 1:
		    if (simulateur == null) {
			System.out.println("Vous n'avez pas de partie en cours");
		    } else {
			simulateur.executerJusquALaFin();
		    }
		    break;
		case 2:
		    chargerFichierDescription();
			break;
		case 3:
		    sauvegarderFichierSerialisation();
		    break;
		case 4:
		    chargerFichierSerialisation();
		    break;
		case 5:
		    scanner.close();
		    System.exit(1);
		    break;
		case 6:
			sauvegarderBD();
		    break;
		case 7:
			lireBD();
		    break;
		
		case 8:
			lireAST();
		    break;
		default:
		    System.err.println("Choisissez une valeur entre 1 et 5.");
		}
	    } catch (java.util.InputMismatchException e) {
		System.out.println("Saisie incorrecte");
		scanner.nextLine();
	    }
	}
    }

    public static void chargerFichierDescription() {
		System.out.println("Chargement d'un fichier textuel de description");
		System.out.print("Veuillez saisir le nom du fichier : ");
		nomFichier = scanner.next();
		try {
			lire(new LecteurDescription(new FileReader(nomFichier)));
		} catch (Exception e) {
			System.err.println("La lecture a rencontré un problème");
			System.err.println(e.getMessage());
		}
	}

    public static void sauvegarderFichierSerialisation() {
	System.out.println("Sauvegarde de la partie en cours");
	if (monde == null) {
	    System.out.println("Vous n'avez pas de partie en cours");
	} else {
	    System.out.print("Veuillez saisir le nom du fichier : ");
	    nomFichier = scanner.next();
	    try {
		enregistreur = new EnregistreurSerialisation(new ObjectOutputStream(new FileOutputStream(nomFichier)));
		enregistreur.enregistrer(monde,conditionsDeFin);
	    } catch (Throwable e) {
		enregistreur = null;
		System.err.println("La sauvegarde a rencontré un problème");
		System.err.println(String.format("---> %s ",e.getMessage()));
	    }
	}
    }

    public static void chargerFichierSerialisation() {
		System.out.println("Chargement d'une sauvegarde");
		System.out.print("Veuillez saisir le nom du fichier : ");
		nomFichier = scanner.next();
		try {
			lire(new LecteurSerialisation(new ObjectInputStream(new FileInputStream(nomFichier))));
		} catch (Exception e) {
			System.err.println("La lecture a rencontré un problème");
			System.err.println(e.getMessage());
		}
    }

	public static void sauvegarderBD() {
		System.out.println("Sauvegarde de la partie en cours");
		if (monde == null) {
			System.out.println("Vous n'avez pas de partie en cours");
		} else {
			System.out.print("Veuillez saisir le nom de la base de données : ");
			nomBase = scanner.next();
			try {
				enregistreur = new EnregistreurBD(nomBase);
				enregistreur.enregistrer(monde,conditionsDeFin);
			} catch (Throwable e) {
				enregistreur = null;
				System.err.println("La sauvegarde a rencontré un problème");
				System.err.println(String.format("---> %s ",e.getMessage()));
			}
		}
    }

	public static void lireBD() {
		System.out.println("Lecture d'une sauvegarde depuis une BD");
		System.out.print("Veuillez saisir le nom de la base de données : ");
		nomBase = scanner.next();
		try {
			lire(new LecteurBD(nomBase));
		} catch (Exception e) {
			System.err.println("La lecture a rencontré un problème");
			System.err.println(e.getMessage());
		}
    }

	public static void lireAST() {
		System.out.println("Lecture d'une sauvegarde depuis une AST");
		System.out.print("Veuillez saisir le nom du fichier représentant l'AST : ");
		nomBase = scanner.next();
		AnalyseurSyntaxique as = null;
		try {
			BufferedReader fluxTexte = new BufferedReader(new FileReader(nomBase));
			String texte = fluxTexte.lines().collect(Collectors.joining("\n"));       
			as = new AnalyseurSyntaxique(new StringReader(texte));
			try {
				Config config = as.config();
				try {
					lire(new LecteurAST(config));
				} catch (Throwable t) {
					System.err.println("La lecture a rencontré un problème");
					System.err.println(t.getMessage());
				}
			} catch (fr.insarouen.iti.prog.compilation.interpreteur.analyseurs.ParseException pe) {
				System.err.println("Erreur de parsing : " + pe.getMessage());
			}
			try {
				fluxTexte.close();
			} catch (java.io.IOException ioe) {
				System.err.println("Erreur lors de la fermeture du fichier : " + ioe.getMessage());
			}
		} catch (FileNotFoundException exp) {
			System.err.println(exp.getMessage());
		}
	}

	private static void lire(Lecteur lecteur) {
		try {
			monde = lecteur.getMonde();
			conditionsDeFin = lecteur.getConditionsDeFin();
			simulateur = new Simulateur(monde, conditionsDeFin);
		} catch (Exception e) {
			System.err.println("La lecture a rencontré un problème");
			System.err.println(e.getMessage());
		}
	}
			
}
