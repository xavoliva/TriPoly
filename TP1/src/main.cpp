
#include <iostream>
#include "groupe.h"


using namespace std; 

int main(int argc, const char * argv[])
{
    cout << "\t \tBienvenue sur PolyCount " << endl << " *****************************************" << endl;
    
	// Creer un  groupe pour  6 depenses et 4 utilisateurs.
	Groupe madrid( "Madrid", 6, 4);
    
    // Creer 5 utilisateurs.

		Utilisateur* u1= new Utilisateur("u1");
		Utilisateur* u2 = new Utilisateur("u2");
		Utilisateur* u3 = new Utilisateur("u3");
		Utilisateur* u4 = new Utilisateur("u4");
		Utilisateur* u5 = new Utilisateur("u5");


    
    //Creer 7 dépenses.
	
	Depense* d1 = new Depense("d1", 200);
	Depense* d2 = new Depense("d2", 10);
	Depense* d3 = new Depense("d3", 50);
	Depense* d4 = new Depense("d4", 50);
	Depense* d5 = new Depense("d5", 200);
	Depense* d6 = new Depense("d6", 50);
	Depense* d7 = new Depense("d7", 60);
	
    
    //ajouter les utilisateurs au groupe
	
	madrid.ajouterUtilisateur(u1);
	madrid.ajouterUtilisateur(u2);
	madrid.ajouterUtilisateur(u3);
	madrid.ajouterUtilisateur(u4);
	madrid.ajouterUtilisateur(u5);
	

    //ajouter les depenses au groupe
	madrid.ajouterDepense(d1, u1);
	madrid.ajouterDepense(d6, u1);
	madrid.ajouterDepense(d7, u1);
	madrid.ajouterDepense(d2, u2);
	madrid.ajouterDepense(d3, u3);
	madrid.ajouterDepense(d4, u4);
	madrid.ajouterDepense(d5, u5);

    
    //calculer le total du groupe et de chaque utilisateur
	madrid.calculerTotalDepenses();

    //Afficher  le groupe
	madrid.afficherGroupe();
    
    //Equilibrer les comptes
	madrid.equilibrerComptes();
    //Afficher le groupe
	madrid.afficherGroupe();

    //terminer le programme correctement

	//system("PAUSE");
	return 0;
}
