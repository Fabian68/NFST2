#include "Creeper.h"
#include "Affichage.h"
#include "Aleatoire.h"
Creeper::Creeper(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 2, 4, 4, 0, 50, 50, 0, 0, 0, 0, animal, rareteAnimal)
{
	ajouterVie(2 * vie());
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
	if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(19 * vie());
		ajouterReduction(99);
	}
	status().setReducteur(niveau() * 2);
}


void Creeper::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;


	int tirage;

	Affichage().dessinerTexte(nom() + " explose ! ",window);
	for (int i = 0; i < equipeEnnemi().taille() && equipeEnnemi().estEnVie(); i++) {
		tirage = Aleatoire(0, 101).entier();
		if (tirage < 30) {

		}
		else {
			if (tirage >= 30 && tirage < 50) {
				DEGATS = degats(0.0, 2.5);
			}
			else if (tirage >= 50 && tirage < 70) {
				DEGATS = degats(2.5, 5.0);
			}
			else if (tirage >= 70 && tirage < 90) {
				DEGATS = degats(5.0, 10.0);
			}
			else if (tirage >= 90 && tirage < 97) {
				DEGATS = degats(7.5, 15.0);
			}
			else {
				DEGATS = degats(10.0, 20.0);
			}
			Attaque(DEGATS, equipeEnnemi()[i], window);
		}
	}
	Attaque(degats(0.0, 20.0), this,window);
	ajouterMana(1);
}

void Creeper::passif(int tour, sf::RenderWindow* window)
{
}

void Creeper::passifDefensif(sf::RenderWindow* window)
{
	
}
