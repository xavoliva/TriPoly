/********************************************
* Titre: Travail pratique #2 - groupe.cpp
* Date: 16 septembre 2018
* Auteur: Wassim Khene & David Dratwa
*******************************************/

#include "groupe.h"

// Constructeurs

//Groupe::Groupe() {
//	nom_ = ""; 
//}

Groupe::Groupe(const string& nom) : nom_(nom) {
}

Groupe::~Groupe() {
	for (int i = 0; i < transferts_.size(); i++) {
		delete transferts_[i];
	}
}


// Methodes d'acces
string Groupe::getNom() const {
	return nom_;
}



vector<DepenseGroupe*> Groupe::getDepenses() const
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


double Groupe::getTotalDepenses() const {

	return totalDepenses_;
}

////MAYBE
vector<double> Groupe::getComptes() const
{
	return comptes_;
}

// Methodes de modifications
void Groupe::setNom(const string& nom) {
	nom_ = nom;
}

// Methodes d'ajout
Groupe& Groupe::ajouterDepense(Depense* depense, Utilisateur* payePar, vector<Utilisateur*> payePour)
{
	//PROBLEM ICI!!!!
	bool flag = false;
	unsigned int count = 0;

	for (unsigned int i = 0; i < utilisateurs_.size(); i++)
	{
		if (utilisateurs_[i] == payePar)
		{
			flag = true;
			break;
		}
	}

	for (unsigned int i = 0; i < utilisateurs_.size(); i++)
	{
		for (unsigned int k = 0; k < payePour.size(); k++)
		{
			if (utilisateurs_[i] == payePour[k])
			{
				count++;
			}
		}

		if (count == payePour.size())
			break;
	}



	if (flag == true && count == payePour.size() && depense->getType() == groupe)
	{


		*payePar += depense;

		for (unsigned int i = 0; i < payePour.size(); i++)
			*payePour[i] += depense;
		
		static_cast<DepenseGroupe>(*depense).setNombreParticipants(payePour.size() + 1);
		cout << "Hello";
		unsigned int montant = static_cast<DepenseGroupe>(*depense).getMontantPersonnel();
		vector<int> indexs;
		int indexPayerPar;
		
		for (unsigned int i = 0; i < utilisateurs_.size(); i++)
		{
			for (unsigned int k = 0; k < payePour.size(); k++)
			{
				if (utilisateurs_[i] == payePour[k])
				{
					indexs.push_back(i);
				}
			}
		}
	
		for (unsigned int i = 0; i < utilisateurs_.size(); i++)
		{
			if (utilisateurs_[i] == payePar)
			{
				indexPayerPar = i;
			}
		}

	

		for (unsigned int i = 0; i < indexs.size(); i++)
			comptes_[indexs[i]] -= montant;

		comptes_[indexPayerPar] += depense->getMontant() - montant;


		depenses_.push_back(&static_cast<DepenseGroupe>(*depense));


	}

	else
	{
		cout << "Erreur: vous tentez d'ajouter une depense individuelle au groupe ou alors les personnes impliquees dans la depense groupe ne sont pas dans le groupe." << endl;
	}

	return *this;
}

Groupe& Groupe::operator+=(Utilisateur* utilisateur)
{
	//VOIR SI UTILISATEUR REGULIER DEJA DANS UN AUTRE GROUPE!!!
	if (utilisateur->getType() == Regulier)
	{

		//CHELOU
		if (static_cast<UtilisateurRegulier>(*utilisateur).estGroupe())
		{
			cout << "L'utilisateur " << utilisateur->getNom() << " n'est pas souscrit(e) a un abonnement premium, et a deja un groupe." << endl;
		}
		//CHELOU

		else
		{
			utilisateurs_.push_back(utilisateur);
			comptes_.push_back(0);
		}
	}

	else
	{
		utilisateurs_.push_back(utilisateur);
		comptes_.push_back(0);
	}

	return *this;
}

void Groupe::equilibrerComptes() {
	
	bool calcul = true;
	int count = 0;
	while (calcul) {
		double max = 0;
		double min = 0;
		int indexMax = 0;
		int indexMin = 0;

		// On cherche le compte le plus eleve et le moins eleve
		for (int i = 0; i < utilisateurs_.size(); i++) {
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


			transferts_.push_back(new Transfert(-min, utilisateurs_[indexMin], utilisateurs_[indexMax]));
			if (utilisateurs_[indexMin]->getType() == Premium)
			{
				static_cast<UtilisateurPremium>(*(utilisateurs_[indexMin])).calculerTaux();
				double montant = (-min)*static_cast<UtilisateurPremium>(*(utilisateurs_[indexMin])).getTaux();

				utilisateurs_[indexMin]->ajouterInteret(montant);
			}
			else
			{
				utilisateurs_[indexMin]->ajouterInteret((-min)*TAUX_REGULIER);
			}
			comptes_[indexMax] += min;
			comptes_[indexMin] = 0;
	
		}
		else if (-min > max  && min != 0 && max != 0) {
			transferts_.push_back(new Transfert(max, utilisateurs_[indexMin], utilisateurs_[indexMax]));
			if (utilisateurs_[indexMin]->getType() == Premium)
			{
				static_cast<UtilisateurPremium>(*(utilisateurs_[indexMin])).calculerTaux();
				double montant = max*static_cast<UtilisateurPremium>(*(utilisateurs_[indexMin])).getTaux();

				utilisateurs_[indexMin]->ajouterInteret(montant);
			}
			else
			{
				utilisateurs_[indexMin]->ajouterInteret(max*TAUX_REGULIER);
			}
			comptes_[indexMax] = 0;
			comptes_[indexMin] += max;
			

		}

		// On incremente le nombre de comptes mis a 0
		count++;
		if (-min == max)
		{
			count++;
		}
		if (count >= utilisateurs_.size() - 1)
		{
			calcul = false;
		}
	}
	
}

void Groupe::calculerTotalDepense()
{
	totalDepenses_ = 0;
	for (unsigned int i = 0; i < utilisateurs_.size(); i++)
	{
		utilisateurs_[i]->calculerTotalDepenses();
	}

	for (unsigned int i = 0; i < depenses_.size(); i++)
	{
		totalDepenses_ += depenses_[i]->getMontant();
	}
	
}

// Methode d'affichage
ostream & operator<<(ostream& os, const Groupe& groupe)
{

	os << "L'evenement nomme : " << groupe.nom_ << " a coute un total de (en terme de depenses groupees): " << groupe.getTotalDepenses() << ", voici les utilisateurs et toutes leurs depenses : \n";

	for (unsigned int i = 0; i < groupe.utilisateurs_.size(); i++) {
		cout << *(groupe.utilisateurs_[i]);
	}
	cout << endl;

	if (groupe.transferts_.size() != 0)
	{
		cout << "Les transferts suivants ont ete realiser pour equilibrer: " << endl;
		for (unsigned int i = 0; i < groupe.transferts_.size(); i++)
		{
			cout << "\t";
			cout << *(groupe.transferts_[i]);
		}
	}

	else
	{
		cout << "Les comptes ne sont pas equilibres. Voici les comptes: " << endl;
		
		for (unsigned int i = 0; i < groupe.comptes_.size(); i++)
		{
			cout << groupe.utilisateurs_[i]->getNom() << " : " << groupe.comptes_[i] << endl;
		}
			
		cout << endl << endl;
	}

	return cout;
}
