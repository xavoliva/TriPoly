#include "gestionnaireDepenses.h"

#include <algorithm>
#include <functional>
#include <numeric>


double GestionnaireDepenses::getTotalDepenses() const
{
	double totalDepenses = 0;

	for (Depense* depense : conteneur_) {
		totalDepenses += depense->getMontant();
	}

	return totalDepenses;

	//return accumulate(conteneur_.begin(), conteneur_.end(), 0);
	
}


