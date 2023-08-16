#include "Cloe.h"
#include "Affichage.h"

Cloe::Cloe(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(9, E, O, A, Obj, "Cloe", 1, 1, 4, 25, 25, -50, 0, 0, 20, 0) {}


void Cloe::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
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
			SOINS = soins(0.1, 0.3);
			bouclier(SOINS, C, equipeAllier()[i], window);
			if (attaqueDouble()) {
				SOINS = soins(0.1, 0.3);
				bouclier(SOINS, C, equipeAllier()[i], window);
			}	
		}
		
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " fais un calin ! ",window);
		cible = equipeAllier().aleatoireEnVie()->indiceEquipe();
		if (cible != this->indiceEquipe()) {
			if (!habile()) {
				equipeAllier().perso(cible)->ajouterForce(niveau() / 20);
				equipeAllier().perso(cible)->ajouterReduction(3);
				equipeAllier().perso(cible)->status().ajouterCompteurProteger(3);
			}
			else {
				equipeAllier().perso(cible)->ajouterForce(niveau() / 10);
				equipeAllier().perso(cible)->ajouterReduction(6);
				equipeAllier().perso(cible)->status().ajouterCompteurProteger(6);
			}
		}

		ajouterMana(1);
		break;
	case 2:
		Affichage().dessinerTexte(nom() + " soigne l'équipe ! ",window);
		for (int i = 0,j=1;i < equipeAllier().taille();i++,j*=2) {
			SOINS = soins(0.1 * j, 0.2 * j);
			soigner(SOINS, C, equipeAllier()[i], window);
		}
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + "balance de la KPOP ",window);
		DEGATS = degats(1.0, 2.0);
		equipeEnnemi().attaqueZone(DEGATS, this,C ,window, allSounds);
		ajouterMana(-3);
		break;
	}
}

void Cloe::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if ((tour + 1) % 5 == 0) {
		Affichage().dessinerTexte(nom() + " est fatiguer ",window);
		reduireVie(vie() /10);
		ajouterReduction(1);
	}
}

void Cloe::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	
}
