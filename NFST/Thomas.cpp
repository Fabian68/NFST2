#include "Thomas.h"
#include "Affichage.h"
#include "Aleatoire.h"
Thomas::Thomas(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(2, E, O, A,Obj, "Thomas", 6, 3, 1, 0, 10, 50, 3, 5, 0, 3)
{
	if (!_texture.loadFromFile("graphics/thomas.png"))
	{
		// error...
	}
	_sprite.setTexture(_texture);
}

void Thomas::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	int indice;
	switch (choix) {

	case 0:
		DEGATS = degats(0.1, 0.30);
		DEGATS += (int)(0.03 * (double)vie()+0.01 * (double)vieMax());
		Affichage().dessinerTexte(nom() + " coup de bide ! ",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (chanceHabileter() > Aleatoire(0, 101).entier()) {
			Affichage().dessinerTexte(nom() + " pete un gros coups, ca asphyxie tout le monde ! ",window);
			for (int i = 0; i < equipeEnnemi().taille() ; i++) {
				DEGATS = (int)(Aleatoire(0.01, 0.05).decimal() * ((double)vie() + (double)bouclier()));
				Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
			}
			ajouterMana(1);
		}
	
		ajouterMana(1);
		break;
	case 1:

		Affichage().dessinerTexte(nom() + " saut dans le tas !  ",window);
		for (int i = 0; i <= equipeEnnemi().taille() / 2; i++) {
			DEGATS = degats(0.10+i*0.10, 0.20+i*0.20);
			Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
			equipeEnnemi()[i]->status().ajouterCompteurFragile(1);

			DEGATS = degats(0.10 + i * 0.10, 0.20 + i * 0.20);
			indice = abs(equipeEnnemi().taille() - 1 - i);
			equipeEnnemi()[i]->status().ajouterCompteurFragile(1);

			Attaque(DEGATS, equipeEnnemi().perso(indice), C, window, allSounds);
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " ramene de la bouffe !  ",window);
		for (int i = 0 ; i < equipeAllier().taille(); i++) {
			SOINS = soins(0.08, 0.32);
			soigner(SOINS, C, equipeAllier()[i], window);
		}
		ajouterMana(1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " J'ai bian manger j'ai bien bu ! ",window);
		DEGATS = (int)(0.08 * (double)vie() + 0.02 * (double)vieMax() + 0.08 * (double)bouclier()+0.40*(double)force());
		Attaque(DEGATS, equipeEnnemi().plusFort(), C, window, allSounds);
		ajouterMana(-3);
		break;
	}
}

void Thomas::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int SOINS;
	if ((tour + 1) % 5 == 0) {
		SOINS = soins(0.30, 0.60);
		soigner(SOINS, C, this, window);
	}
}

void Thomas::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	if (Aleatoire(0, 101).entier() <= chanceHabileter()) {
		bouclier((int)((double)vie()*0.04), C, this,window);
		equipeAllier().moinsResistant()->status().ajouterCompteurProteger(1);
		equipeAllier().moinsResistant()->ajouterReduction(1);
	}
}
