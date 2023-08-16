#include "Amine.h"
#include "Affichage.h"	

Amine::Amine(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(10, E, O, A, Obj, "Amine", 1, 5, 1, 0, 25, -50, 5, 50, 0,5)
{
}

void Amine::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	int point_mana = mana();
	switch (choix) {

	case 0:
		Affichage().dessinerTexte(nom() + " poings du dragon ! ",window);
		DEGATS = degats(0.8, 1.2);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C,window, allSounds);
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " a la flemme ",window);
		if (vie() == vieMax()&& bouclier()==bouclierMax()) {
			attaqueEnnemis(C, window,allSounds );
		}
		else {
			SOINS = soins(0.1, 0.3);
			soigner(SOINS * 2, C, this, window);
			bouclier(SOINS, C, this, window);
		}
		ajouterMana(1);
		break;
	case 2:
		Affichage().dessinerTexte(nom() + "se prepare ",window);
		ajouterCoupCritique(1);
		ajouterDegatsCritique(5);
		ajouterMana(1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " ASURA STRIKE ! ",window);
		DEGATS = degats((double)point_mana/3.0, (double)point_mana/2.0) + degats(0.5, 1.0, CHOIXBOUCLIER);
		reduireBouclier(bouclierMax());
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		ajouterMana(-point_mana);
		break;
	}
}

void Amine::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int DEGATS;
	double ratio = equipeEnnemi().plusProcheVivant()->pourcentageReduction() / 50.0;
	
	if ((tour + 1) % 8 == 0) {
		Affichage().dessinerTexte(nom() + " fist du dragon ! ",window);
		DEGATS = degats(ratio, ratio * 3.0 +0.1);
		if (DEGATS <= 0) {
			DEGATS = 1;
		}
		AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),C,window);
	}
}

void Amine::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	bouclier(niveau(), C, this, window);
}
