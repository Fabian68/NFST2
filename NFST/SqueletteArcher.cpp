#include "SqueletteArcher.h"
#include "Affichage.h"	

SqueletteArcher::SqueletteArcher(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal, int id) : Personnage(LVL, nom, 1, 4, 5, 30, 30, 30, 3, 30, 3, 3, animal, rareteAnimal)
{
	setId(id);
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
}



void SqueletteArcher::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;

	Affichage().dessinerTexte(nom() + " fleches ",window);
	for (int i = 1; i <= 3&& equipeEnnemi().estEnVie(); i++) {
		DEGATS = degats(0.3*i, 0.3*(i+1.0));
		Attaque(DEGATS, equipeEnnemi().plusFaible(),window,allSounds);
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.3 * i, 0.3 * (i + 1.0));
			Attaque(DEGATS, equipeEnnemi().plusFaible(),window,allSounds);
		}
	}
	if (attaqueDouble() && equipeEnnemi().estEnVie()) {
		for (int i = 1; i <= 3 && equipeEnnemi().estEnVie(); i++) {
			DEGATS = degats(0.3 * i, 0.3 * (i + 1.0));
			Attaque(DEGATS, equipeEnnemi().plusFaible(),window,allSounds);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.3 * i, 0.3 * (i + 1.0));
				Attaque(DEGATS, equipeEnnemi().plusFaible(),window,allSounds);
			}
		}
	}
	ajouterMana(1);
}

void SqueletteArcher::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
}

void SqueletteArcher::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
}
