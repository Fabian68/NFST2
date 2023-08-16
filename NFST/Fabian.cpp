#include "Fabian.h"
#include "Affichage.h"
#include <iostream>
#include "Aleatoire.h"


Fabian::Fabian(Experiences E,Orbes O,Animaux A, Objets Obj): Personnage(0, E,O,A,Obj,"Fabian",2,2,2,7,7,-70,7,7,7,7){
	int diviseur = 7;

	if (niveau() > 999) {
		diviseur = 2;
	}
	else if (niveau() > 99) {
		diviseur = 3;
	}
	else if (niveau() > 9) {
		diviseur = 5;
	}
	status().setAdducteur(force() / diviseur + niveau());
	status().setReducteur(niveau());

	if (Aleatoire(0, 1000).entier() == 1) {
		setNom("Mister Bean");
	}
	else if (Aleatoire(0, 1000).entier() == 52) {
		setNom("Hibernatus");
	}
}

void Fabian::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	
	int choix = choixAttaque();
	int DEGATS;
	//sf::SoundBuffer buffer;
	switch (choix) {

	case 0:
		Affichage().dessinerTexte(nom() + " coup de pieds",window);
		DEGATS = degats(0.2, 0.4);
		DEGATS += degats(0.1, 0.3, CHOIXVITESSE);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
	
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " multicoup",window);
		DEGATS = degats(0.77, 1.17);
		for (int i = 0; i <= (3+vitesse()/niveau()) && equipeEnnemi().estEnVie(); i++) {
			allSounds[2].play();
			DEGATS = degats(0.017 + i * 0.017, 0.17 + i * 0.034);
			Attaque(DEGATS, equipeEnnemi().plusFort(), C, window, allSounds);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				allSounds[2].play();
				DEGATS = degats(0.17 + i * 0.017, 0.17 + i * 0.07);
				Attaque(DEGATS, equipeEnnemi().plusFort(), C, window, allSounds);
			}
			if (habile() && equipeEnnemi().estEnVie()) {
				allSounds[2].play();
				DEGATS = degats(0.017 + i * 0.017, 0.07 + i * 0.07);
				AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),C,window);
			}
		}
	
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " boost",window);
		ajouterCoupCritique(2);
		ajouterDegatsCritique(7);
		ajouterMana(-1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " soins ",window);
		if (vie() == vieMax() && bouclier() == bouclierMax()) {
			DEGATS = degats(0.5, 1.5);
			DEGATS += degats(0.75, 1.25, CHOIXVITESSE);
			Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
			ajouterMana(-2);
		}
		else {
			soigner((int)vieMax(), C, this, window);
			bouclier(bouclierMax(), C, this, window);
			ajouterMana(-3);
		}
		break;
	}
}

void Fabian::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (((tour+1) % 17) == 0) {
		ajouterReduction(7);
		Affichage().dessinerTexte(this->nom() + " devient plus resistant grace au froid de sa chambre ! ",window);
	}
	if (((tour + 1) % 70) == 0) {
		ajouterForce((int)((double)force() * 0.17));
		Affichage().dessinerTexte(this->nom() + " a fait de la muscu attention ! ",window);
	}
}

void Fabian::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	status().setReducteur(status().reducteur() + 1);
}
