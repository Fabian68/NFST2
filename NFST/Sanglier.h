#pragma once
#include "Personnage.h"

class Sanglier :
	public Personnage
{
public:
	Sanglier(int LVL, std::string nom, int difficulte = 0, int animal = -1, int rareteAnimal = 0, int id = -1);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

