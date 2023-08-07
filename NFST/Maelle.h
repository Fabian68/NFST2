#pragma once
#include "Personnage.h"
class Maelle :
	public Personnage
{
public:
	Maelle(Experiences E, Orbes O, Animaux A, Objets Obj);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)override;
	bool estTransformer;
};

