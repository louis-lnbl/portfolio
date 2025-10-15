package fr.insarouen.iti.prog.aventure.elements;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

import fr.insarouen.iti.prog.aventure.elements.vivants.TestVivant;
import fr.insarouen.iti.prog.aventure.elements.structure.TestPiece;
import fr.insarouen.iti.prog.aventure.elements.structure.TestPorte;
import fr.insarouen.iti.prog.aventure.elements.objets.serrurerie.TestSerrurerie;


@RunWith(Suite.class)
@SuiteClasses({
    TestEntite.class,
    TestVivant.class,
    TestPiece.class,
    TestPorte.class,
    TestSerrurerie.class
})

public class AllTestsElements {}