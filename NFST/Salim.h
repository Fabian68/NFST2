#pragma once
#include "Personnage.h"
class Salim :
	public Personnage
{
public:
	Salim(Experiences E, Orbes O, Animaux A, Objets Obj);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
	bool estTransformer;
	bool superTransformation;
};

