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

void Ghast::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;


	Affichage().dessinerTexte(nom() + " boule de feu ! ",window);
	for (int i = 0; i < equipeEnnemi().taille()&&equipeEnnemi().estEnVie(); i++) {
		DEGATS = degats(0.8, 1.6);
		Attaque(DEGATS, equipeEnnemi()[i],window);
		equipeEnnemi()[i]->status().appliquerBrulure();
		if (habile() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.4, 0.8);
			Attaque(DEGATS, equipeEnnemi()[i],window);
		}
		if (habile() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.3, 0.7);
			Attaque(DEGATS, equipeEnnemi()[i],window);
		}
		if (habile() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.2, 0.6);
			Attaque(DEGATS, equipeEnnemi()[i],window);
		}
	}
	ajouterMana(1);
}

void Ghast::passif(int tour, sf::RenderWindow* window)
{
}

void Ghast::passifDefensif(sf::RenderWindow* window)
{
}
