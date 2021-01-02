/********************************************
* Titre: Travail pratique #3 - depense.h
* Date premiere version : 16 septembre 2018
* Auteur: Wassim Khene & David Dratwa
*******************************************/

#ifndef DEPENSE_H
#define DEPENSE_H

#include <string>
#include <iostream>



using namespace std;

enum TypeDepense {groupe, individuelle};

class Depense {
public:
	// Constructeurs

	Depense(const string& nom = "", double montant = 0 , const string& lieu = "Montreal", const TypeDepense & type = individuelle);
	Depense(const Depense& depense);

	// Destructeur 
	~Depense();

	// Methodes d'access
	string getNom() const;
	double getMontant() const;
	string* getLieu() const;
	TypeDepense getType() const; 

	// Methodes de modifications
	void setNom(const string& nom);
	void setMontant(double montant);
	void setLieu(const string& lieu);
	void setType(TypeDepense type); 
	
	//operateurs
	Depense& operator=(const Depense& depense);

	// Affichage
	friend ostream& operator<<(ostream& os, const Depense& depense);

private:
	string nom_;
	double montant_;
	string* lieu_;
	TypeDepense type_; 

};
#endif