#include "Rapace.h"
#include "Affichage.h"

Rapace::Rapace(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 1, 2, 7, 50, 0, 0, 0, 50, 50, 10, animal, rareteAnimal)
{
	ajouterForce(force());
	ajouterVitesse(vitesse());
	ajouterBouclier(bouclierMax());
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
}


void Rapace::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;

	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " Assaut",window);
		DEGATS = degats(0.6, 0.9);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(0.6, 0.9);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			ajouterMana(1);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + "roulade sur le coter ",window);
		ajouterForce(niveau() / 10);
		bouclier(vitesse(), C, this, window);
		
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + "SNIPE ",window);
		DEGATS = degats(1.0, 6.0);
		Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(1.0, 6.0);
			AttaqueBrut(DEGATS, equipeEnnemi().plusFaible(), C,window);
		}
		ajouterMana(-2);
		break;
	case 3:

		Affichage().dessinerTexte(nom() + " protege alliers ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			equipeAllier()[i]->ajouterReduction(5);
		}
		ajouterMana(-3);
		break;
	}
}

void Rapace::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if ((tour + 1) % 10 == 0) {
		bouclier(bouclierMax(), C, this, window);
	}
	status().ajouterCompteurProteger(1);
}

void Rapace::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
