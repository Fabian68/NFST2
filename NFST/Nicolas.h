#pragma once
#include "Personnage.h"


class Nicolas :
	public Personnage
{
public:
	Nicolas(Experiences E,Orbes O,Animaux A, Objets Obj);
private:
	int _compteur_tour_joue;
	virtual void attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)override;
};


