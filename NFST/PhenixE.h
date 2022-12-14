#pragma once
#include "Personnage.h"
class PhenixE :
	public Personnage
{
public:
	PhenixE(int LVL, std::string nom,int taille=1, int difficulte = 0, int animal = 9, int rareteAnimal = 5);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
	int _taille;
};
