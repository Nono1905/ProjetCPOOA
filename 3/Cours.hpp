
/*
 * @file Cours.hpp
 *
 * @date 1 nov. 2017
 * @author EVA
 */

#ifndef COURS_HPP_
#define COURS_HPP_

#include <iostream>
#include <list>

// Classes définies ici pour éviter l'inclusion circulaire
class Enseignant; 
class Etudiant;

/**
 * @class Cours
 */
class Cours {

private:

	std::string nom; // Nom du cours
	std::string dateDebut;// Date de debut du cours
	std::string dateFin;// Date de fin du cours
	std::string dateFinInscription;// Date de fin des inscriptions
	int nbPlace;// Nombre de place disponible
	Enseignant* enseignant;//Enseignant responsable du cours
	std::list<Etudiant*> listeEtudiantP;
	std::list<Etudiant*> listeEtudiantA;
	bool validation;


public:

	/**
	 * @brief Constructeur de l'objet Cours
	 * @param nom Le nom du cours
	 * @param dateDebut Date de commencement du cours
	 * @param dateFin Date de fin du cours
	 * @param dateFinInscription Date de fin d'inscription au cours
	 * @param nbPlace Nombre de place disponible pour le cours
	 * @version 1
	 *
	 */
	Cours(std::string nom, std::string dateDebut, std::string dateFin, std::string dateFinInscription, int nbPlace)
	: nom(nom), dateDebut(dateDebut), dateFin(dateFin), dateFinInscription(dateFinInscription), nbPlace(nbPlace), enseignant(NULL) {
		validation=false;
	}

	/**
	 * @brief Renvoie le nom du cours
	 * @return std::string
	 * @version 1
	 *
	 */
	std::string getNom() { return nom; }

	/**
	 * @brief Defini l'enseignant responsable du cours
	 * @param e L'enseignant qui deviendra responsable
	 * @version 1
	 *
	 */
	void setEnseignant(Enseignant& e) { enseignant = &e; }

	/**
	 * @brief Renvoie l'enseigant responsable du cours
	 * @return Enseignant&
	 * @version 1
	 *
	 */
	Enseignant& getEnseignant() { return *enseignant ;}

	/**
	 * @brief Renvoie le login de l'enseigant responsable du cours
	 * @return const std::string
	 * @version 1
	 *
	 */
	const std::string getLoginEnseignant();

	/**
	 * @brief Renvoie le boolean de validité du cours
	 * @return boolean
	 * @version 3
	 *
	 */
	bool getStatus() { return validation ;}

	/**
	 * @brief Supprime un etudiant a la liste principale/attente
	 * @param etu Etudiant devant etre ajouter a la liste
	 * @version 3
	 */
	void removeEtudiant(Etudiant& etu){
		listeEtudiantA.remove(&etu);
		listeEtudiantP.remove(&etu);
		if (listeEtudiantP.size() < (size_t)nbPlace){
			listeEtudiantP.push_back(*listeEtudiantA.begin());
			listeEtudiantA.remove(*listeEtudiantA.begin());
		}
	}

	/**
	 * @brief Renvoie la liste des etudiant sur la liste principale d'inscription au cours
	 * @return std::list<Etudiant*>
	 * @version 3
	 *
	 */
	std::list<Etudiant*> getListeEtudiantP() { return listeEtudiantP; }

	/**
	 * @brief Renvoie la liste des etudiant sur la liste d'attente d'inscription au cours
	 * @return std::list<Etudiant*>
	 * @version 3
	 *
	 */
	std::list<Etudiant*> getListeEtudiantA() { return listeEtudiantA; }

	/**
	 * @brief Ajoute un etudiant a la liste principale/attente
	 * @param etu Etudiant devant etre ajouter a la liste
	 * @version 3
	 *
	 */
	void addEtudiant(Etudiant& etu){
		if (getStatus()){
			if (listeEtudiantP.size() >= (size_t)nbPlace){
				listeEtudiantA.push_back(&etu);
			}else{
				listeEtudiantP.push_back(&etu);
			}
		}
	}

	/**
	 * @brief Setter pour l'attribut validation
	 * @param b Valeur du boolean
	 * @version 3
	 *
	 */
	void setValidation(bool b){ validation=b; }

	/**
	 * @brief Redefinition de l'operateur == pour pouvoir l'utiliser sur des cours, utile pour list.remove
	 * par exemple
	 * @return bool
	 * @version 1
	 */
	bool operator==( const Cours& test ) const {
		return this->nom == test.nom;
	}

	/**
	 * @brief Affiche les étudiants des deux listes (principale et attente)
	 * @return std::string
	 * @version 3
	 */
	std::string afficherListesEtudiants();

	/**
	 * @brief Permet d'afficher tous les étudiants de la liste principale
	 * @return La liste des étudiants en liste principale
	 * @version 3
	 */
	std::string afficherListeP();

	/**
	 * @brief Permet d'afficher tous les étudiants de la liste d'attente
	 * @return La liste des étudiants en liste d'attente
	 * @version 3
	 */
	std::string afficherListeA();
};

#endif /* COURS_HPP_ */
