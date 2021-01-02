/********************************************
* Titre: Travail pratique #4 - main.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include <iostream>
//#include "depense.h";
#include "utilisateur.h"
#include "transfert.h"
#include "groupe.h"

using namespace std;

int main() {
	// Initialisation des utilisateurs
	UtilisateurRegulier* ur1 = new UtilisateurRegulier("Yves", Paypal, "yves@polymtl.ca", "yb");
	UtilisateurRegulier* ur2 = new UtilisateurRegulier("Martine", Interac, "martine@polymtl.ca", "mb");
	UtilisateurRegulier* ur3 = new UtilisateurRegulier("Samuel", Interac, "samuel@polymtl.ca", "sk");
	UtilisateurRegulier* ur4 = new UtilisateurRegulier("Axel", Interac, "axel@polymtl.ca", "am");

	UtilisateurPremium* up1 = new UtilisateurPremium("Ryan", Paypal, 10, "ryan@polymtl.ca", "rh");
	UtilisateurPremium* up2 = new UtilisateurPremium("Rebecca", Interac, 10, "rebecca@polymtl.ca", "rvc");
	UtilisateurPremium* up3 = new UtilisateurPremium("David", Paypal, 10, "david@polymtl.ca", "dd");
	UtilisateurPremium* up4 = new UtilisateurPremium("Gaspard", Interac, 10, "gaspard@polymtl.ca", "gdv");

	Depense* d1 = new Depense("test1", 50, "IGA");
	Depense* d2 = new Depense(*d1);

	UtilisateurPremium* uptest = new UtilisateurPremium("Yves", Paypal, 10, "yves@polymtl.ca", "yb");

	vector<Transfert*> transferts;
	transferts.push_back(new TransfertPaypal(100, up1, up2));
	transferts.push_back(new TransfertInterac(200, up2, ur1));
	transferts.push_back(new TransfertPaypal(150, ur2, up3));
	transferts.push_back(new TransfertInterac(300, ur3, ur4));

	Groupe* groupe1 = new Groupe("Madrid");
	Groupe* groupe2 = new Groupe("Collocation");

	/*
	* Tests
	*/
	vector<bool> tests;

	/*
	* Depense
	*/
	
	// Test 1: Constructeur par copie
	tests.push_back(d2->getNom() == "test1"
		&& d2->getMontant() == 50
		&& *d2->getLieu() == "IGA");

	// Test 2: Deep copy
	d1->setLieu("Provigo");
	tests.push_back(*d2->getLieu() == "IGA");

	d1->setMontant(150);
	d1->setNom("test2");
	*d2 = *d1;

	// Test 3: Operateur =
	tests.push_back(d2->getNom() == "test2"
		&& d2->getMontant() == 150
		&& *d2->getLieu() == "Provigo");

	/*
	* Utilisateur
	*/
	*uptest += d1;
	*uptest += d2;

	uptest->modifierBalanceFrais(10);
	uptest->modifierBalanceFrais(-15);
	uptest->modifierBalanceTranferts(50);
	uptest->modifierBalanceTranferts(-20);

	// Test 4: Methodes de Utilisateur
	tests.push_back(uptest->getDepenses().size() == 2
		&& uptest->getBalance() == -5
		&& uptest->getTotalATransferer() == 30);

	/*
	* Transfert
	*/
	// Test 5: Bonne initialisation des transferts
	tests.push_back(dynamic_cast<TransfertPaypal*>(transferts[0])->getId() == "rh"
		&& (dynamic_cast<TransfertInterac*>(transferts[1])->getCourriel() == "yves@polymtl.ca"));

	// Test 6: Calcul des frais pour premium
	tests.push_back(transferts[0]->getFraisTransfert() == 0
		&& transferts[1]->getFraisTransfert() == 0);

	// Test 7: Calcul des frais pour regulier
	tests.push_back(transferts[2]->getFraisTransfert() == 4.2
		&& transferts[3]->getFraisTransfert() == 1);

	transferts[0]->effectuerTransfert();
	// Test 8: 1er transfert
	tests.push_back(up1->getTotalATransferer() == 100
		&& up1->getBalance() == -3
		&& up2->getTotalATransferer() == -100);

	transferts[1]->effectuerTransfert();
	// Test 9: 2eme transfert
	tests.push_back(up2->getTotalATransferer() == 100
		&& up2->getBalance() == -6
		&& ur1->getTotalATransferer() == -200);

	transferts[2]->effectuerTransfert();
	// Test 10: 3eme transfert
	tests.push_back(ur2->getTotalATransferer() == 150
		&& ur2->getBalance() == 4.2
		&& up3->getTotalATransferer() == -150);

	transferts[3]->effectuerTransfert();
	// Test 11: 4eme transfert
	tests.push_back(ur3->getTotalATransferer() == 300
		&& ur3->getBalance() == 1
		&& ur4->getTotalATransferer() == -300);


	// Remise a 0 des valeurs balancs et valeurs a transferer
	up1->modifierBalanceFrais(3);
	up2->modifierBalanceFrais(6);
	ur2->modifierBalanceFrais(-4.2);
	ur3->modifierBalanceFrais(-1);

	up1->modifierBalanceTranferts(-100);
	up2->modifierBalanceTranferts(-100);
	up3->modifierBalanceTranferts(150);
	ur1->modifierBalanceTranferts(200);
	ur2->modifierBalanceTranferts(-150);
	ur3->modifierBalanceTranferts(-300);
	ur4->modifierBalanceTranferts(300);

	/*
	* Groupe
	*/

	// Test 12: ajout d'un utilisateur premium
	*groupe1 += up1;
	tests.push_back(groupe1->getUtilisateurs().size() == 1);

	up2->setJoursRestants(0);
	*groupe1 += up2;

	// Test 13: jours restants a 0
	tests.push_back(groupe1->getUtilisateurs().size() == 1);

	*groupe1 += up3;
	*groupe1 += up4;
	// Test 14: ajouts utilisateurs premium
	tests.push_back(groupe1->getUtilisateurs().size() == 3);

	*groupe1 += ur1;
	*groupe1 += ur2;
	*groupe1 += ur3;

	*groupe2 += ur4;
	// Test 15: ajout utilisateurs regulier
	tests.push_back(groupe1->getUtilisateurs().size() == 6
		&& groupe2->getUtilisateurs().size() == 1);

	*groupe1 += ur4;
	// Test 16: ajout d'utilisateur deja dans un groupe
	tests.push_back(groupe1->getUtilisateurs().size() == 6);

	groupe1->ajouterDepense(180, up1, "d1")
		.ajouterDepense(50, up2, "d2 - impossible");

	// Test 17: ajout de depense avec utilisateur hors du groupe
	tests.push_back(groupe1->getDepenses().size() == 1);

	// Test 18: modification des comptes
	tests.push_back(groupe1->getComptes()[0] == 150
		&& groupe1->getComptes()[1] == -30);

	groupe1->ajouterDepense(360, up4, "d2")
		.ajouterDepense(240, up3, "d3")
		.ajouterDepense(60, ur1, "d4")
		.ajouterDepense(600, ur2, "d5")
		.ajouterDepense(300, ur3, "d6")
		.ajouterDepense(720, ur4, "d7")
		.ajouterDepense(120, ur2, "d8")
		.ajouterDepense(180, up1, "d9");

	// Test 19: bonne valeurs pour les comptes
	tests.push_back(groupe1->getComptes()[0] == 20
		&& groupe1->getComptes()[1] == -100
		&& groupe1->getComptes()[2] == 20
		&& groupe1->getComptes()[3] == -280
		&& groupe1->getComptes()[4] == 380
		&& groupe1->getComptes()[5] == -40 
		&& groupe1->getTotalDepenses() == 2040);

	groupe1->equilibrerComptes();

	// Test 20: verification des transferts
	tests.push_back(groupe1->getTransferts().size() == 4
		&& groupe1->getComptes()[0] == 0
		&& groupe1->getComptes()[1] == 0
		&& groupe1->getComptes()[2] == 0
		&& groupe1->getComptes()[3] == 0
		&& groupe1->getComptes()[4] == 0
		&& groupe1->getComptes()[5] == 0);

	// Test 21: verification de la nature des transferts
	tests.push_back(dynamic_cast<TransfertPaypal*>(groupe1->getTransferts()[0]) != nullptr
		&& dynamic_cast<TransfertPaypal*>(groupe1->getTransferts()[1]) != nullptr
		&& dynamic_cast<TransfertInterac*>(groupe1->getTransferts()[2]) != nullptr
		&& dynamic_cast<TransfertInterac*>(groupe1->getTransferts()[3]) != nullptr);

	// Test 22 - 27: verification des balances et montants a transferts pour les utilisateurs
	tests.push_back(groupe1->getUtilisateurs()[0]->getTotalATransferer() == -20
		&& groupe1->getUtilisateurs()[0]->getBalance() == 0);

	tests.push_back(groupe1->getUtilisateurs()[1]->getTotalATransferer() == 100
		&& groupe1->getUtilisateurs()[1]->getBalance() == -3);
	tests.push_back(groupe1->getUtilisateurs()[2]->getTotalATransferer() == -20
		&& groupe1->getUtilisateurs()[2]->getBalance() == 0);
	tests.push_back(groupe1->getUtilisateurs()[3]->getTotalATransferer() == 280
		&& floorf(groupe1->getUtilisateurs()[3]->getBalance() * 100) / 100 == floorf(7.58 * 100) / 100);
	tests.push_back(groupe1->getUtilisateurs()[4]->getTotalATransferer() == -380
		&& groupe1->getUtilisateurs()[4]->getBalance() == 0);
	tests.push_back(groupe1->getUtilisateurs()[5]->getTotalATransferer() == 40
		&& groupe1->getUtilisateurs()[5]->getBalance() == 2);

	// Affichage des tests
	cout << "TESTS" << endl;
	for (unsigned int i = 0; i < tests.size(); i++)
	{
		cout << "\tTest " << setfill('0') << setw(2) << i + 1 << "... ";
		if (tests[i])
			cout << "OK!" << endl;
		else
			cout << "ECHEC" << endl;
	}

	// Test des methodes d'affichage
	cout << *groupe1;

	// TODO: Liberation de la memoire si nécessaire
	delete groupe2;
	groupe2 = nullptr;
	delete groupe1;
	groupe1 = nullptr;
	delete uptest;
	uptest = nullptr;

	for (unsigned int i = 0; i < transferts.size(); i++)
	{
		delete  transferts[i];
		transferts[i] = nullptr;
	}

	delete d2;
	d2 = nullptr;
	delete d1;
	d1 = nullptr;
	delete up4;
	up4 = nullptr;
	delete up3;
	up3 = nullptr;
	delete up2;
	up2 = nullptr;
	delete up1;
	up1 = nullptr;
	delete ur4;
	ur4 = nullptr;
	delete ur3;
	ur3 = nullptr;
	delete ur2;
	ur2 = nullptr;
	delete ur1;
	ur1 = nullptr;

	//system("pause");
	return 0;
}