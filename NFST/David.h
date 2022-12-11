#pragma once
#include "Personnage.h"
class David :
	public Personnage
{
public:
	David(Experiences E, Orbes O, Animaux A, Objets Obj);
private:

	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

