#include "Thomas.h"
#include "Affichage.h"
#include "Aleatoire.h"
Thomas::Thomas(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(2, E, O, A,Obj, "Thomas", 6, 3, 1, 0, 10, 80, 3, 8, 0, 3)
{
}

void Thomas::attaqueEnnemis(sf::RenderWindow* window)
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
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
		if (chanceHabileter() > Aleatoire(0, 101).entier()) {
			Affichage().dessinerTexte(nom() + " pete un gros coups, ca asphyxie tout le monde ! ",window);
			for (int i = 0; i < equipeEnnemi().taille() ; i++) {
				DEGATS = (int)(Aleatoire(0.01, 0.05).decimal() * ((double)vie() + (double)bouclier()));
				Attaque(DEGATS, equipeEnnemi()[i],window);
			}
			ajouterMana(1);
		}
	
		ajouterMana(1);
		break;
	case 1:

		Affichage().dessinerTexte(nom() + " saut dans le tas !  ",window);
		for (int i = 0; i <= equipeEnnemi().taille() / 2; i++) {
			DEGATS = degats(0.10+i*0.10, 0.20+i*0.20);
			Attaque(DEGATS, equipeEnnemi()[i],window);
			equipeEnnemi()[i]->status().ajouterCompteurFragile(1);

			DEGATS = degats(0.10 + i * 0.10, 0.20 + i * 0.20);
			indice = abs(equipeEnnemi().taille() - 1 - i);
			equipeEnnemi()[i]->status().ajouterCompteurFragile(1);

			Attaque(DEGATS, equipeEnnemi()[indice],window);
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " ramene de la bouffe !  ",window);
		for (int i = 0 ; i < equipeAllier().taille(); i++) {
			SOINS = soins(0.08, 0.32);
			soigner(SOINS, equipeAllier()[i],window);
		}
		ajouterMana(1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " J'ai bian manger j'ai bien bu ! ",window);
		DEGATS = (int)(0.10 * (double)vie() + 0.02 * (double)vieMax() + 0.2 * (double)bouclier()+0.30*(double)force());
		Attaque(DEGATS, equipeEnnemi().plusFort(),window);
		ajouterMana(-3);
		break;
	}
}

void Thomas::passif(int tour, sf::RenderWindow* window)
{
	int SOINS;
	if ((tour + 1) % 5 == 0) {
		SOINS = soins(0.30, 0.60);
		soigner(SOINS, this,window);
	}
}

void Thomas::passifDefensif(sf::RenderWindow* window)
{
	if (Aleatoire(0, 101).entier() <= chanceHabileter()) {
		AjouterBouclier((int)((double)vie()*0.04),window);
		equipeAllier().moinsResistant()->ajouterReduction(1);
		equipeAllier().moinsResistant()->status().ajouterCompteurProteger(1);
	}
}
