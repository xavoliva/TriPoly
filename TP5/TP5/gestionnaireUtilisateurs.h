/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#pragma once

#include "utilisateur.h"
#include "gestionnaireGenerique.h"
#include <functional>

class GestionnaireUtilisateurs : public GestionnaireGenerique<Utilisateur*, map<Utilisateur*, double>, pair<Utilisateur*, double>, AjouterUtilisateur>
{
public:

	vector<double> getComptes() const;
	bool estExistant(Utilisateur* utilisateur) const;
	void mettreAJourComptes(Utilisateur* utilisateur, double montant);
	pair<Utilisateur*, double>& getMax() const;
	pair<Utilisateur*, double>& getMin() const;
	Utilisateur* getUtilisateurSuivant(Utilisateur* utilisateur, double montant) const;
	vector<pair<Utilisateur*, double>> getUtilisateursEntre(double borneInf, double borneSup) const;
	GestionnaireUtilisateurs& setCompte(pair<Utilisateur*, double> p);

};