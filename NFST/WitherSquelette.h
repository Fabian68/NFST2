#pragma once
#include "Personnage.h"
class WitherSquelette :
	public Personnage
{
public:
	WitherSquelette(int LVL, std::string nom, int difficulte = 0, int animal = 6, int rareteAnimal = 3, int id = -1);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

