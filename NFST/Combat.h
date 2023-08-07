#pragma once

#include "Zones.h"
#include <vector>
#include "Personnage.h"
#include <SFML/Audio.hpp>
class Combat
{
public:
	Combat(Equipes   & Joueur,Equipes  & Ia,Zones & Z,Animaux& A, Orbes& O, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds);
	void tirageRecompenses(Zones Z, Animaux A, Orbes O, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds);
	~Combat();

private:
	Equipes _joueur;
	Equipes _ia;
	std::vector<Personnage*> _quiJoue;
	int _tour;
};

