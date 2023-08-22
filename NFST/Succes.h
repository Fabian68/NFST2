#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Personnage.h"

const int SUCCES_BOING = 0;
const int SUCCES_NIV1 = 1;
const int SUCCES_NIV5 = 2;
const int SUCCES_NIV10 = 3;
const int SUCCES_NIV15 = 4;
const int SUCCES_NIV20 = 5;
const int SUCCES_NIV25 = 6;
const int SUCCES_NIV50 = 7;
const int SUCCES_OBJET_LEGENDAIRE = 8;
const int SUCCES_ANIMAL_LEGENDAIRE = 9;
const int SUCCES_ORBE_LEGENDAIRE = 10;
const int SUCCES_OEUF_TORTUE = 11;
const int SUCCES_CENDRE_PHENIX = 12;
const int SUCCES_NIV25_NICOLAS = 13;
const int SUCCES_NIV25_FIONA = 14;
const int SUCCES_NIV10_2PERSOS = 15;
const int SUCCES_NIV10_FABIAN_FIONA = 16;
const int SUCCES_NIV25_3PERSOS = 17;
const int SUCCES_NIV10_NICOLAS_SEBASTIEN = 18;
const int SUCCES_NIV25_FABIAN_FIONA_CLOE = 19;
const int SUCCES_10SUCCES = 20;
class Succes
{
public:
	Succes();
	void sauvegarder();
	bool estDebloque(int succes)const;
	void affichageDeblocageSucces(int succes, std::vector< sf::Sound>)const;
	void debloquerSucces(int succes);
	void appliquerBonus(Personnage* P);

	void afficherTexte(float x, float y, std::string texte, sf::Color couleurTexte, sf::RenderWindow* window) const;

	int nombres() const;
	bool estCache(int i)const;
	std::string nom(int i)const;
	std::string description(int i)const;

	int nbSuccesDebloque() const;

private:
	std::vector<int> _succesDebloquer;
	std::vector<bool> _succesCache;
	std::vector<std::pair<std::string, std::string> > _listeSucces;
};

