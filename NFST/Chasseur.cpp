#include "Chasseur.h"
#include "Affichage.h"

Chasseur::Chasseur(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 5, 4, 1, 0, 30, 90, 3, 60, 0, 3, animal, rareteAnimal)
{
	ajouterVie(vie());
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
	status().setAdducteur(niveau());
	if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(19 * vie());
		status().setReducteur(10 * niveau());
	}
}


void Chasseur::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	switch (choix) {

	case 0:
		ajouterMana(1);
		break;
	case 1:
		if (habile()) {
			Affichage().dessinerTexte(nom() + " coup charger ! ",window);
			DEGATS = degats(1.0, 4.0);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
		}
		ajouterMana(-1);
		break;
	case 2:
		Affichage().dessinerTexte(nom() + " coup coude ! ",window);
		DEGATS = degats(1.5, 2.5);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
		ajouterMana(-1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " coup charger precis ! ",window);
		if (habile()) {
			DEGATS = degats(4.0, 8.0);
			AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),window);
		}
		else {
			DEGATS = degats(3.0, 6.0);
			Attaque(DEGATS, equipeEnnemi().aleatoireEnVie(),window,allSounds);
		}
		
	
		ajouterMana(-3);
		break;
	}
}

void Chasseur::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
}

void Chasseur::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
}
