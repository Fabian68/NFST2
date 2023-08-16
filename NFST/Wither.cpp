#include "Wither.h"
#include "Affichage.h"

Wither::Wither(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal, int id): Personnage(LVL, nom, 30, 4, 4, 33, 33, 33, 0, 0, 0, 12, animal, rareteAnimal)
{
	setId(id);
	ajouterVie(9 * vie());
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
		ajouterReduction(60);
	}
}

void Wither::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;

	Affichage().dessinerTexte(nom() + " attaque  ! ",window);
	for (int i = 0; i < equipeEnnemi().taille()&&equipeEnnemi().estEnVie(); i++) {
		if (vie() < vieMax() / 2) {
			DEGATS = degats(3.0, 6.0);
		}
		else {
			DEGATS = degats(1.0, 2.0);
		}
		Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
	}
	if (attaqueDouble() && equipeEnnemi().estEnVie()) {
		for (int i = 0; i < equipeEnnemi().taille() && equipeEnnemi().estEnVie(); i++) {
			if (vie() < vieMax() / 2) {
				DEGATS = degats(3.0, 6.0);
			}
			else {
				DEGATS = degats(1.0, 2.0);
			}
			Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
		}
	}
	ajouterMana(1);
}

void Wither::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int SOINS;
	if (vie() < vieMax() / 4) {
		SOINS = soins(0.1, 0.4);
		soigner(SOINS, C, this, window);

		SOINS = soins(0.4, 1.6);
		bouclier(SOINS, C, this, window);
	}
}

void Wither::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	int SOINS = soins(0.01, 0.1);
	soigner(SOINS, C, this, window);
	bouclier(SOINS, C, this, window);
}
