/********************************************
* Titre: Travail pratique #4 - transfert.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "transfert.h"

// Constructeurs
Transfert::Transfert() : montant_(0), expediteur_(nullptr), receveur_(nullptr) {
}

Transfert::Transfert(double montant, Utilisateur* expediteur, Utilisateur* receveur) : 
	montant_(montant), expediteur_(expediteur), receveur_(receveur) {
}

// Methodes d'acces
double Transfert::getMontant() const {
	return montant_;
}


Utilisateur* Transfert::getExpediteur() const {
	return expediteur_;
}

Utilisateur* Transfert::getReceveur() const {
	return receveur_;
}

// Methodes de modifications
void Transfert::setMontant(double montant) {
	montant_ = montant;
}

void Transfert::setExpediteur(Utilisateur *donneur) {
	expediteur_ = donneur;
}

void Transfert::setReceveur(Utilisateur *receveur) {
	receveur_ = receveur;
}

void Transfert::effectuerTransfert()
{
	expediteur_->modifierBalanceTranferts(montant_);
	receveur_->modifierBalanceTranferts(-montant_);

	if (dynamic_cast<UtilisateurPremium*>(expediteur_) == nullptr)  //donc Régulier
		expediteur_->modifierBalanceFrais(getFraisTransfert());

	else {
		expediteur_->modifierBalanceFrais(-TAUX_EPARGNE *montant_);
	}

}

//Methode affichage
ostream& operator<<(ostream& os, const Transfert& transfert)
{
	os << "- " << transfert.expediteur_->getNom() << " -> " << transfert.receveur_->getNom() << "\t: " << transfert.montant_ << "$" << endl;
	
	return os;
}
