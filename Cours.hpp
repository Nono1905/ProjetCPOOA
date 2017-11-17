/*
 * Cours.hpp
 *
 *  Created on: 1 nov. 2017
 *      Author: EVA
 */

#ifndef COURS_HPP_
#define COURS_HPP_

#include <iostream>

class Enseignant;

class Cours {

private:
	std::string nom;
	std::string dateDebut;
	std::string dateFin;
	std::string dateFinInscription;
	int nbPlace;
	Enseignant* enseignant;

public:
	// Vérifier la passage par référence
	Cours(std::string nom, std::string dateDebut, std::string dateFin, std::string dateFinInscription, int nbPlace)
	: nom(nom), dateDebut(dateDebut), dateFin(dateFin), dateFinInscription(dateFinInscription), nbPlace(nbPlace), enseignant(NULL) {};


	std::string getNom() { return nom; }
	void setEnseignant(Enseignant* e) { enseignant = e; };
	Enseignant* getEnseignant() { return enseignant; };
	const std::string getLoginEnseignant();
};

#endif /* COURS_HPP_ */
