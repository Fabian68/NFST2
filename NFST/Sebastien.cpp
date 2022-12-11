#include "Sebastien.h"
#include "Affichage.h"

Sebastien::Sebastien(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(8, E, O, A, Obj, "Sebastien", 1, 5, 5, 20, 0, 25, 0, 0, 0, 6), pause{ 0 } {}


void Sebastien::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;

	double inc = 0.0;
	double inc2 = 0.0;

	double mult = 1.0;
	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " attaque a la mitraillette",window);
		for (int i = 0;i < (vitesse()*10)/force()+1 && equipeEnnemi().estEnVie();i++, inc += 0.01,inc2+=0.02) {	
			DEGATS = degats(0.01+inc, 0.02 + inc2);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			if (attaqueDouble()&& equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.1, 0.2 + inc);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
				inc += 0.01;
				inc2 += 0.02;
			}
		}
		if (attaqueDouble()) {
			for (int i = 0;i < (vitesse() * 5) / force()+1 && equipeEnnemi().estEnVie();i++, inc += 0.01,inc+=0.02) {
				DEGATS = degats(0.01+inc, 0.02 + inc2);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
				if (attaqueDouble() && equipeEnnemi().estEnVie()) {
					DEGATS = degats(0.1, 0.2 + inc);
					Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
					inc += 0.01;
					inc2 += 0.02;
				}
			}
		}
		ajouterMana(3);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " cible un ennemi au gun ! ",window);
		DEGATS = degats(0.25, 0.75);
		Attaque(DEGATS, equipeEnnemi().plusFaible(),window);
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.5, 1.5);
			Attaque(DEGATS, equipeEnnemi().plusFaible(),window);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				DEGATS = degats(1.0, 3.0);
				Attaque(DEGATS, equipeEnnemi().plusFaible(),window);
			}
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " coup épée ",window);
		DEGATS = degats(2.0, 4.0);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(1.5, 3.0);
			Attaque(DEGATS, equipeEnnemi().plusFaible(),window);
			
		}
		ajouterMana(-2);
		break;
	case 3:
	
		Affichage().dessinerTexte(nom() + " BAZOOKA ",window);
		for (int i = 0, j = equipeEnnemi().taille() - 1;i < equipeEnnemi().taille()/2 && j>=0;i++, j--,mult*=2) {
			DEGATS = degats(0.2*mult, 0.4*mult);
			Attaque(DEGATS, equipeEnnemi()[i],window);

			DEGATS = degats(0.2 * mult, 0.4 * mult);
			Attaque(DEGATS, equipeEnnemi()[j],window);
		}
		ajouterMana(-3);
		break;
	}
}

void Sebastien::passif(int tour, sf::RenderWindow* window)
{
	
	if ((pause + 1) % 4 == 0) {
		bouclier(bouclierMax(), this,window);
	}
	pause++;
}

void Sebastien::passifDefensif(sf::RenderWindow* window)
{
	ajouterChanceDoubleAttaque(1);
	pause = 0;
}
