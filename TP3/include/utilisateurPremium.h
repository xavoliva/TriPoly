/********************************************
* Titre: Travail pratique #3 - utilisateurPremium.h
* Date premiere version : 2 octobre 2018
* Auteur: David Dratwa
*******************************************/

#ifndef UTILISATEUR_PREMIUM_H
#define UTILISATEUR_PREMIUM_H

#include "utilisateur.h"


class UtilisateurPremium : public Utilisateur {
public :

	//constructeurs 
	UtilisateurPremium(const string& nom= "");
	UtilisateurPremium(const Utilisateur& utilisateur); 


	//getters
	unsigned int getJoursRestants() const; 
	double getTaux() const; 

	//setters 
	void setJoursRestants(unsigned int joursRestants); 

	//methode de calcul 
	void calculerTaux(); 

	//operateurs
	UtilisateurPremium& operator= (Utilisateur* utilisateur); 

	friend ostream& operator << (ostream& os, const UtilisateurPremium& utilisateur); 

private : 
	unsigned int joursRestants_; 
	double taux_; 
};

#endif 
