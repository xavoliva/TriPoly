/********************************************
* Titre: Travail pratique #4 - groupe.h
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#ifndef GROUPE_H
#define GROUPE_H

#include <string>
#include <vector>

#include "depense.h"
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"
#include "transfertInterac.h"
#include "transfertPaypal.h"

using namespace std;

class Groupe {
public:
	// Constructeurs
	Groupe();
	Groupe(const string& nom);
	~Groupe();

	// Methodes d'acces
	string getNom() const;
	vector<Depense*> getDepenses() const;
	vector<Utilisateur*> getUtilisateurs() const;
	vector<Transfert*> getTransferts() const;
	vector<double> getComptes() const;
	double getTotalDepenses() const;

	// Methodes de modification
	void setNom(const string& nom);

	// Methodes d'ajout
	// TODO
	Groupe& ajouterDepense(double montant, Utilisateur* payePar, const string& nom = "", const string& lieu = "Montreal");
	// TODO
	Groupe& operator+=(Utilisateur* utilisateur);

	// Methodes de calcul
	// TODO
	void equilibrerComptes();

	// Methode d'affichage
	friend ostream& operator<<(ostream& os, const Groupe& groupe);

private:
	string nom_;
	vector<Utilisateur*> utilisateurs_;
	vector<Depense*> depenses_;
	vector<Transfert*> transferts_;
	vector<double> comptes_; 
};

#endif
