CHEMIN=fr/insarouen/iti/prog/aventure

all:

compilation: analyseurs ast config aventure

execution:
	java -classpath ./classes:/usr/share/java/postgresql-jdbc4.jar fr.insarouen.iti.prog.aventure.Main 

executionCompilMain:
	java -classpath ./classes fr.insarouen.iti.prog.compilation.interpreteur.configuration.Main exemple.cfg


aventure: 
	javac -classpath ./classes:/usr/share/java/postgresql-jdbc4.jar -sourcepath ./src -d ./classes ./src/fr/insarouen/iti/prog/aventure/*.java

analyseurs: 
	javacc -OUTPUT_DIRECTORY=./src/fr/insarouen/iti/prog/compilation/interpreteur/analyseurs/ ./src/fr/insarouen/iti/prog/compilation/interpreteur/analyseurs/*.jj
	javac -sourcepath ./src -d ./classes ./src/fr/insarouen/iti/prog/compilation/interpreteur/analyseurs/*.java

ast:  
	javac -classpath ./classes -sourcepath ./src -d ./classes ./src/fr/insarouen/iti/prog/patronsConception/visiteur/*.java
	javac -classpath ./classes -sourcepath ./src -d ./classes ./src/fr/insarouen/iti/prog/compilation/interpreteur/arbreSyntaxiqueAbstrait/*.java


config:
	javac -classpath ./classes -sourcepath ./src -d ./classes ./src/fr/insarouen/iti/prog/compilation/interpreteur/configuration/*.java


compilationTests: 
	javac -classpath ./classes:/usr/share/java/postgresql-jdbc4.jar:/usr/share/java/junit4.jar:/usr/share/java/hamcrest-all.jar -sourcepath ./srctest -d ./classestest ./srctest/fr/insarouen/iti/prog/aventure/*.java

tests:
	java -classpath ./classestest:./classes:/usr/share/java/junit4.jar:/usr/share/java/hamcrest-all.jar org.junit.runner.JUnitCore fr.insarouen.iti.prog.aventure.AllTests 

testsProf:
	java -classpath ./classestest_prof_avec_monstre:./classes:/usr/share/java/junit4.jar:/usr/share/java/hamcrest-all.jar org.junit.runner.JUnitCore fr.insarouen.iti.prog.aventure.AllTests 



clean:
	rm -rf classes/*
	rm -rf src/fr/insarouen/iti/prog/compilation/interpreteur/analyseurs/*.java
	rm -rf classestest/*