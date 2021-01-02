/********************************************
* Titre: Travail pratique #4 - groupe.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "groupe.h"

// Constructeurs

Groupe::Groupe() {
	nom_ = "";
}

Groupe::Groupe(const string& nom) : nom_(nom) {
}

Groupe::~Groupe()
{
	for (unsigned int i = 0; i < depenses_.size() ; i++)
	{
		delete depenses_[i];
		depenses_[i] = nullptr;
	}

	for (unsigned int i = 0; i < transferts_.size(); i++)
	{
		delete  transferts_[i];
		transferts_[i] = nullptr;
	}
}

// Methodes d'acces
string Groupe::getNom() const {
	return nom_;
}

vector<Depense*> Groupe::getDepenses() const
{
	return depenses_;
}

vector<Utilisateur*> Groupe::getUtilisateurs() const
{
	return utilisateurs_;
}

vector<Transfert*> Groupe::getTransferts() const
{
	return transferts_;
}

vector<double> Groupe::getComptes() const
{
	return comptes_;
}

double Groupe::getTotalDepenses() const {
	double totalDepenses = 0;
	for (unsigned int i = 0; i < depenses_.size(); i++) {
		totalDepenses += depenses_[i]->getMontant();
	}
	return totalDepenses;
}

// Methodes de modifications
void Groupe::setNom(const string& nom) {
	nom_ = nom;
}


Groupe& Groupe::ajouterDepense(double montant, Utilisateur * payePar, const string & nom, const string & lieu)
{
	bool appartientGroupe = false;
	unsigned int count = 0;
	unsigned int indexPayePar = 0;

	for (unsigned int i = 0; i < utilisateurs_.size(); i++)
	{
		if (utilisateurs_[i] == payePar)
		{
			indexPayePar = i;
			appartientGroupe = true;
			break;
		}
	}  //verifier que utilisateur appartient au groupe

	if (appartientGroupe)
	{
		Depense* depense = new Depense(nom, montant, lieu);

		depenses_.push_back(depense);

		unsigned int nombreUtilisateurs = utilisateurs_.size();

		for (unsigned int i = 0; i < utilisateurs_.size(); i++)
		{

			comptes_[i] -= montant / nombreUtilisateurs;

		} //ajouter depense a tous les utilisateurs

		comptes_[indexPayePar] += montant;

		*payePar += depense;
	}

	else
	{
		//cout << "Erreur: La personne impliquee dans la depense n'est pas dans le groupe." << endl;
	}

	return *this;
}


Groupe & Groupe::operator+=(Utilisateur * utilisateur)
{
	if (dynamic_cast<UtilisateurRegulier*>(utilisateur) != nullptr) { //si il est regulier
		if (!dynamic_cast<UtilisateurRegulier*>(utilisateur)->getPossedeGroupe()) {
			utilisateurs_.push_back(utilisateur);
			comptes_.push_back(0);
			dynamic_cast<UtilisateurRegulier*>(utilisateur)->setPossedeGroupe(true);
		}
		else {
			cout << "Erreur: L'utilisateur " << utilisateur->getNom() << " n'est pas un utilisateur premium et est deja dans un groupe." << endl;
		}
	}

	else { //donc premium
		if (dynamic_cast<UtilisateurPremium*>(utilisateur)->getJoursRestants()>0) {
			utilisateurs_.push_back(utilisateur);
			comptes_.push_back(0);
		}
		else {
			cout << "Erreur: L'utilisateur " << utilisateur->getNom() << " doit renouveler son abonnement premium." << endl;
		}
	}


	return *this;
}

void Groupe::equilibrerComptes() {

	bool calcul = true;
	unsigned int count = 0;
	while (calcul) {
		double max = 0;
		double min = 0;
		int indexMax = 0;
		int indexMin = 0;

		// On cherche le compte le plus eleve et le moins eleve
		for (unsigned int i = 0; i < utilisateurs_.size(); i++) {
			if (comptes_[i] > max) {
				max = comptes_[i];
				indexMax = i;
			}
			if (comptes_[i] < min) {
				min = comptes_[i];
				indexMin = i;
			}
		}

		// On cherche lequel des deux a la dette la plus grande
		if (-min <= max && min != 0 && max != 0) {
			// Faire le transfert  du bon type
			if (utilisateurs_[indexMin]->getMethodePaiement() == Paypal)
			{
				TransfertPaypal* transfertPaypal = new TransfertPaypal(-min, utilisateurs_[indexMin], utilisateurs_[indexMax]);
				transferts_.push_back(transfertPaypal);
				transfertPaypal->effectuerTransfert();
			}
			else
			{
				TransfertInterac* transfertInterac = new TransfertInterac(-min, utilisateurs_[indexMin], utilisateurs_[indexMax]);
				transferts_.push_back(transfertInterac);
				transfertInterac->effectuerTransfert();
			}
			comptes_[indexMax] += min;
			comptes_[indexMin] = 0;
		}
		else if (-min > max  && min != 0 && max != 0) {
			// Faire le transfert du bon type
			if (utilisateurs_[indexMin]->getMethodePaiement() == Paypal)
			{
				TransfertPaypal* transfertPaypal = new TransfertPaypal(max, utilisateurs_[indexMin], utilisateurs_[indexMax]);
				transferts_.push_back(transfertPaypal);
				transfertPaypal->effectuerTransfert();
			}
			else
			{
				TransfertInterac* transfertInterac = new TransfertInterac(max, utilisateurs_[indexMin], utilisateurs_[indexMax]);
				transferts_.push_back(transfertInterac);
				transfertInterac->effectuerTransfert();
			}
			comptes_[indexMax] = 0;
			comptes_[indexMin] += max;
		}

		// On incremente le nombre de comptes mis a 0
		count++;
		if (-min == max) {
			count++;
		}
		if (count >= utilisateurs_.size() - 1) {
			calcul = false;
		}
	}

}

// Methode d'affichage
ostream & operator<<(ostream& os, const Groupe& groupe)
{
	os << "\nGroupe " << groupe.nom_ << ".\nCout total: " << groupe.getTotalDepenses() << "$ \nUtilisateurs:    \n\n";
	for (unsigned int i = 0; i < groupe.utilisateurs_.size(); i++) {
		os << *groupe.utilisateurs_[i];
	}
	os << endl;

	if (groupe.transferts_.size() != 0) {
		os << "Transferts :" << endl;
		for (unsigned int i = 0; i < groupe.transferts_.size(); i++)
			os << *groupe.transferts_[i];
	}
	else {
		os << "Les comptes ne sont pas equilibres" << endl << endl;
		for (unsigned int i = 0; i < groupe.comptes_.size(); i++) {
			os << groupe.utilisateurs_[i]->getNom() << " : " << groupe.comptes_[i] << endl;
		}
	}

	os << endl;
	return os;
}
