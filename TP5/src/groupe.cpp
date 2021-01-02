/********************************************
* Titre: Travail pratique #5 - groupe.cpp
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#include "groupe.h"
#include <iterator>

// Constructeurs
Groupe::Groupe() {
	nom_ = "";
	gestionnaireDepenses_ = new GestionnaireDepenses();
	gestionnaireUtilisateurs_ = new GestionnaireUtilisateurs();
}

Groupe::Groupe(const string& nom) : nom_(nom) {
	gestionnaireDepenses_ = new GestionnaireDepenses();
	gestionnaireUtilisateurs_ = new GestionnaireUtilisateurs();
}

Groupe::~Groupe()
{
	for (Depense* depense : getDepenses())
	{
		delete depense;
	}
	for (Transfert* transfert : transferts_)
	{
		delete transfert;
	}

	delete gestionnaireDepenses_;
	delete gestionnaireUtilisateurs_;
}

// Methodes d'acces
string Groupe::getNom() const {
	return nom_;
}

// TODO : À modifier :
vector<Depense*> Groupe::getDepenses() const
{
	return gestionnaireDepenses_->getConteneur();
}

// TODO : À modifier :
map<Utilisateur*, double> Groupe::getUtilisateurs() const
{
	return gestionnaireUtilisateurs_->getConteneur();
}

vector<Transfert*> Groupe::getTransferts() const
{
	return transferts_;
}

// TODO : À modifier :
vector<double> Groupe::getComptes() const {
	return gestionnaireUtilisateurs_->getComptes();
}

double Groupe::getTotalDepenses() const {
	return gestionnaireDepenses_->getTotalDepenses();
}

GestionnaireUtilisateurs* Groupe::getGestionnaireUtilisateurs()
{
	return gestionnaireUtilisateurs_;
}

GestionnaireDepenses * Groupe::getGestionnaireDepenses()
{
	return gestionnaireDepenses_;
}

// Methodes de modifications
void Groupe::setNom(const string& nom) {
	nom_ = nom;
}

// Methodes d'ajout
// TODO : À modifier :
Groupe& Groupe::ajouterDepense(double montant, Utilisateur* payePar, const string& nom, const string& lieu)
{

	if ( !(gestionnaireUtilisateurs_->estExistant(payePar)) ){
		//cout << "Erreur: La personne impliquee dans la depense n'est pas dans le groupe." << endl;
		return *this;
	}

	Depense* depense = new Depense(nom, montant, lieu);

	// Ajouté :
	gestionnaireDepenses_->ajouter(depense);


	gestionnaireUtilisateurs_->mettreAJourComptes(payePar, montant);

	*payePar += depense;

	return *this;
}


Groupe& Groupe::operator+=(Utilisateur* utilisateur)
{
	// Ajouté :
	gestionnaireUtilisateurs_->ajouter(utilisateur);

	return *this;
}

// TODO : À modifier :
void Groupe::equilibrerComptes() {

	bool calcul = true;
	//int count = 0;
	while (calcul)
	{
		pair<Utilisateur*, double> max (gestionnaireUtilisateurs_->getMax());
		pair<Utilisateur*, double> min (gestionnaireUtilisateurs_->getMin());


		// On cherche lequel des deux a la dette la plus grande
		if ( -min.second <= max.second && min.second != 0 && max.second != 0) {
			if (min.first->getMethodePaiement() == Interac) {
				TransfertInterac* transfert = new TransfertInterac(-min.second, min.first, max.first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			else {
				TransfertPaypal* transfert = new TransfertPaypal(-min.second, min.first, max.first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			max.second += min.second;
			gestionnaireUtilisateurs_->setCompte(max);
			min.second = 0;
			gestionnaireUtilisateurs_->setCompte(min);
			//count++;
		}
		else if (-min.second > max.second  && min.second != 0 && max.second != 0) {
			if (min.first->getMethodePaiement() == Interac) {
				TransfertInterac* transfert = new TransfertInterac(max.second, min.first, max.first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			else {
				TransfertPaypal* transfert = new TransfertPaypal(max.second, min.first, max.first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			max.second = 0;
			gestionnaireUtilisateurs_->setCompte(max);
			min.second += max.second;
			gestionnaireUtilisateurs_->setCompte(min);
			//count++;
		}

		else if (min.second == 0 || max.second == 0)
		{
			calcul = false;
		}
	}

}

// Methode d'affichage
// TODO : À modifier :
ostream & operator<<(ostream& os, const Groupe& groupe)
{
	os << "\nGroupe " << groupe.nom_ << ".\nCout total: " << groupe.getTotalDepenses() << "$ \nUtilisateurs:    \n\n";

	for (auto elem : groupe.gestionnaireUtilisateurs_->getConteneur())
	{
		os << "\t- " << *elem.first << "\n";
	}

	if (groupe.transferts_.size() != 0) {
		os << "Transferts :" << endl;
		for (Transfert* elem : groupe.transferts_)
			os << "\t" << *elem;
	}
	else {
		os << "Les comptes ne sont pas equilibres" << endl << endl;
		for (auto elem : groupe.gestionnaireUtilisateurs_->getConteneur()) {
			os << elem.first->getNom() << " : " << elem.second << endl;
		}
	}

	os << endl;
	return os;
}
