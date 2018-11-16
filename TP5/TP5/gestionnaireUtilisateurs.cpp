/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.cpp
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#include "gestionnaireUtilisateurs.h"
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"
#include <functional>



vector<double> GestionnaireUtilisateurs::getComptes() const
{
	vector<double> comptes;

	for (auto& value : conteneur_)
		comptes.push_back(value.second);

	return comptes;
}

bool GestionnaireUtilisateurs::estExistant(Utilisateur * utilisateur) const
{
	if (conteneur_.find(utilisateur) != conteneur_.end())
	{
		return true;
	}

	return false;
}

void GestionnaireUtilisateurs::mettreAJourComptes(Utilisateur * utilisateur, double montant)
{


	double montantReparti = montant / getNombreElements();

	conteneur_.find(utilisateur)->second += montant;

	for (auto& paire : conteneur_)
	{
		paire.second -= montantReparti;
	}


}

pair<Utilisateur*, double>& GestionnaireUtilisateurs::getMax() const
{
	pair<Utilisateur*, double> paire (*max_element(conteneur_.begin(), conteneur_.end(),
		[](pair<Utilisateur*, double> p1, pair<Utilisateur*, double> p2)
	    {return p1.second < p2.second; }));


	return paire;
}
	

pair<Utilisateur*, double>& GestionnaireUtilisateurs::getMin() const
{
	
	pair<Utilisateur*, double> paire (*min_element(conteneur_.begin(), conteneur_.end(),
									[] ( pair<Utilisateur*, double> p1,  pair<Utilisateur*, double> p2)
									{return p1.second < p2.second; }));

	return paire;
}

Utilisateur* GestionnaireUtilisateurs::getUtilisateurSuivant(Utilisateur * utilisateur, double montant) const
{
	pair<Utilisateur*, double> paire_utilisateur(utilisateur, montant);
	auto it = find_if(conteneur_.begin(), conteneur_.end(), bind(greater<pair<Utilisateur*, double>>(), placeholders::_1, paire_utilisateur));

	return it->first;
}

vector<pair<Utilisateur*, double>> GestionnaireUtilisateurs::getUtilisateursEntre(double borneInf, double borneSup) const
{
	vector<pair<Utilisateur*, double>> vectorPaires;
	copy_if(conteneur_.begin(), conteneur_.end(), back_inserter(vectorPaires), FoncteurIntervalle(borneInf, borneSup));


	return vectorPaires;
}

GestionnaireUtilisateurs & GestionnaireUtilisateurs::setCompte(pair<Utilisateur*, double> p)
{
	if (conteneur_.find(p.first) != conteneur_.end())
		conteneur_[p.first] = p.second;

	return *this;
}
