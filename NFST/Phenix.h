#pragma once
#include "Personnage.h"
class Phenix :
    public Personnage
{
public:
	Phenix(Experiences E, Orbes O, Animaux A, Objets Obj);
private:
	virtual void attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)override;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)override;
	void remettreAZero();
	void sauvegarderCharge();
	
	int _taille;
	int _stack;
};

