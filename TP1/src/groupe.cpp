#include "groupe.h"
#include "utilisateur.h"
#include "depense.h"
#include "transfert.h"

Groupe::Groupe() : nom_("unknown"), totalDepenses_(0), tailleTabUtilisateurs_(5), listeUtilisateurs_(new Utilisateur*[5]), nombreDepenses_(0), nombreUtilisateurs_(0), comptes_(new double[0]), tailleTabDepenses_(10), listeDepenses_(new Depense*[10]), nombreTransferts_(0), listeTransferts_(new Transfert*[0])
{
	
}

Groupe::Groupe(const string & nom, unsigned int tailleTabDepenses, unsigned int tailleTabUtilisateurs) : nom_(nom), totalDepenses_(0), tailleTabUtilisateurs_(tailleTabUtilisateurs), listeUtilisateurs_(new Utilisateur*[tailleTabUtilisateurs]), nombreDepenses_(0), nombreUtilisateurs_(0), comptes_(new double[nombreUtilisateurs_]), tailleTabDepenses_(tailleTabDepenses), listeDepenses_(new Depense*[tailleTabDepenses]), nombreTransferts_(0), listeTransferts_(new Transfert*[nombreUtilisateurs_])
{

}

Groupe::~Groupe()
{
	delete[] listeUtilisateurs_;
	
	listeUtilisateurs_ = nullptr;

	delete[] listeDepenses_;

	listeDepenses_ = nullptr;

	// !!!!!!!!!!!!!!!!!
	delete[] listeTransferts_;

	for (int i = 0; i < nombreTransferts_; i++)
	{
		listeTransferts_[i] = nullptr;
	}

	listeTransferts_ = nullptr;
}

string Groupe::getNom() const
{
	return nom_;
}

unsigned int Groupe::getNombreDepenses() const
{
	return nombreDepenses_;
}

double Groupe::getTotal() const
{
	return totalDepenses_;
}

void Groupe::setNom(string & nom)
{
	nom_ = nom;
}

void Groupe::ajouterDepense(Depense * uneDepense, Utilisateur * payePar)
{
	if (nombreDepenses_ >= tailleTabDepenses_)

	{
		//nouveau tableau et copier tout
		Depense  ** copylisteDepense;
		copylisteDepense = nullptr;

		copylisteDepense = new Depense*[2 * tailleTabDepenses_];

		for (unsigned int i = 0; i < 2 * tailleTabDepenses_; i++)
		{
			copylisteDepense[i] = nullptr;
		}

		for (unsigned int i = 0; i < tailleTabDepenses_; i++)
		{
			copylisteDepense[i] = listeDepenses_[i];
		}

		delete[] listeDepenses_;
		listeDepenses_ = copylisteDepense;
		tailleTabDepenses_ *= 2;
	}

	listeDepenses_[nombreDepenses_] = uneDepense;
	nombreDepenses_++;

	payePar->ajouterDepense(uneDepense);
}

void Groupe::ajouterUtilisateur(Utilisateur * unUtilisateur)
{
	if (nombreUtilisateurs_ >= tailleTabUtilisateurs_)

	{
		//nouveau tableau et copier tout
		Utilisateur  ** copylisteUtilisateur;
		copylisteUtilisateur = nullptr;

		copylisteUtilisateur = new Utilisateur*[2 * tailleTabUtilisateurs_];

		for (unsigned int i = 0; i < 2 * tailleTabUtilisateurs_; i++)
		{
			copylisteUtilisateur[i] = nullptr;
		}

		for (unsigned int i = 0; i < tailleTabUtilisateurs_; i++)
		{
			copylisteUtilisateur[i] = listeUtilisateurs_[i];
		}

		delete[] listeUtilisateurs_;
		listeUtilisateurs_ = copylisteUtilisateur;
		tailleTabUtilisateurs_ *= 2;
	}

	listeUtilisateurs_[nombreUtilisateurs_] = unUtilisateur;
	nombreUtilisateurs_++;
}

void Groupe::calculerTotalDepenses()
{
	// calculer depense total pour le groupe
	for (unsigned int i = 0; i < nombreUtilisateurs_; i++)
	{
		listeUtilisateurs_[i]->calculerTotal();
		totalDepenses_ += listeUtilisateurs_[i]->getTotal();
	}



	double moyenne = totalDepenses_ / nombreUtilisateurs_;

	for (unsigned int i = 0; i < nombreUtilisateurs_; i++)
	{
		comptes_[i] = listeUtilisateurs_[i]->getTotal() - moyenne;
	}
}

void Groupe::equilibrerComptes()
{
	/*
	//copier liste comptes_
	double* copycomptes;
	copycomptes = nullptr;
	copycomptes = new double[nombreUtilisateurs_];

	for (int i = 0; i < nombreUtilisateurs_; i++)
	{
		copycomptes[i] = comptes_;
	}
	*/

	double max = 0;
	double min = 0;
	int placemin;
	int placemax;

	for (unsigned int n = 0; n < nombreUtilisateurs_; n++)

	{

		for (unsigned int i = 0; i < nombreUtilisateurs_; i++)
		{
			if (comptes_[i] > max)
			{
				max = comptes_[i];
				placemax = i;
			}

			if (comptes_[i] < min)
			{
				min = comptes_[i];
				placemin = i;
			}
		}

		if (max == min)
			break;

		else if (max + min >= 0)
		{
			max += min;
	
			Transfert* transfert = new Transfert(abs(min), listeUtilisateurs_[placemin], listeUtilisateurs_[placemax]);

			min = 0;

			listeTransferts_[n] = transfert;

			comptes_[placemin] = min;
			comptes_[placemax] = max;

			nombreTransferts_++;
		}

		else
		{
			min += max;
	
			Transfert* transfert = new Transfert(max, listeUtilisateurs_[placemin], listeUtilisateurs_[placemax]);
			max = 0;
			nombreTransferts_++;
			listeTransferts_[n] = transfert;

			comptes_[placemin] = min;
			comptes_[placemax] = max;
			

		}
	}


}

void Groupe::afficherGroupe() const
{


	cout << "L'evenement: " << nom_ << " a coute un total pour le groupe de: " << totalDepenses_ << "."<< endl;
	cout << "Voici les depenses:" << endl;
	int dejaequilibre = 1;

	for (unsigned int i = 0; i < nombreUtilisateurs_; i++)
	{

		listeUtilisateurs_[i]->afficherUtilisateur();

		if (comptes_[i] != 0)
			dejaequilibre = 0;
	}

	if (dejaequilibre == 0)
	{
		cout << "soit les comptes suivants:" << endl;
		for (unsigned int i = 0; i < nombreUtilisateurs_; i++)
		{
			cout << listeUtilisateurs_[i]->getNom() << ": " << comptes_[i] << endl;
		}
		cout << endl;
	}

	else
	{
		for (unsigned int i = 0; i < nombreTransferts_; i++)
		{
			listeTransferts_[i]->afficherTransfert();
		}
	}
}