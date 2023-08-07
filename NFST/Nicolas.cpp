#include "Nicolas.h"
#include "Aleatoire.h"
#include "Affichage.h"


Nicolas::Nicolas(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(1, E, O, A, Obj, "Niquola", 4, 3, 3, 10, 10, 50, 0, 50, 25, 0) {

	status().devientEnmagasineur();
 //ajouter Nicla
}


void Nicolas::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) {
	int choix = choixAttaque();
	int DEGATS;

	std::string a = nom();


	switch (choix) {

	case 0:
		DEGATS = degats(0.8, 1.2);
		Affichage().dessinerTexte(nom() + " Bras de fer ",window);
		if (this->force() > equipeEnnemi().plusProcheVivant()->force()) {
			DEGATS *= 2;
		}
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
		ajouterMana(1);
		break;
	case 1:

		Affichage().dessinerTexte(nom() + " prie pour l'équipe ! ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			equipeAllier()[i]->ajouterReduction(1);
			if (habile()) {
				equipeAllier()[i]->ajouterReduction(1);
				if (attaqueDouble()) {
					equipeAllier()[i]->ajouterReduction(1);
				}
			}
		}
		
		
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " Relachement ! ",window);
		DEGATS = degats(0.20, 0.40) + status().enmagasination()*2;
		Attaque(DEGATS, equipeEnnemi().plusFort(),window,allSounds);

		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.40, 0.80) + status().enmagasination();
			Attaque(DEGATS, equipeEnnemi().plusFort(),window,allSounds);

		}
		status().retirerEmagasination(status().enmagasination());
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " partage Equipement Minecraft !",window);
		for (int i = 0; i < equipeAllier().taille(); i++) {
			if (equipeAllier()[i] != this && equipeAllier()[i]->estEnVie()) {
				equipeAllier()[i]->ajouterForce((equipeAllier()[i]->force() / 5));
			}
		}
		ajouterMana(-2);
		break;
	}
}

void Nicolas::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (status().estBruler()) {
		status().soignerBrulure();
	}
	if (tour % 5 == 0) {
		Affichage().dessinerTexte(nom() + " Priere ! ",window);
		status().ajoutEnmagasination((int)vieMax() / 50);
		bouclier((int)vieMax() / 5,this,window);
	}
}

void Nicolas::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degatss, Personnage* P)
{
	if (Aleatoire(0, 101).entier() <= 10) {
		int Degats = degats(0.15, 0.30)+status().enmagasination()/10;
		Affichage().dessinerTexte(this->nom() + " VENDETTA ",window);
		Attaque(Degats, equipeEnnemi().plusProcheVivant(),window,allSounds);
	}
}
