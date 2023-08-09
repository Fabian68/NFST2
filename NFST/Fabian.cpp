#include "Fabian.h"
#include "Affichage.h"
#include <iostream>


Fabian::Fabian(Experiences E,Orbes O,Animaux A, Objets Obj): Personnage(0, E,O,A,Obj,"Fabian",2,2,2,17,17,-70,7,10,10,17){
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
}

void Fabian::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	
	int choix = choixAttaque();
	int DEGATS;
	//sf::SoundBuffer buffer;
	switch (choix) {

	case 0:
		Affichage().dessinerTexte(nom() + " coup de pieds",window);
		DEGATS = degats(0.2, 0.4);
		DEGATS += degats(0.1, 0.3, CHOIXVITESSE);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
	
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " multicoup",window);
		DEGATS = degats(0.77, 1.17);
		for (int i = 0; i <= (3+vitesse()/niveau()) && equipeEnnemi().estEnVie(); i++) {
			allSounds[2].play();
			DEGATS = degats(0.017 + i * 0.017, 0.17 + i * 0.034);
			Attaque(DEGATS, equipeEnnemi().plusFort(),window,allSounds);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				allSounds[2].play();
				DEGATS = degats(0.17 + i * 0.017, 0.17 + i * 0.07);
				Attaque(DEGATS, equipeEnnemi().plusFort(),window,allSounds);
			}
			if (habile() && equipeEnnemi().estEnVie()) {
				allSounds[2].play();
				DEGATS = degats(0.017 + i * 0.017, 0.07 + i * 0.07);
				AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),window);
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
			Attaque(DEGATS, equipeEnnemi().plusFaible(), window,allSounds);
			ajouterMana(-2);
		}
		else {
			soigner((int)vieMax(), this,window);
			bouclier(bouclierMax(), this, window);
			ajouterMana(-3);
		}
		break;
	}
}

void Fabian::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
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

void Fabian::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
	status().setReducteur(status().reducteur() + 1);
}
