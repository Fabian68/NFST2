#pragma once
#include "Personnage.h"
class Magicien :
	public Personnage
{
public:
	Magicien(int LVL, std::string nom, int difficulte = 0, int animal = 9, int rareteAnimal = 5);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
	int stade;
};

