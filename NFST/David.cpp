#include "David.h"
#include "Aleatoire.h"
#include "Affichage.h"

David::David(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(6, E, O, A, Obj, "David", 1, 1, 6, 0, 30, 0, 3, 0, 0, 3) {}


void David::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	double ratio = (vitesse() * 1.0) / (force() * 1.0);

	switch (choix) {

	case 0:
		Affichage().dessinerTexte(nom() + " joue du diabolo ",window);
		for (int i = 0;i < 7 && equipeEnnemi().estEnVie();i++) {
			if (habile()) {
				DEGATS = degats(0.15, 0.35, CHOIXVITESSE); 
				Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
			}		
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " joue de la guitare ",window);

		if (!habile()) {
			for (int i = 0;i < equipeEnnemi().taille();i++) {
				DEGATS = degats(ratio / 14.0, ratio / 10.0);
				Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
			}
			ajouterMana(-1);
		}
		else {
			for (int i = 0;i < equipeAllier().taille();i++) {
				SOINS = soins(ratio / 16.0, ratio / 12.0);
				soigner(SOINS, C, equipeAllier()[i], window);

				SOINS = soins(ratio / 32.0, ratio / 24.0);
				bouclier(SOINS, C, equipeAllier()[i], window);
			}
			ajouterMana(1);
		}
		
		break;
	case 2:
		passif(0, C, window,allSounds);
		ajouterMana(1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " roule sur les ennemis ",window);
		double j = 0.01;
		for (int i = 0;i < equipeEnnemi().taille();i++) {
			if (equipeEnnemi()[i]->estEnVie()) {
				DEGATS = static_cast<int>(Aleatoire(j, j * 2).decimal() * (vitesse()*1.0));
				Attaque(DEGATS+vitesse()/5, equipeEnnemi()[i], C, window, allSounds);
				j *= 2;
			}
		}
		ajouterMana(-3);
		break;
	}
}

void David::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (vie() == vieMax()) {
		
		int SOINS = static_cast<int>(0.059 * vieMax());
		bouclier(SOINS, C, this, window);
	}
	else {
		Affichage().dessinerTexte(nom() + " s'enfile une desperado ",window);
		int SOINS = static_cast<int>(0.059 * vieMax());
		soigner(SOINS, C, this, window);
	}
	
}

void David::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
