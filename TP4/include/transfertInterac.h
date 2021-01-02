/********************************************
* Titre: Travail pratique #4 - tranfertInterac.h
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/
#pragma once

#include "transfert.h"
#include "utilisateurPremium.h"

const double FRAIS_TRANSFERT = 1.0;

class TransfertInterac : public Transfert {
public:
	// Constructeur
	// TODO: a modifier
	TransfertInterac(double montant, Utilisateur* expediteur, Utilisateur* receveur);

	string getCourriel() const;
	void setcourriel(string courriel);

	// TODO
	double getFraisTransfert() const;
private:
	string courriel_;
};