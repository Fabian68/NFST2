#include "Brute.h"
#include "Affichage.h"

Brute::Brute(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 2, 6, 2, 10, 50, 25, 0, 0, 0, 0, animal, rareteAnimal)
{
	ajouterForce(force());
	if (difficulte == 1) {
		ajouterVitesse(vitesse());
		ajouterVie(9 * (long long int)vie());
	}
	else if (difficulte == 5) {
		ajouterVie(vie());
		ajouterReduction(90);
	}
	status().devientEnmagasineur();
	status().setAdducteur(niveau());
	enrager = false;
}


void Brute::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;

	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " Lance Grenade",window);
		DEGATS = degats(0.4, 0.8);
		if (enrager) {
			DEGATS *= 2;
		}
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(0.4, 0.8);
			if (enrager) {
				DEGATS *= 2;
			}
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " coup rasoir ",window);
		DEGATS = degats(0.5, 1.5);
		if (enrager) {
			DEGATS *= 2;
		}
		Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(0.5, 1.5);
			if (enrager) {
				DEGATS *= 2;
			}
			Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " coup enrager ",window);
		DEGATS = degats(0.5, 1.0);
		DEGATS += status().enmagasination();
		status().retirerEmagasination(status().enmagasination());
		AttaqueBrut(DEGATS, equipeEnnemi().plusFort(),C,window);
		ajouterMana(-2);
		break;
	case 3:

		Affichage().dessinerTexte(nom() + " Coup de marteau ",window);
		DEGATS = degats(2.0, 4.0);
		if (enrager) {
			DEGATS *= 2;
		}
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		ajouterMana(-3);
		break;
	}
}

void Brute::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (vie() < (vieMax() / 5)) {
		enrager = true;
	}
	else {
		enrager = false;
	}
}

void Brute::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
