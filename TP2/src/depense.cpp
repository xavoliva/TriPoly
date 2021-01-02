/********************************************
* Titre: Travail pratique #2 - depense.cpp
* Date: 16 septembre 2018
* Auteur: Wassim Khene
*******************************************/

#include "depense.h"

// Constucteurs
Depense::Depense() : nom_(""), montant_(0), lieu_(nullptr)
{
	lieu_ = new string("");
}

Depense::Depense(const string& nom, const double & montant, const string& lieu) : nom_(nom), montant_(montant), lieu_(nullptr)
{
	lieu_ = new string(lieu);
}

//Constructeur par copie
Depense::Depense(const Depense & depense) : nom_(depense.getNom()), montant_(depense.getMontant()), lieu_(nullptr)
{
	lieu_ = new string(*(depense.getLieu()));
}

//Destructeur
Depense::~Depense()
{
	delete lieu_;
	lieu_ = nullptr;
}


// Methodes d'acces
string Depense::getNom() const
{
	return nom_;
}

double Depense::getMontant() const
{
	return montant_;
}

string * Depense::getLieu() const
{
	return lieu_;
}

// Methodes de modifications
void Depense::setNom(const string& nom)
{
	nom_ = nom;
}

void Depense::setMontant(const double & montant)
{
	montant_ = montant;
}

void Depense::setLieu(const string & lieu)
{
	delete lieu_;
	lieu_ = new string(lieu);
}

Depense Depense::operator=(const Depense & depense)
{
	if (this != &depense)
	{
		delete lieu_;

		lieu_ = new string(*(depense.lieu_));
		nom_ = depense.getNom();
		montant_ = depense.getMontant();
	}

	return *this;
}

ostream & operator<<(ostream & o, const Depense & d)
{
	return o << "Achat : " << d.nom_ << " Prix : " << d.montant_ << "; " << endl;
}



/*
// Methode d'affichage
void Depense::afficherDepense() const
{
	cout << "Achat : " << nom_ << " Prix : " << montant_ << "; " << endl;
}
*/


