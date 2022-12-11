#pragma once
#include "Personnage.h"
class Grognard :
	public Personnage
{
public:
	Grognard(int LVL, std::string nom, int difficulte = 0, int animal = 2, int rareteAnimal = 4);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

