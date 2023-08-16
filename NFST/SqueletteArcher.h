#pragma once
#include "Personnage.h"
class SqueletteArcher :
	public Personnage
{
public:
	SqueletteArcher(int LVL, std::string nom, int difficulte = 0, int animal = 5, int rareteAnimal = 2, int id = -1);
private:
	virtual void attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)override;
};

