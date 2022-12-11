#pragma once
#include "Personnage.h"
class Cerf :
	public Personnage
{
public:
	Cerf(int LVL, std::string nom, int difficulte = 0, int animal = 3, int rareteAnimal = 1);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

