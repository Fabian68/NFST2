#include "Ghast.h"
#include "Affichage.h"

Ghast::Ghast(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal, int id) : Personnage(LVL, nom, 1, 6, 3, 0, 60, 10, 0, 0, 30, 0, animal, rareteAnimal)
{
	setId(id);
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
}

void Ghast::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;


	Affichage().dessinerTexte(nom() + " boule de feu ! ",window);
	for (int i = 0; i < equipeEnnemi().taille()&&equipeEnnemi().estEnVie(); i++) {
		DEGATS = degats(0.8, 1.6);
		Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
		equipeEnnemi()[i]->status().appliquerBrulure();
		if (habile() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.4, 0.8);
			Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
		}
		if (habile() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.3, 0.7);
			Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
		}
		if (habile() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.2, 0.6);
			Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
		}
	}
	ajouterMana(1);
}

void Ghast::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
}

void Ghast::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
