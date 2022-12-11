#pragma once
#include "Personnage.h"
#include <SFML/Audio.hpp>

class Fabian :
	public Personnage
{
public:
	Fabian(Experiences E,Orbes O,Animaux A,Objets Obj);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;

	sf::SoundBuffer  buffer;
	sf::Sound  sound;
};

