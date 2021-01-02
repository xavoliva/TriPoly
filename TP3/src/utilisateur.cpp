/********************************************
* Titre: Travail pratique #2 - utilisateur.cpp
* Date: 16 septembre 2018
* Auteur: Wassim Khene & David Dratwa 
*******************************************/

#include "utilisateur.h"

// Constructeurs



// Methodes d'acces


Utilisateur::Utilisateur(const string & nom, TypeUtilisateur type) : nom_(nom), type_(Regulier), interet_(0), totalDepense_(0)
{

}

Utilisateur::Utilisateur(const Utilisateur & utilisateur) : nom_(utilisateur.getNom()), type_(utilisateur.getType()), interet_(utilisateur.getInteret()), totalDepense_(getTotalDepenses())
{

}

Utilisateur::~Utilisateur()
{
}

string Utilisateur::getNom() const {
	return nom_;
}


double Utilisateur::getInteret() const {
	return interet_;
}

double Utilisateur::getTotalDepenses() const {
	return totalDepense_;
}

TypeUtilisateur Utilisateur::getType() const {
	return type_; 
}


unsigned int Utilisateur::getNombreDepenses() const
{
	
	return depenses_.size();
}

vector <Depense*> Utilisateur::getDepenses() const
{
	return depenses_; 
}

//Methodes de modification
void Utilisateur::setNom(const string& nom) {
	nom_ = nom;
}

void Utilisateur::calculerTotalDepenses()
{
	totalDepense_ = 0;

	for (unsigned int i = 0; i < depenses_.size(); i++)
	{
		totalDepense_ += depenses_[i]->getMontant();
	}
}

Utilisateur& Utilisateur::operator=(Utilisateur * utilisateur)
{
	if (this != utilisateur)
	{
		depenses_ = utilisateur->getDepenses();
		nom_ = utilisateur->getNom();
	}

	return *this;
}


void Utilisateur::ajouterInteret(double montant)
{
	interet_ += montant;
}

Utilisateur& Utilisateur::operator+=(Depense* depense)
{
	depenses_.push_back(depense);

	return *this;
}

// Methode d'affichage
ostream& operator<<(ostream& os, const Utilisateur& utilisateur)

{
	cout << "Utilisateur : " << utilisateur.nom_ << "(" << utilisateur.getType() << ")" << " a depense pour un total de : " << utilisateur.getTotalDepenses() <<
		", Polycount prend en interet: " << utilisateur.interet_ << ", voici les depenses:" << endl;

	for (unsigned int i = 0; i < utilisateur.depenses_.size(); i++)
	{
		cout << "\t\t";
		cout << *(utilisateur.depenses_[i]);
	}

	return cout;
}
