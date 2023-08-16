#pragma once
#include "Personnage.h"
class Fiona :
	public Personnage
{
public:
	Fiona(Experiences E, Orbes O, Animaux A, Objets Obj);
private:
	int _nbAnimaux;
	virtual void attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)override;
};

