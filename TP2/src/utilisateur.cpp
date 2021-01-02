/********************************************
* Titre: Travail pratique #2 - utilisateur.cpp
* Date: 16 septembre 2018
* Auteur: Wassim Khene
*******************************************/

#include "utilisateur.h"

// Constructeurs
Utilisateur::Utilisateur() : nom_("")
{
}

Utilisateur::Utilisateur(const string& nom) : nom_(nom)
{
}

Utilisateur::Utilisateur(const Utilisateur & utilisateur) : nom_(utilisateur.getNom())
{
}

// Methodes d'acces
string Utilisateur::getNom() const
{
	return nom_;
}


double Utilisateur::getTotalDepenses() const
{
	double total = 0;
	for (unsigned int i = 0; i < depenses_.size(); i++) {
		total += depenses_[i]->getMontant();
	}
	return total;
}

vector<Depense*> Utilisateur::getDepenses() const
{
	return depenses_;
}



//Methodes de modification
void Utilisateur::setNom(const string& nom)
{
	nom_ = nom;
}


Utilisateur& Utilisateur::operator+=(Depense* depense)
{
	depenses_.push_back(depense);

	return *this;
}

Utilisateur& Utilisateur::operator=(const Utilisateur & utilisateur)
{
	if (this != &utilisateur)
	{
		depenses_ = utilisateur.getDepenses();
		nom_ = utilisateur.getNom();
	}

	return *this;

}

ostream & operator<<(ostream & cout, const Utilisateur & u)
{
	cout << "Utilisateur : " << u.nom_ << " a depense pour un total de : " << u.getTotalDepenses() << endl
		<< "\t Liste de depenses : " << endl;

	for (unsigned int i = 0; i < u.depenses_.size(); i++)
	{
		cout << "\t\t";
		cout << *(u.depenses_[i]);
	}

	return cout;
}

