#include "Dragon.h"
#include "Affichage.h"

Dragon::Dragon(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal, int id) : Personnage(LVL, nom, 2, 4, 4, 10, 10, 10, 10, 10, 10, 10, animal, rareteAnimal)
{
	ajouterVie(4 * vie());
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(90 * vie());
	}
	if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(270 * vie());
	}
	status().setReducteur(niveau() * 2);
}

void Dragon::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;

	double mult = 1.0;
	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " morsure ",window);
		DEGATS = degats(1.0, 2.0);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(1.0, 2.0);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " lance flamme ! ",window);
		DEGATS = degats(6.0, 12.0);
		for (int i = 0;i < equipeEnnemi().taille();i++) {
			if (equipeEnnemi()[i]->estEnVie()) {
				Attaque(DEGATS*(int)mult, equipeEnnemi()[i], C, window, allSounds);
				equipeEnnemi()[i]->status().appliquerBrulure();
				DEGATS = (int)(DEGATS * (int)(1.0 - (double)equipeEnnemi()[i]->pourcentageReduction() / 100.0));
			}
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " Coup de queue ",window);
		DEGATS = degats(1.0, 2.0);
		for (int i = equipeEnnemi().taille()-1;i >=0;i--) {
			if (equipeEnnemi()[i]->estEnVie()) {
				Attaque(DEGATS * (int)mult, equipeEnnemi()[i], C, window, allSounds);
				DEGATS = (int)(DEGATS *(int)(1.2 + (double)equipeEnnemi()[i]->pourcentageReduction() / 100.0));
			}
		}
		ajouterMana(1);
		break;
	case 3:

		Affichage().dessinerTexte(nom() + " Croissance ",window);
		ajouterChanceDoubleAttaque(10);
		ajouterChanceHabileter(10);
		ajouterReduction(10);
		ajouterCoupCritique(10);
		ajouterDegatsCritique(10);
		ajouterMana(-3);
		break;
	}
}

void Dragon::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
}

void Dragon::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
