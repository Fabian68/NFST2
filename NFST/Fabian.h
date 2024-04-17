#pragma once
#include "Personnage.h"
#include <SFML/Audio.hpp>

class Fabian :
	public Personnage
{
public:
	Fabian(Experiences E,Orbes O,Animaux A,Objets Obj);
private:
	virtual void attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)override;
	std::vector<std::shared_ptr<sf::SoundBuffer>> _allBuffers;
	std::vector<sf::Sound> _allSounds;
};

