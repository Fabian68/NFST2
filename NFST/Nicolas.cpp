#include "Nicolas.h"
#include "Aleatoire.h"
#include "Affichage.h"


Nicolas::Nicolas(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(1, E, O, A, Obj, "Niquola", 3, 3, 3, 10, 0, 20, 0, 25, 0, 0) {

	status().devientEnmagasineur();
	_compteur_tour_joue = 0;

	if (Aleatoire(0, 1000).entier() == 1) {
		setNom("Nico Nico Ni");
	}
	else if (Aleatoire(0, 1000).entier() == 52) {
		setNom("Nicla");
	}
	if (!_texture.loadFromFile("graphics/nicolas.png"))
	{
		// error...
	}
	_sprite.setTexture(_texture);
 //ajouter Nicla
}


void Nicolas::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) {
	int choix = choixAttaque();
	int DEGATS;

	std::string a = nom();


	switch (choix) {

	case 0:
		DEGATS = degats(0.2, 0.6);
		Affichage().dessinerTexte(nom() + " Bras de fer ",window);
		if (this->force() > equipeEnnemi().plusProcheVivant()->force()) {
			DEGATS *= 2;
		}
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		ajouterMana(1);
		break;
	case 1:

		Affichage().dessinerTexte(nom() + " prie pour l'équipe ! ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			equipeAllier()[i]->ajouterReduction(1);
			if (habile()) {
				equipeAllier()[i]->ajouterReduction(1);
			}
			if (attaqueDouble()) {
				equipeAllier()[i]->ajouterReduction(1);
			}
		}
		
		
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " Relachement ! ",window);
		DEGATS = degats(0.20, 0.40) + status().enmagasination()*2;
		Attaque(DEGATS, equipeEnnemi().plusFort(), C, window, allSounds);

		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.40, 0.80) + status().enmagasination();
			Attaque(DEGATS, equipeEnnemi().plusFort(), C, window, allSounds);

		}
		status().retirerEmagasination(status().enmagasination());
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " partage Equipement Minecraft !",window);
		for (int i = 0; i < equipeAllier().taille(); i++) {
			if (equipeAllier()[i] != this && equipeAllier()[i]->estEnVie()) {
				equipeAllier()[i]->ajouterForce((equipeAllier()[i]->force() / 20));
			}
		}
		ajouterMana(-2);
		break;
	}
	_compteur_tour_joue += 1;
}

void Nicolas::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (status().estBruler()) {
		status().soignerBrulure();
	}
	if (tour % 5 == 0) {
		Affichage().dessinerTexte(nom() + " Priere ! ",window);
		status().ajoutEnmagasination((int)vieMax() / 50);
		bouclier((int)vieMax() / 10, C, this, window);
	}
}

void Nicolas::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degatss, Personnage* P)
{
	Affichage().dessinerTexte(nom() + " La transpiration fait des défats ! ", window);
	int DEGATS = vieMax() / 100 + (int)((double)vieMax() * ((double)_compteur_tour_joue / 1000.0));
	Attaque(DEGATS,P, C, window, allSounds);
}
