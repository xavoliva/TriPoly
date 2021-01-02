#ifndef DEPENSE_INDIVIDUELLE_H
#define DEPENSE_INDIVIDUELLE_H

#include "depense.h"
#include "string"
#include <iostream>

using namespace std; 



class DepenseIndividuelle : public Depense {

public :
	DepenseIndividuelle(const string & nom, double montant, const string& lieu);
	friend ostream& operator<< (ostream& os, const DepenseIndividuelle& depense); 
 
};

#endif // !DEPENSE_INDIVIDUELLE_H

