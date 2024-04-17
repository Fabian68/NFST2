#include "Sanglier.h"
#include "Affichage.h"
#include "Aleatoire.h"

Sanglier::Sanglier(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal,int id) : Personnage(LVL, nom, 4, 4, 2, 0, 30, 30, 3, 30, 0, 0, animal, rareteAnimal)
{
	setId(id);
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
		if (!_texture.loadFromFile("graphics/sanglier_boss.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}else if (difficulte == 2) {
		ajouterForce(force()*2);
		ajouterVie(19 * vie());
		if (!_texture.loadFromFile("graphics/sanglier_d2.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else {
		if (!_texture.loadFromFile("graphics/sanglier.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
		status().setReducteur(niveau() * 2);
	}
	if (id == 22) {
		if (!_texture.loadFromFile("graphics/Oxanne.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}

	
}




void Sanglier::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;

	switch (choix) {

	case 0:
		DEGATS = degats(0.9, 1.3);
		Affichage().dessinerTexte(nom() + " charge ",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);

		ajouterMana(1);
		break;
	case 1:

		SOINS = soins(0.5, 0.75);
		Affichage().dessinerTexte(nom() + " se repose !  ",window);
	    status().ajouterCompteurProteger(10);
		if (vie() == vieMax()) {
			bouclier(SOINS, C, this, window);
		}
		else {
			soigner(SOINS, C, this, window);
		}
		
		
		ajouterMana(1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " se gonfle !  ",window);

		ajouterChanceHabileter(3);
		equipeEnnemi().plusProcheVivant()->status().ajouterCompteurFragile(3);
		ajouterForce(force() / 5);
		ajouterMana(1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " charge dans tout les sens ! ",window);
		for (int i = 1,j=1; i <= 5 && equipeEnnemi().estEnVie(); i++,j*=2) {
			DEGATS = degats(j/10.0, j/5.0);
			Attaque(DEGATS, equipeEnnemi().aleatoireEnVie(), C, window, allSounds);
		}
		ajouterMana(-3);
		break;
	}
}

void Sanglier::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int SOINS;
	if ((tour + 1) % 5 == 0) {
		SOINS = soins(0.10, 0.25);
		bouclier(SOINS, C, this,window);
	}
	if ((tour + 1) % 10 == 0) {
		SOINS = soins(0.25, 0.50);
		soigner(SOINS, C, this, window);
	}
}

void Sanglier::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	int SOINS;
	if (Aleatoire(0, 101).entier() <= 10) {
		SOINS = soins(0.05, 0.10);
		bouclier(SOINS, C, this,window);
	}
	if (Aleatoire(0, 101).entier() <= 10) {
		SOINS = soins(0.08, 0.24);
		soigner(SOINS, C, this, window);
	}
}
