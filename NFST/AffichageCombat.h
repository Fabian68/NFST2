#pragma once
//#include <SFML/Graphics.hpp>
#include <math.h>
#include "Personnage.h"
#include "Delais.h"
#include <iostream>

class AffichageCombat
{
public:
	AffichageCombat();
	void afficherTexte(float x, float y, std::string texte, sf::Color couleurTexte, sf::RenderWindow* window)const;
	void dessinerJoueur(int indice, bool equipeIA, Personnage* P, sf::RenderWindow* window)const;
	void dessinerTexteModificationVie(Personnage* P, sf::RenderWindow* window) const;
	void dessinerEquipeJoueur(Equipes  J, sf::RenderWindow* window)const;
	void dessinerEquipeIA(Equipes I, sf::RenderWindow* window)const;
	void dessinerDeuxEquipes(Equipes J, Equipes E, Combat & C, sf::RenderWindow* window)const;
	void dessinerAttaque(Personnage* Attaquant, Personnage* Defenseur, sf::RenderWindow* window);
	void afficherStats(Equipes joueur, sf::RenderWindow* window);
	void dessinerTour(std::vector<Personnage*> quiJoue,int index, sf::RenderWindow* window);
	void cleanMainZone(sf::RenderWindow* window)const;
private:
	
};

