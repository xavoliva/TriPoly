#include "utilisateurPremium.h"

UtilisateurPremium::UtilisateurPremium(const string & nom) : Utilisateur(nom), joursRestants_(30), taux_(0.05)
{
}

UtilisateurPremium::UtilisateurPremium(const Utilisateur & utilisateur) : Utilisateur(utilisateur), joursRestants_(30), taux_(0.05)
{
}

unsigned int UtilisateurPremium::getJoursRestants() const
{
	return joursRestants_;
}

double UtilisateurPremium::getTaux() const
{
	return taux_;
}

void UtilisateurPremium::setJoursRestants(unsigned int joursRestants)
{
	joursRestants_ = joursRestants;

	if (joursRestants == 0)
		cout << "Erreur: L'utilisateur " << getNom() << " doit renouveler son abonnement." << endl;
}

void UtilisateurPremium::calculerTaux()
{
	taux_ = 0.05;

	if (getNombreDepenses() < 10)
	{
		for (int i = 0; i < floor(getNombreDepenses() / 2); i++)
			taux_ -= 0.01;
	}

	else
	{
		taux_ = 0;
	}



}

UtilisateurPremium & UtilisateurPremium::operator=(Utilisateur * utilisateur)
{
	if (this != utilisateur)
	{
		*this = utilisateur;
		joursRestants_ = 30;
		taux_ = 0.05;
	}

	return *this;
}

ostream & operator<<(ostream & os, const UtilisateurPremium & utilisateur)
{

	os << static_cast<Utilisateur>(utilisateur);
	os << "taux final: " << utilisateur.taux_ << endl;
	os << "Nombre de jours restants: " << utilisateur.joursRestants_ << endl;
	return os;
}
