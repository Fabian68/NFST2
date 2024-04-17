#include "Isidore.h"
#include "Affichage.h"

Isidore::Isidore(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(7, E, O, A, Obj, "Isidore", 1, 1, 8, 8, 8, 8, 8, 8, 8, 8) {
	if (!_texture.loadFromFile("graphics/isidore.png"))
	{
		// error...
	}
	_sprite.setTexture(_texture);
}


void Isidore::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	ajouterVieMax(niveau());
	int cible;
	switch (choix) {

	case 0:
		
		Affichage().dessinerTexte(nom() + "dit bonjour",window);
		DEGATS = degats(0.001, 0.01);
		cible = equipeEnnemi().aleatoireEnVie()->indiceEquipe();
		Attaque(DEGATS, equipeEnnemi().perso(cible), C, window, allSounds);

		if (habile() && equipeEnnemi().perso(cible)->estEnVie()) {


			Affichage().dessinerTexte(nom() + "saute sur " + equipeEnnemi().perso(cible)->nom(),window);
			DEGATS = degats(0.5, 1.5);
		
			Attaque(DEGATS, equipeEnnemi().perso(cible), C, window, allSounds);
			ajouterMana(1);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " ganbade",window);
		for (double i = 0; i < 1.0; i += 0.01) {
			if (habile()) {
				SOINS = soins(i / 10.0, i / 10.0 + 0.01);
				soigner(SOINS, C, this, window);
			
				ajouterVieMax(vieMax()/1000);
			}
		}
		ajouterMana(1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + "embete les ennemis ",window);
		for (int i = 0; i < equipeEnnemi().taille(); i++) {

			equipeEnnemi()[i]->ajouterReduction(-2);

		}
		ajouterMana(-2);
		break;
	case 3:
		cible = equipeEnnemi().aleatoireEnVie()->indiceEquipe();
		Affichage().dessinerTexte(nom() + " encule " + equipeEnnemi().perso(cible)->nom(),window);
		DEGATS = degats(1.0, 2.0)+degats(0.5,1.0,CHOIXVITESSE);
		Attaque(DEGATS, equipeEnnemi().perso(cible), C, window, allSounds);
		ajouterMana(-3);
		break;
	}
}

void Isidore::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	ajouterVieMax(niveau()/10);
	if ((tour + 1) % 5 == 0) {
		if (habile() && attaqueDouble()) {
			ajouterForce(niveau() / 10);
			ajouterVieMax(niveau()*10);
		}
		else {
			ajouterForce(niveau() / 10);
			ajouterVieMax(niveau());
		}
		Affichage().dessinerTexte(nom() + "grandit ! ",window);
		
	}
	if ((tour + 1) % 30 == 0) {
		Affichage().dessinerTexte(nom() + "se repose ! ",window);
		soigner((int)vieMax(), C, this, window);
		bouclier(bouclierMax(), C, this, window);
	}
	
}

void Isidore::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
