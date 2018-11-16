/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/
//#pragma once

#ifndef FONCTEUR_H
#define FONCTEUR_H

#include <map>
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"
//#include "gestionnaireUtilisateurs.h"
using namespace std;


class AjouterDepense
{

public:
	AjouterDepense(vector<Depense*>& conteneur) : conteneur_(conteneur)
	{};

	vector<Depense*>& operator()(Depense* depense)
	{
		conteneur_.push_back(depense);
		return conteneur_;
	};

private:
	vector<Depense*> conteneur_;
};


class AjouterUtilisateur
{

public:
	AjouterUtilisateur(map<Utilisateur*, double>& conteneur) : conteneur_(conteneur)
	{};

	map<Utilisateur*, double>& operator()(Utilisateur* utilisateur)
	{
		if (dynamic_cast<UtilisateurRegulier*>(utilisateur) != nullptr) {
			if ( !(dynamic_cast<UtilisateurRegulier*>(utilisateur)->getPossedeGroupe()))
			{
				conteneur_.insert(pair<Utilisateur*, double>(utilisateur, 0));
				dynamic_cast<UtilisateurRegulier*>(utilisateur)->setPossedeGroupe(true);
			}

			else {
				cout << "Erreur : L'utilisateur " << utilisateur->getNom() << " n'est pas un utilisateur premium et est deja dans un groupe." << endl;

			}
		}

		else {
			if (dynamic_cast<UtilisateurPremium*>(utilisateur)->getJoursRestants() > 0) {
				conteneur_.insert(pair<Utilisateur*, double>(utilisateur, 0));
			}
			else {
				cout << "Erreur: L'utilisateur " << utilisateur->getNom() << " doit renouveler son abonnement premium." << endl;
			}
		}

		
		return conteneur_;
	};

private:
	map<Utilisateur*, double> conteneur_;
};



class FoncteurIntervalle
{

public:
	FoncteurIntervalle(double borneInf, double borneSup) : borneInf_(borneInf), borneSup_(borneSup)
	{};

	bool operator()(pair<Utilisateur*, double> pair)
	{ 
		if (pair.second >= borneInf_ && pair.second <= borneSup_)
			return true;

		return false;
	};

private:
	double borneInf_, borneSup_;
};

#endif