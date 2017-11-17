/*
 * Etudiant.hpp
 *
 *  Created on: 6 nov. 2017
 *      Author: EVA
 */

#ifndef ETUDIANT_HPP_
#define ETUDIANT_HPP_

#include <iostream>
#include <list>

#include "Cours.hpp"

class Etudiant {

protected:
	std::string login;
	std::string motDePasse;
	std::list<Cours> listeCours;

public:
	Etudiant(std::string login, std::string motDePasse) : login(login), motDePasse(motDePasse) {};
	const std::string getLogin() { return login; }
	bool verifMDP(const std::string mdp) { return mdp.compare(motDePasse) == 0 ? true : false; }
	std::list<Cours>::iterator getPremierCours() { return listeCours.begin(); };
	std::list<Cours>::iterator getDernierCours() { return listeCours.end(); };

};


#endif /* ETUDIANT_HPP_ */
