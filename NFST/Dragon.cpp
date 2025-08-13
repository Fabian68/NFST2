#include "Dragon.h"
#include "Affichage.h"

Dragon::Dragon(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal, int id) : Personnage(LVL, nom, 2, 4, 4, 10, 10, 10, 10, 10, 10, 10, animal, rareteAnimal)
{
	ajouterVie(4 * vie());
	std::shared_ptr<sf::SoundBuffer> buffer0 = std::make_shared<sf::SoundBuffer>();
	buffer0->loadFromFile("./song/yugioh.ogg");
	_allBuffers.push_back(buffer0);

	_allSounds.push_back(sf::Sound(*buffer0));
	_allSounds[0].setLoop(true);
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(90 * vie());
	}
	else if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(270 * vie());
	}
	else if (difficulte == 3) {
		ajouterForce(force()/2);
		ajouterVitesse(vitesse()/2);
		ajouterVie(9 * vie());
		if (!_texture.loadFromFile("graphics/DEDD.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 4) {
		ajouterForce(force() );
		ajouterVie(14 * vie());
		if (!_texture.loadFromFile("graphics/DRAGON_BLANC.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
		_allSounds[0].play();
	}
	else if (difficulte == 5) {
		ajouterVitesse(vitesse());
		ajouterVie(14 * vie());
		if (!_texture.loadFromFile("graphics/PUGM.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 6) {
		ajouterVie(19 * vie());
		ajouterForce(force());
		ajouterVitesse(vitesse());
		if (!_texture.loadFromFile("graphics/MBD.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 7) {
		ajouterVie(4 * vie());
		ajouterForce(force()/3);
		ajouterVitesse(vitesse()/3);
		if (!_texture.loadFromFile("graphics/REBD.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	status().setReducteur(niveau());
}

void Dragon::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;

	double mult = 1.0;
	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " morsure ",window);
		DEGATS = degats(1.0, 2.0);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(1.0, 2.0);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " lance flamme ! ",window);
		DEGATS = degats(1.0, 2.0);
		for (int i = 0;i < equipeEnnemi().taille();i++) {
			if (equipeEnnemi()[i]->estEnVie()) {
				Attaque(DEGATS*(int)mult, equipeEnnemi()[i], C, window, allSounds);
				equipeEnnemi()[i]->status().appliquerBrulure();
				DEGATS = (int)(DEGATS * (int)(1.0 - (double)equipeEnnemi()[i]->pourcentageReduction() / 100.0));
			}
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " Coup de queue ",window);
		DEGATS = degats(1.0, 2.0);
		for (int i = equipeEnnemi().taille()-1;i >=0;i--) {
			if (equipeEnnemi()[i]->estEnVie()) {
				Attaque(DEGATS * (int)mult, equipeEnnemi()[i], C, window, allSounds);
				DEGATS = (int)(DEGATS *(int)(1.2 + (double)equipeEnnemi()[i]->pourcentageReduction() / 100.0));
			}
		}
		ajouterMana(1);
		break;
	case 3:

		Affichage().dessinerTexte(nom() + " Croissance ",window);
		ajouterChanceDoubleAttaque(3);
		ajouterChanceHabileter(3);
		ajouterReduction(3);
		ajouterCoupCritique(3);
		ajouterDegatsCritique(9);
		ajouterMana(-3);
		break;
	}
}

void Dragon::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
}

void Dragon::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
