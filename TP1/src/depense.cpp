#include "depense.h"

Depense::Depense() : titre_("unknown"), montant_(0)
{

}

Depense::Depense(const string & titre, double montant) : titre_(titre), montant_(montant)
{

}

string Depense::getTitre() const
{
	return titre_;
}

double Depense::getMontant() const
{
	return montant_;
}

void Depense::setTitre(string & titre)
{
	titre_ = titre;
}

void Depense::setMontant(double montant)
{
	montant_ = montant;
}

void Depense::afficherDepense() const
{
	cout << "Achat: " << titre_ << " Prix: " << montant_ << endl;
}
