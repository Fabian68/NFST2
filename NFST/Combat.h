#pragma once

#include "Zones.h"
#include <vector>
#include "Personnage.h"
class Combat
{
public:
	Combat(Equipes   & Joueur,Equipes  & Ia,Zones & Z,Animaux& A, Orbes& O, sf::RenderWindow* window);
	void tirageRecompenses(Zones Z, Animaux A, Orbes O, sf::RenderWindow* window);
	~Combat();

private:
	Equipes _joueur;
	Equipes _ia;
	std::vector<Personnage*> _quiJoue;
	int _tour;
};

