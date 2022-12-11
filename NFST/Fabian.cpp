#include "Fabian.h"
#include "Affichage.h"
#include <iostream>


Fabian::Fabian(Experiences E,Orbes O,Animaux A, Objets Obj): Personnage(0, E,O,A,Obj,"Fabian",2,4,4,17,17,-70,7,10,10,17){
	int diviseur = 10;

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
	if (!buffer.loadFromFile("vine-boom.ogg")) {

	}
	else {
		sound.setBuffer(buffer);
		//sound.play();
	}
}

void Fabian::attaqueEnnemis(sf::RenderWindow* window)
{
	
	int choix = choixAttaque();
	int DEGATS;
	//sf::SoundBuffer buffer;
	switch (choix) {

	case 0:
		Affichage().dessinerTexte(nom() + " coup de pieds",window);
		DEGATS = degats(0.2, 0.4);
		DEGATS += degats(0.3, 0.6, CHOIXVITESSE);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
	
		ajouterMana(1);
	
		/*
		if (!buffer.loadFromFile("dry-fart.ogg")) {

		}
		else {
			sf::Sound sound;
			sound.setBuffer(buffer);
			sound.play();
		}
		*/	
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " multicoup",window);
		DEGATS = degats(0.77, 1.17);
		for (int i = 0; i <= (5+vitesse()/niveau()) && equipeEnnemi().estEnVie(); i++) {
			sound.play();
			DEGATS = degats(0.017 + i * 0.017, 0.17 + i * 0.034);
			Attaque(DEGATS, equipeEnnemi().plusFort(),window);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				sound.play();
				DEGATS = degats(0.17 + i * 0.017, 0.17 + i * 0.07);
				Attaque(DEGATS, equipeEnnemi().plusFort(),window);
			}
			if (habile() && equipeEnnemi().estEnVie()) {
				sound.play();
				DEGATS = degats(0.017 + i * 0.017, 0.07 + i * 0.07);
				AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			}
		}
	
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " boost",window);
		ajouterCoupCritique(5);
		ajouterDegatsCritique(17);
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " soins ",window);
		if (vie() == vieMax() && bouclier() == bouclierMax()) {
			attaqueEnnemis(window);
		}
		else {
			soigner((int)vieMax(), this,window);
			bouclier(bouclierMax(), this, window);
			ajouterMana(-3);
		}
		break;
	}
}

void Fabian::passif(int tour, sf::RenderWindow* window)
{
	if (((tour+1) % 7) == 0) {
	
		
		ajouterReduction(17);
		Affichage().dessinerTexte(this->nom() + " devient plus resistant grace au froid de sa chambre ! ",window);
	}
	if (((tour + 1) % 17) == 0) {
		ajouterForce((int)((double)force() * 0.07));
		Affichage().dessinerTexte(this->nom() + " a fait de la muscu attention ! ",window);
	}
}

void Fabian::passifDefensif(sf::RenderWindow* window)
{
	status().setReducteur(status().reducteur() + 1);
}
