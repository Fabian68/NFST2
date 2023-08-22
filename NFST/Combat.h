#pragma once

#include "Zones.h"
#include <vector>
#include "Personnage.h"
#include <SFML/Audio.hpp>
class Combat
{
public:
	Combat(Equipes & Joueur, Equipes & Ia,Zones & Z,Animaux& A, Orbes& O, std::vector< sf::Sound >& allSounds);
	void modifierQuiJoue();
	void tirageRecompenses(Zones Z, Animaux A, Orbes O, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds);
	~Combat();
	sf::Sprite fond() const;
	int tour()const;
	std::vector<Personnage*> quiJoue()const;
	int quiJoueIndex()const;

private:
	Equipes _joueur;
	Equipes _ia;
	std::vector<Personnage*> _quiJoue;
	int _tour;
	int _quiJoueIndex;
	int _nbJouerPourAugmenterTour;
	sf::Texture _backgroundTexture;
	sf::Sprite _background;
};

