/********************************************
* Titre: Travail pratique #2 - utilisateur.h
* Date: 16 septembre 2018
* Auteur: Wassim Khene
*******************************************/

#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>
#include <iostream>
#include <vector>

#include "depense.h"

using namespace std;

class Utilisateur {
public:
	// Constructeurs
	Utilisateur();
	Utilisateur(const string& nom);
	// TODO: Ajouter un constructeur par copie
	Utilisateur(const Utilisateur &utilisateur);

	// Methodes d'accès
	string getNom() const;
	double getTotalDepenses() const;
	vector<Depense*> getDepenses() const;

	// Methodes de modification
	void setNom(const string& nom);

	// TODO: Ajouter un operateur += et =
	
	Utilisateur& operator+=(Depense* depense);

	Utilisateur& operator=(const Utilisateur& utilisateur);

	friend ostream & operator<<(ostream & cout, const Utilisateur & u);

private:
	string nom_;
	// TODO: Remplacer depenses_ par un vecteur
	vector<Depense*> depenses_;

};
#endif