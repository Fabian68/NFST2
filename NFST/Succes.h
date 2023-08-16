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
const int SUCCES_NIV30 = 7;
const int SUCCES_NIV35 = 8;
const int SUCCES_NIV40 = 9;
const int SUCCES_NIV45 = 10;
const int SUCCES_NIV50 = 11;
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

private:
	std::vector<int> _succesDebloquer;
	std::vector<bool> _succesCache;
	std::vector<std::pair<std::string, std::string> > _listeSucces;
};

