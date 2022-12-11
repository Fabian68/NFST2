#pragma once
#include "Personnage.h"


class Nicolas :
	public Personnage
{
public:
	Nicolas(Experiences E,Orbes O,Animaux A, Objets Obj);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};


