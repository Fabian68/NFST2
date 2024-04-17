#include "Fiona.h"
#include "Affichage.h"
#include "Lapin.h"
#include "Sanglier.h"	
#include "AffichageCombat.h"

Fiona::Fiona(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(3, E, O, A, Obj, "Fiona", 3, 2, 1, 7, 7, 7, 7, 7, 7, 37) , _nbAnimaux{0} {

	if (!_texture.loadFromFile("graphics/fiona.png"))
	{
		// error...
	}
	_sprite.setTexture(_texture);
}

void Fiona::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	
	switch (choix) {

	case 0:
		equipeEnnemi().plusProcheVivant()->ajouterReduction(-1);
		DEGATS = degats(0.4, 0.8);
		Affichage().dessinerTexte(nom() + " tire oreille",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.25, 0.95);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " soins picher ",window);
		for (int i = 0; i < 7; i++) {
			while (ricoche()) {
				SOINS = soins(0.10, 0.25);
				soigner(SOINS, C, equipeAllier().aleatoireEnVie(), window);
			}
		}
		if (attaqueDouble() ) {
			for (int i = 0; i < 7; i++) {
				while (ricoche()) {
					SOINS = soins(0.05, 0.5);
					soigner(SOINS, C, equipeAllier().aleatoireEnVie(), window);
				}
			}
		}
		ajouterMana(1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " les 3 pichnettes ",window);
		for (int i = 1; i <= 3 && equipeEnnemi().estEnVie(); i++) {
			equipeEnnemi().plusProcheVivant()->ajouterReduction(-1);
			DEGATS = degats(0.2 * i , 0.3 *i);
			Attaque(DEGATS, equipeEnnemi().plusFort(), C, window, allSounds);
		}
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			for (int i = 1; i <= 3 && equipeEnnemi().estEnVie(); i++) {
				equipeEnnemi().plusProcheVivant()->ajouterReduction(-1);
				DEGATS = degats(0.3 * i, 0.4 * i);
				Attaque(DEGATS, equipeEnnemi().plusFort(), C, window, allSounds);
			}
		}
		ajouterMana(-2);
		break;
	case 3:

	
		DEGATS = degats(0.7, 1.7);
		equipeEnnemi().plusProcheVivant()->ajouterReduction(-7);

		Affichage().dessinerTexte(nom() + " pûissance 17 ",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		ajouterChanceHabileter(3);
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(1.17, 1.77);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(-3);
		break;
	}
}

void Fiona::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	std::string nom;
	int Degats;

	if (((tour + 1) % 17) == 0) {
		ajouterCoupCritique(7);
		if (habile()) {
			ajouterDegatsCritique(7);
		}
	}
	if (((tour + 1) % 70) == 0) {
		ajouterDegatsCritique(17);
		for (size_t i = 0; i < 17; i++)
		{
			Degats = degats(0.17, 0.18 + 0.017 * i);
			Attaque(Degats, equipeEnnemi().plusFort(), C, window, allSounds);
		}
	}
}

void Fiona::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{

}
