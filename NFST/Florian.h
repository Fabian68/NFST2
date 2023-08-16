#pragma once
#include "Personnage.h"
class Florian :
	public Personnage
{
public:
	Florian(Experiences E, Orbes O, Animaux A, Objets Obj);
	virtual void attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)override;
	bool floppy;
	bool floppylegende;
};

