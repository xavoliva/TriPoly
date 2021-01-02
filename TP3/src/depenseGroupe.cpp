#include "depenseGroupe.h"

DepenseGroupe::DepenseGroupe(const string & nom, double montant, const string & lieu) : Depense(nom, montant, lieu, groupe), nombreParticipants_(0)
{

}



DepenseGroupe::DepenseGroupe(const Depense & depense) : Depense(depense), nombreParticipants_(0)
{
	setType(groupe);

	if(depense.getType() == groupe)
		setNombreParticipants(static_cast<DepenseGroupe>(depense).nombreParticipants_);
}

unsigned int DepenseGroupe::getNombreParticipants() const
{
	return nombreParticipants_;
}

double DepenseGroupe::getMontantPersonnel() const
{
	if (nombreParticipants_ != 0)
	{
		return getMontant() / nombreParticipants_;
	}

	return 0;
}

void DepenseGroupe::setNombreParticipants(unsigned int nombre)
{
	nombreParticipants_ = nombre;
}

ostream & operator<<(ostream & os, const DepenseGroupe & depense)
{
	return os << "Depense de groupe :     "
	<< static_cast<Depense>(depense) << "fait part : " << depense.nombreParticipants_ << "personnes, soit : "
	<< depense.getMontantPersonnel() << "par personne." << endl;
}
