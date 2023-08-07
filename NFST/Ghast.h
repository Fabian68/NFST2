#pragma once
#include "Personnage.h"
class Ghast :
	public Personnage
{
public:
	Ghast(int LVL, std::string nom, int difficulte = 0, int animal = 4, int rareteAnimal = 3, int id = -1);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)override;
};

