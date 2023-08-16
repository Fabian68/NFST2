#pragma once
#include "Personnage.h"
class Chasseur :
	public Personnage
{
public:
	Chasseur(int LVL, std::string nom, int difficulte = 0, int animal = 1, int rareteAnimal = 4);
private:
	virtual void attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)override;
};

