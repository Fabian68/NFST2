#pragma once
#include "Personnage.h"
class Magicien :
	public Personnage
{
public:
	Magicien(int LVL, std::string nom, int difficulte = 0, int animal = 9, int rareteAnimal = 5);
private:
	virtual void attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)override;
	int stade;
};

