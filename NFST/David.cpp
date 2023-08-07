#include "David.h"
#include "Aleatoire.h"
#include "Affichage.h"

David::David(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(6, E, O, A, Obj, "David", 2, 2, 6, 0, 30, 0, 3, 0, 0, 3) {}


void David::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	double ratio = (vitesse() * 1.0) / (force() * 1.0);

	switch (choix) {

	case 0:
		
		DEGATS = degats(0.4, 0.8);
		Affichage().dessinerTexte(nom() + " joue du diabolo ",window);
		for (int i = 0;i < 7 && equipeEnnemi().estEnVie();i++) {
			if (habile()) {
				DEGATS = degats(0.2, 1.25, CHOIXVITESSE); 
				Attaque(DEGATS, equipeEnnemi().plusFaible(),window,allSounds);	
				ajouterMana(1);
			}		
		}
		
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " joue de la guitare ",window);

		if (!habile()) {
			for (int i = 0;i < equipeEnnemi().taille();i++) {
				DEGATS = degats(ratio / 4.0, ratio / 2.0);
				Attaque(DEGATS, equipeEnnemi()[i],window,allSounds);
			}
		}
		else {
			for (int i = 0;i < equipeAllier().taille();i++) {
				SOINS = soins(ratio / 4.0, ratio / 2.0);
				soigner(SOINS, equipeAllier()[i],window);

				SOINS = soins(ratio / 5.0, ratio / 2.5);
				bouclier(SOINS, equipeAllier()[i],window);
			}
		}
		ajouterMana(+1);
		break;
	case 2:
		passif(0,window,allSounds);
		ajouterMana(1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " roule sur les ennemis ",window);
		double j = 0.02;
		for (int i = 0;i < equipeEnnemi().taille();i++) {
			if (equipeEnnemi()[i]->estEnVie()) {
				DEGATS = static_cast<int>(Aleatoire(j, j * 2).decimal() * (vitesse()*1.0));
				Attaque(DEGATS+vitesse()/5, equipeEnnemi()[i],window,allSounds);	
				if (habile()) {
					DEGATS = static_cast<int>(Aleatoire(j, j * 2).decimal() * (vitesse() * 1.0));
					AttaqueBrut(DEGATS+vitesse()/10, equipeEnnemi()[i],window);
				}
				j *= 2;
			}
		}
		ajouterMana(-3);
		break;
	}
}

void David::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (vie() == vieMax()) {
		Affichage().dessinerTexte(nom() + " jette une despe sur un ennemi ",window);
		int DEGATS = degats(0.4, 0.8) + degats(0.8, 1.6, CHOIXVITESSE) + degats(0.1, 0.2, CHOIXBOUCLIER);
		if (equipeEnnemi().estEnVie()) {
			Attaque(DEGATS, equipeEnnemi().plusFort(),window,allSounds);
		}
		reduireBouclier(bouclier());
	}
	else {
		Affichage().dessinerTexte(nom() + " s'enfile une desperado ",window);
		int SOINS = static_cast<int>(0.059 * vieMax());
		soigner(SOINS, this,window);
	}
	
}

void David::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
}
