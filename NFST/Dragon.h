#pragma once
#include "Personnage.h"
class Dragon :
	public Personnage
{
public:
	Dragon(int LVL, std::string nom, int difficulte = 0, int animal = 9, int rareteAnimal = 5, int id = -1);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

