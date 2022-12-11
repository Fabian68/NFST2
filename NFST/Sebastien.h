#pragma once
#include "Personnage.h"
class Sebastien :
	public Personnage
{
public:
	Sebastien(Experiences E, Orbes O, Animaux A, Objets Obj);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
	int pause;
};

