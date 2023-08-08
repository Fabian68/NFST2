#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Personnage.h"
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

private:
	std::vector<int> _succesDebloquer;
	std::vector<bool> _succesCache;
	std::vector<std::pair<std::string, std::string> > _listeSucces;
};

