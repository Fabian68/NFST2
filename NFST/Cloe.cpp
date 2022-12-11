#include "Cloe.h"
#include "Affichage.h"

Cloe::Cloe(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(9, E, O, A, Obj, "Cloe", 1, 6, 3, 25, 25, -50, 0, 75, 0, 0) {}


void Cloe::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	double ratio = (vitesse() * 1.0) / (force() * 1.0);
	int cible;
	switch (choix) {

	case 0:

	
		Affichage().dessinerTexte(nom() + " viens jouer  ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			if (habile()) {
				SOINS = soins(0.1, 0.3);
				bouclier(SOINS, equipeAllier()[i],window);
				if (attaqueDouble()) {
					SOINS = soins(0.1, 0.3);
					bouclier(SOINS, equipeAllier()[i],window);
				}
			}
			if (attaqueDouble()) {
				SOINS = soins(0.1, 0.3);
				bouclier(SOINS, equipeAllier()[i],window);
				if (habile()) {
					SOINS = soins(0.1, 0.3);
					bouclier(SOINS, equipeAllier()[i],window);
				}
			}
		}
		if (attaqueDouble()) {
			for (int i = 0;i < equipeAllier().taille();i++) {
				if (habile()) {
					SOINS = soins(0.1, 0.3);
					bouclier(SOINS, equipeAllier()[i],window);
					if (attaqueDouble()) {
						SOINS = soins(0.1, 0.3);
						bouclier(SOINS, equipeAllier()[i],window);
					}
				}
				if (attaqueDouble()) {
					SOINS = soins(0.1, 0.3);
					bouclier(SOINS, equipeAllier()[i],window);
					if (habile()) {
						SOINS = soins(0.1, 0.3);
						bouclier(SOINS, equipeAllier()[i],window);
					}
				}
			}
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " fais un calin ! ",window);
		cible = equipeAllier().aleatoireEnVie()->indiceEquipe();
		if (cible != this->indiceEquipe()) {
			if (!habile()) {
				equipeAllier()[cible]->ajouterForce(niveau() / 20);
				equipeAllier()[cible]->ajouterReduction(3);
				equipeAllier()[cible]->status().ajouterCompteurProteger(3);
			}
			else {
				equipeAllier()[cible]->ajouterForce(niveau() / 10);
				equipeAllier()[cible]->ajouterReduction(6);
				equipeAllier()[cible]->status().ajouterCompteurProteger(6);
			}
		}

		ajouterMana(1);
		break;
	case 2:
		Affichage().dessinerTexte(nom() + " soigne l'équipe ! ",window);
		for (int i = 0,j=1;i < equipeAllier().taille();i++,j*=2) {
			SOINS = soins(0.2 * j, 0.4 * j);
			soigner(SOINS, equipeAllier()[i],window);
		}
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + "balance de la KPOP ",window);
		DEGATS = degats(1.0, 2.0);
		equipeEnnemi().attaqueZone(DEGATS, this,window);
		ajouterMana(-3);
		break;
	}
}

void Cloe::passif(int tour, sf::RenderWindow* window)
{
	if ((tour + 1) % 5 == 0) {
		Affichage().dessinerTexte(nom() + " est fatiguer ",window);
		reduireVie(vie() /20);
	}
}

void Cloe::passifDefensif(sf::RenderWindow* window)
{
	ajouterReduction(1);
	ajouterForce(force() / 10);
}
