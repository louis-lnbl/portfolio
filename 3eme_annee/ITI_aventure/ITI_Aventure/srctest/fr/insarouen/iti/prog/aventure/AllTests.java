package fr.insarouen.iti.prog.aventure;

import fr.insarouen.iti.prog.aventure.elements.AllTestsElements; 

import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.junit.runners.Suite.SuiteClasses;

import fr.insarouen.iti.prog.aventure.TestMonde;

@RunWith(Suite.class)
@SuiteClasses({
    AllTestsElements.class,
    TestMonde.class
})

public class AllTests {}