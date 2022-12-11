#pragma once
#include "Personnage.h"
class Wither :
	public Personnage
{
public:
	Wither(int LVL, std::string nom, int difficulte = 0, int animal = 6, int rareteAnimal = 5, int id = -1);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

