#include "utilisateur.h"
#include "depense.h"

Utilisateur::Utilisateur():nom_("unknown"),	tailleTabDepense_(5),nombreDepenses_(0),totalDepense_(0), listeDepenses_(new Depense*[5])
{
	
}

Utilisateur::Utilisateur(const string & nom):nom_(nom),	tailleTabDepense_(5),nombreDepenses_(0),totalDepense_(0), listeDepenses_(new Depense*[5])
{

}

Utilisateur::~Utilisateur()
{
	delete[] listeDepenses_;
	
	listeDepenses_ = nullptr;
	
}

string Utilisateur::getNom() const
{
	return nom_;
}

unsigned int Utilisateur::getNombreDepense() const
{
	return nombreDepenses_;
}

double Utilisateur::getTotal() const
{
	return totalDepense_;
}

void Utilisateur::setNom(string & nom)
{
	nom_ = nom;
}

void Utilisateur::ajouterDepense(Depense * uneDepense)
{
	if (nombreDepenses_ >= tailleTabDepense_) //si tableau est déjà plein

	{
		// créer nouveau tableau deux fois plus grand et copier tous les élements

		//initialiser copylisteDepenses
		Depense  ** copylisteDepenses;
		copylisteDepenses = nullptr;

		copylisteDepenses = new Depense*[2 * tailleTabDepense_];

		for (unsigned int i = 0; i < 2 * tailleTabDepense_; i++)
		{
			copylisteDepenses[i] = nullptr;
		}

		// boucle for pour copier chaque élement dans le nouveau tableau
		for (unsigned int i = 0; i < tailleTabDepense_; i++)
		{
			copylisteDepenses[i] = listeDepenses_[i];
		}

		//supprimer listeDepenses_
		delete[] listeDepenses_;

		// la nouvelle listeDepenses_ est le nouveau tableau plus grand
		listeDepenses_ = copylisteDepenses;
		tailleTabDepense_ *= 2;
	}

	//ajouter nouvelle dépense
	listeDepenses_[nombreDepenses_] = uneDepense;
	nombreDepenses_++;
}

void Utilisateur::calculerTotal()
{
	for (unsigned int i = 0; i < nombreDepenses_; i++)
	{
		totalDepense_ += listeDepenses_[i]->getMontant();
	}

}

void Utilisateur::afficherUtilisateur() const
{
	cout << "Utilisateur: " << nom_ << " a depense pour un total de: " << totalDepense_ << endl;
	cout << "Liste de depenses:" << endl;

	//Afficher chaque dépense pour utilisateur
	for (unsigned int i = 0; i < nombreDepenses_; i++)
	{
		listeDepenses_[i]->afficherDepense();
		cout << endl;
	}

}
