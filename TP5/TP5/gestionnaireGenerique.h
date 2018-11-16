/********************************************
* Titre: Travail pratique #5 - gestionnaireGenerique.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/
#pragma once
/*
	class GestionnaireGenerique
	
	Méthodes :
	C getConteneur() const;
	void ajouter(T t);
	int getNombreElements() const;
	D getElementParIndex(int i) const;

	Attributs :
	C conteneur_;
*/

#include "foncteur.h"

template<typename T, typename C, typename D, typename FoncteurAjouter>
class GestionnaireGenerique
{
public:
	C getConteneur();
	void ajouter(T t);
	int getNombreElements() const;
	D getElementParIndex(int i) const;

protected:
	C conteneur_;
};

template<typename T, typename C, typename D, typename FoncteurAjouter>
C GestionnaireGenerique<T, C, D, FoncteurAjouter>::getConteneur()
{
	return conteneur_;
}

template<typename T, typename C, typename D, typename FoncteurAjouter>
void GestionnaireGenerique<T, C, D, FoncteurAjouter>::ajouter(T t)
{
	
	//FoncteurAjouter foncteur;
	FoncteurAjouter foncteur(conteneur_);
	conteneur_ = foncteur(t);

}

template<typename T, typename C, typename D, typename FoncteurAjouter>
int GestionnaireGenerique<T, C, D, FoncteurAjouter>::getNombreElements() const
{
	return (int)conteneur_.size();
}


template<typename T, typename C, typename D, typename FoncteurAjouter>
D GestionnaireGenerique<T, C, D, FoncteurAjouter>::getElementParIndex(int i) const
{
	return *next(conteneur_.begin(), i);
}

