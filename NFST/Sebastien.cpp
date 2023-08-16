#include "Sebastien.h"
#include "Affichage.h"
#include "Aleatoire.h"

Sebastien::Sebastien(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(8, E, O, A, Obj, "Sebastien", 2, 2, 2, 20, 0, 15, 0, 0, 0, 6), pause{ 0 } {


	if (Aleatoire(0, 1000).entier() == 1) {
		setNom("Seb la frite");
	}
}


void Sebastien::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;

	double inc = 0.0;
	double inc2 = 0.0;

	double mult = 1.0;
	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " attaque a la mitraillette",window);
		for (int i = 0;i < (vitesse()*5)/force()+1 && equipeEnnemi().estEnVie();i++, inc += 0.01,inc2+=0.02) {	
			DEGATS = degats(0.01+inc, 0.02 + inc2);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			if (attaqueDouble()&& equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.01, 0.02 + inc);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
				inc += 0.01;
				inc2 += 0.02;
			}
		}
		if (attaqueDouble()) {
			for (int i = 0;i < (vitesse() * 5) / force()+1 && equipeEnnemi().estEnVie();i++, inc += 0.01,inc+=0.02) {
				DEGATS = degats(0.01+inc, 0.02 + inc2);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
				if (attaqueDouble() && equipeEnnemi().estEnVie()) {
					DEGATS = degats(0.01, 0.02 + inc);
					Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
					inc += 0.01;
					inc2 += 0.02;
				}
			}
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " cible un ennemi au gun ! ",window);
		DEGATS = degats(0.25, 0.50);
		Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.50, 1.0);
			Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.75, 1.5);
				Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
			}
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " coup épée ",window);
		DEGATS = degats(1.5, 2.5);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		ajouterMana(-2);
		break;
	case 3:
	
		Affichage().dessinerTexte(nom() + " BAZOOKA ",window);
		for (int i = 0, j = equipeEnnemi().taille() - 1;i < equipeEnnemi().taille()/2 && j>=0;i++, j--,mult*=2) {
			DEGATS = degats(0.1*mult, 0.4*mult);
			Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);

			DEGATS = degats(0.1 * mult, 0.4 * mult);
			Attaque(DEGATS, equipeEnnemi().perso(j), C, window, allSounds);
		}
		ajouterMana(-3);
		break;
	}
}

void Sebastien::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	
	if ((pause + 1) % 4 == 0) {
		bouclier(bouclierMax(), C, this, window);
	}
	pause++;
}

void Sebastien::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	ajouterChanceDoubleAttaque(1);
	pause = 0;
}
