#include "Lapin.h"
#include "Affichage.h"
#include "Objets.h"


Lapin::Lapin(int LVL,std::string nom,int difficulte,int animal,int rareteAnimal,int id) : Personnage(LVL, nom, 2, 4, 4, 30, 0, 0, 0, 0, 10, 0,animal,rareteAnimal) 
{
	setId(id);
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9*vie());
		if (!_texture.loadFromFile("graphics/lapin_boss.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 2) {
		if (!_texture.loadFromFile("graphics/lapin_d2.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
		ajouterVitesse(vitesse());
		ajouterVie(19 * vie());
		ajouterReduction(99);
	}
	if (difficulte == 3) {
		ajouterVitesse(vitesse()*3);
		ajouterVie(2 * vie());
		//Clippy
		Objets obj;
		setObjets(obj.objetNumero(OBJET_FLEAU_SADIQUE), obj.objetNumero(OBJET_CAPE_NINJA));
		if (!_texture.loadFromFile("graphics/clippy.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 5) {
		ajouterVie(vie());
		ajouterReduction(90);
	}

	if (id == 21) {
		if (!_texture.loadFromFile("graphics/Perle.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
}
void Lapin::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) {
	int choix = choixAttaque();
	int DEGATS;

	
	switch (choix) {

	case 0:
		DEGATS = degats(0.1, 0.3)+degats(0.0,0.5,CHOIXVITESSE);
		Affichage().dessinerTexte(nom() + " bondissage ",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);

		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			Affichage().dessinerTexte(nom() + " Coup de boule ",window);
			DEGATS = degats(0.4, 0.8);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			ajouterMana(1);
		}
		ajouterChanceDoubleAttaque(1);
		ajouterMana(1);
		break;
	case 1:
		
		DEGATS = degats(0.3, 1.2);
		Affichage().dessinerTexte(nom() + " griffures !  ",window);

		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(0.15, 0.6);
			Affichage().dessinerTexte(nom() + " saignement !  ",window);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(-1);
		break;
	case 2:

		DEGATS = degats(0.1, 0.5)+degats(0.2,0.6,CHOIXVITESSE);
		Affichage().dessinerTexte(nom() + " sautille !  ",window);

		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(1.15, 1.6);
			Affichage().dessinerTexte(nom() + " coup de boule !  ",window);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterChanceHabileter(5);
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + "s'enrage !",window);
		DEGATS = degats(1.3, 2.2);
		equipeEnnemi().plusProcheVivant()->status().appliquerPoison();
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		
		ajouterMana(-3);
		break;
	}
	
}

void Lapin::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if ((tour+1) % 3 == 0) {
		bouclier((int)((double)vitesse()/3.0), C, this,window);
	}
}

void Lapin::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
