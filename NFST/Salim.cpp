#include "Salim.h"
#include "Affichage.h"
#include "Aleatoire.h"

Salim::Salim(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(15, E, O, A, Obj, "Salim", 6, 1, 1, 0, 25, -20, 0, 0, 0, 3), estTransformer{ false }, superTransformation{ false } {

	if (!_texture.loadFromFile("graphics/salim.png"))
	{
		// error...
	}
	_sprite.setTexture(_texture);
}


void Salim::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	int nb;
	
	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " racine poignard ",window);
		DEGATS = (int)(Aleatoire(0.01, 0.02).decimal() * (double)vieMax() + degats(0.1, 0.2));
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (habile()&&equipeEnnemi().estEnVie()) {
			DEGATS = (int)(Aleatoire(0.005, 0.01).decimal() * (double)vieMax() + degats(0.05, 0.1));
			AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(), C,window);
			ajouterMana(1);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " SUPERSOIN ! ",window);
		nb = equipeAllier().nbEnVie();
		for (int i = 0;i < equipeAllier().taille();i++) {
			SOINS = soins(1.0 / nb, 4.0 / nb);
			soigner(SOINS, C, equipeAllier()[i], window);
			SOINS = soins(0.5 / nb, 2.0 / nb);
			bouclier(SOINS, C, equipeAllier()[i], window);
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " endormissement ",window);
		SOINS = soins(0.25, 0.75);
		bouclier(SOINS, C, this, window);
		SOINS = soins(0.5, 1.5);
		soigner(SOINS, C, this, window);
		ajouterReduction(5);
		ajouterMana(-2);
		break;
	case 3:
		if (!estTransformer && mana() > 5) {
			Affichage().dessinerTexte(nom() + " TRANSFORMATION ! ",window);
			reduireVieMax((vieMax() / 10) * 9);
			ajouterForce(force() * 2);
			setNom("GRAND SALIMALEKUM");
			estTransformer = true;
			ajouterReduction(10);
			ajouterMana(-5);
			if (!_texture.loadFromFile("graphics/salim2.png"))
			{
				// error...
			}
			_sprite.setTexture(_texture);
		}
		else if (!superTransformation && mana() > 9) {
			Affichage().dessinerTexte(nom() + "SUUUPPEEEERR TRANSFORMATION ! ",window);
			reduireVieMax((vieMax() / 10) * 9);
			ajouterForce(force() * 2);
			setNom("GRAND SALIMALEKUM DIEUX DES TERRES ET DES OCEANS");
			superTransformation = true;
			ajouterReduction(20);
			ajouterMana(-10);
			if (!_texture.loadFromFile("graphics/salim3.png"))
			{
				// error...
			}
			_sprite.setTexture(_texture);
		}
		else {
			Affichage().dessinerTexte(nom() + " rejuvenation ! ",window);
			ajouterVieMax(niveau()*10);
			SOINS = soins(0.2, 1.2);
			soigner(SOINS, C, this, window);
			SOINS = soins(0.1, 0.6);
			bouclier(SOINS, C, this, window);
			ajouterMana(-3);
		}
		
		break;
	}
}

void Salim::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int DEGATS;

	if (habile()) {
		ajouterVieMax(force() / 10);
		if (habile()) {
			ajouterVieMax(force()/10);
		}
	}
	ajouterVieMax(force() / 10);
	if ((tour + 1) % 100 == 0) {
		Affichage().dessinerTexte(nom() + " jugement dernier ! ",window);
		for (int i = 0;i < equipeEnnemi().taille();i++) {
			DEGATS = degats(1.11, 2.11);
			if (habile()) {
				AttaqueBrut(DEGATS, equipeEnnemi()[i],C,window);
			}
			else {
				Attaque(DEGATS, equipeEnnemi()[i], C, window, allSounds);
			}
		}
	}
}

void Salim::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	if (habile()) {
		ajouterVieMax(force() / 10);
		if (habile()) {
			ajouterVieMax(force()/10);
		}
	}
	ajouterVieMax(force()/10);
}
