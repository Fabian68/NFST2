#pragma once
#include "Personnage.h"
class Rapace :
	public Personnage
{
public:
	Rapace(int LVL, std::string nom, int difficulte = 0, int animal = 1, int rareteAnimal = 4);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)override;

};