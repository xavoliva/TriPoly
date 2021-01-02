/********************************************
* Titre: Travail pratique #3 - depenseGroupe.h
* Date premiere version : 2 octobre 2018
* Auteur: David Dratwa
*******************************************/


#ifndef DEPENSE_GROUPE_H
#define DEPENSE_GROUPE_H

#include "depense.h"

#include <vector>

using namespace std; 

class DepenseGroupe : public Depense {
public:
	//constructeur
	DepenseGroupe( const string& nom = "", double montant = 0, const string& lieu = "Montreal");
	DepenseGroupe(const Depense& depense); 

	//getters 
	unsigned int getNombreParticipants() const; 
	double getMontantPersonnel() const;

	//setters
	void setNombreParticipants(unsigned int nombre); 


	//surcharge 
	friend ostream& operator<<(ostream& os, const DepenseGroupe& depense); 
private : 
	//Les utilisateurs qui partageront la depense
	unsigned int  nombreParticipants_; 
};

#endif // !DEPENSE_GROUPEE_H
