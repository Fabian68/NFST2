#pragma once
#include "Personnage.h"
class Fiona :
	public Personnage
{
public:
	Fiona(Experiences E, Orbes O, Animaux A, Objets Obj);
private:
	int _nbAnimaux;
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
};

