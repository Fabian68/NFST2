#pragma once
#include "Personnage.h"
class Phenix :
    public Personnage
{
public:
	Phenix(Experiences E, Orbes O, Animaux A, Objets Obj);
private:
	virtual void attaqueEnnemis(sf::RenderWindow* window)override;
	virtual void passif(int tour, sf::RenderWindow* window)override;
	virtual void passifDefensif(sf::RenderWindow* window)override;
	void sauvegarderCharge();
	void remettreAZero();
	int _taille;
	int _stack;
};

