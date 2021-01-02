#include "depenseIndividuelle.h"

DepenseIndividuelle::DepenseIndividuelle(const string & nom, double montant, const string& lieu) : Depense(nom, montant, lieu, individuelle)
{
}





ostream& operator<< (ostream& os, const DepenseIndividuelle& depense)
{
	os << "Depense individuelle : " << endl
		<< "\t" << static_cast<Depense> (depense);
	return os; 
}