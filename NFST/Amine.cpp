#include "Amine.h"
#include "Affichage.h"	

Amine::Amine(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(10, E, O, A, Obj, "Amine", 1, 8, 1, 20, 50, -50, 5, 50, 0,5)
{
}

void Amine::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	
	switch (choix) {

	case 0:
		Affichage().dessinerTexte(nom() + " poings du dragon ! ",window);
		equipeEnnemi().plusProcheVivant()->ajouterReduction(-2);
		DEGATS = degats(1.0, 2.0);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " a la flemme ",window);
		if (vie() == vieMax()&& bouclier()==bouclierMax()) {
			attaqueEnnemis(window,allSounds);
		}
		else {
			SOINS = soins(0.4, 0.8);
			soigner(SOINS * 2, this,window);
			bouclier(SOINS, this,window);
		}
		ajouterMana(1);
		break;
	case 2:
		Affichage().dessinerTexte(nom() + "se prepare ",window);
		ajouterCoupCritique(1);
		ajouterDegatsCritique(5);
		ajouterMana(3);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " ASURA STRIKE ! ",window);
		DEGATS = degats(5.0, 10.0)+degats(0.5,2.0,CHOIXBOUCLIER);
		reduireBouclier(bouclierMax());
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
		ajouterMana(-3);
		break;
	}
}

void Amine::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int DEGATS;
	double ratio = equipeEnnemi().plusProcheVivant()->pourcentageReduction() / 20.0;
	
	if ((tour + 1) % 8 == 0) {
		Affichage().dessinerTexte(nom() + " fist du dragon ! ",window);
		DEGATS = degats(ratio, ratio * 3.0 +0.1);
		if (DEGATS <= 0) {
			DEGATS = 1;
		}
		AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),window);
	}
}

void Amine::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
	bouclier(niveau(), this,window);
}
