#include "Grognard.h"
#include "Affichage.h"

Grognard::Grognard(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 1, 3, 6, 50, 0, 0, 0, 0, 10, 10, animal, rareteAnimal)
{	
	ajouterVitesse(vitesse());
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
	else if (difficulte == 5) {
		ajouterVie(vie());
		ajouterReduction(90);
	}
	if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(49 * vie());
		status().setReducteur(10 * niveau());
	}
}

void Grognard::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	
	double inc = 0.0;

	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " needler !",window);
		for (int i = 0;i < 10 && equipeEnnemi().estEnVie();i++) {
			DEGATS = degats(0.1, 0.2);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			inc += 0.1;
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				inc += 0.1;
				DEGATS = degats(0.1, 0.2);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);

			}
		}
		if (equipeEnnemi().estEnVie()) {
			Affichage().dessinerTexte(nom() + "Explosion",window);
			DEGATS = degats(0.2+inc, 0.4+inc*2);
			AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),C,window);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " sauver vous ! ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			equipeAllier()[i]->ajouterReduction(1);
			equipeAllier()[i]->status().ajouterCompteurProteger(1);
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " a l'aide ! ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			equipeAllier()[i]->ajouterReduction(1);
			equipeAllier()[i]->status().ajouterCompteurProteger(1);
		}
		ajouterMana(-1);
		break;
	case 3:

		Affichage().dessinerTexte(nom() + " SUICIDE ",window);
		DEGATS = degats(5.0, 10.0);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		Attaque(DEGATS, this, C, window, allSounds);
		ajouterMana(-3);
		break;
	}
}

void Grognard::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
}

void Grognard::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
