/********************************************
* Titre: Travail pratique #4 - transfertPaypal.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "transfertPaypal.h"

TransfertPaypal::TransfertPaypal(double montant, Utilisateur * expediteur, Utilisateur * receveur)
	: Transfert(montant, expediteur, receveur), id_(expediteur->getIdPaypal())
{
}

string TransfertPaypal::getId() const
{
	return id_;
}

void TransfertPaypal::setId(string id)
{
	id_ = id;
}

double TransfertPaypal::getFraisTransfert() const
{
	if (dynamic_cast<UtilisateurPremium*>(Transfert::expediteur_) == nullptr) //controle pour voir qu'il est bien r�gulier
		return COMMISSION * Transfert::montant_ + FRAIS;

	else {
		return 0;
	}

}

