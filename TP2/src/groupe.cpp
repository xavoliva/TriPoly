/********************************************
* Titre: Travail pratique #2 - groupe.cpp
* Date: 16 septembre 2018
* Auteur: Wassim Khene
*******************************************/

#include "groupe.h"

// Constructeurs
Groupe::Groupe() : nom_("")
{
}

Groupe::Groupe(const string& nom) : nom_(nom)
{
}


Groupe::~Groupe()
{
	for (unsigned int i = 0; i < transferts_.size(); i++)
	{
		delete transferts_[i];
		transferts_[i] = nullptr;
	}
}


// Methodes d'acces
string Groupe::getNom() const
{
	return nom_;
}

double Groupe::getTotalDepenses() const
{
	double total = 0;
	for (unsigned int i = 0; i < depenses_.size(); i++)
	{
		total += depenses_[i]->getMontant();
	}
	return total;
}

// Methodes de modifications
void Groupe::setNom(const string& nom)
{
	nom_ = nom;
}

// Methodes d'ajout
Groupe& Groupe::ajouterDepense(Depense* depense, Utilisateur* utilisateur)
{
	*utilisateur += depense;
	depenses_.push_back(depense);

	return *this;

}

Groupe & Groupe::operator+=(Utilisateur * utilisateur)
{
	utilisateurs_.push_back(utilisateur);

	return *this;
}

void Groupe::calculerComptes()
{
	double moyenne = getTotalDepenses() / utilisateurs_.size();
	for (unsigned int i = 0; i < utilisateurs_.size(); i++)
	{
		comptes_.push_back( ((utilisateurs_[i]->getTotalDepenses()) - moyenne) );
	}
}

void Groupe::equilibrerComptes()
{
	calculerComptes();
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
		if (-min <= max) {
			transferts_.push_back(new Transfert(-min, utilisateurs_[indexMin], utilisateurs_[indexMax]));
			comptes_[indexMax] += min;
			comptes_[indexMin] = 0;
		}
		else {
			transferts_.push_back(new Transfert(max, utilisateurs_[indexMin], utilisateurs_[indexMax]));
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
ostream & operator<<(ostream & o, const Groupe & g)
{
	cout << "L'evenement " << g.nom_ << " a coute un total de " << g.getTotalDepenses() << " :  \n\n";

	for (unsigned int i = 0; i < g.utilisateurs_.size(); i++) {
		cout << *(g.utilisateurs_[i]);
	}
	cout << endl;

	if (g.transferts_.size() != 0)
	{
		cout << "Les transferts suivants ont ete realiser pour equilibrer: " << endl;
		for (unsigned int i = 0; i < g.transferts_.size(); i++)
		{
			cout << "\t";
			cout << *(g.transferts_[i]);
		}
	}

	else
	{
		cout << "Les comptes ne sont pas equilibres" << endl << endl;
	}
	cout << endl;

	return cout;
}
