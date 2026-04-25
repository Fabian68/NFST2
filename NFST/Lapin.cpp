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
		ajouterReduction(80);
	}
	else if (difficulte == 3) {
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

		std::shared_ptr<sf::SoundBuffer> buffer0 = std::make_shared<sf::SoundBuffer>();
		buffer0->loadFromFile("./song/iniciowindows.ogg");
		_allBuffers.push_back(buffer0);
		_allSounds.push_back(sf::Sound(*buffer0));

		std::shared_ptr<sf::SoundBuffer> buffer1 = std::make_shared<sf::SoundBuffer>();
		buffer1->loadFromFile("./song/windowsxperror.ogg");
		_allBuffers.push_back(buffer1);
		_allSounds.push_back(sf::Sound(*buffer1));

		_allSounds[0].play();
	}
	else if (difficulte == 4) {
		ajouterVie(4*vie());
		ajouterReduction(30);
		if (!_texture.loadFromFile("graphics/risitas.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);

		std::shared_ptr<sf::SoundBuffer> buffer2 = std::make_shared<sf::SoundBuffer>();
		buffer2->loadFromFile("./song/issou0.ogg");
		_allBuffers.push_back(buffer2);

		std::shared_ptr<sf::SoundBuffer> buffer3 = std::make_shared<sf::SoundBuffer>();
		buffer3->loadFromFile("./song/issou1.ogg");
		_allBuffers.push_back(buffer3);

		std::shared_ptr<sf::SoundBuffer> buffer4 = std::make_shared<sf::SoundBuffer>();
		buffer4->loadFromFile("./song/issou2.ogg");
		_allBuffers.push_back(buffer4);
		_allSounds.push_back(sf::Sound(*buffer2));
		_allSounds.push_back(sf::Sound(*buffer3));
		_allSounds.push_back(sf::Sound(*buffer4));
		_allSounds[0].play();
	}
	else if (difficulte == 5) {
		ajouterVie(vie());
		ajouterReduction(80);
	}
	else if (difficulte == 6) {
		ajouterVie(9*vie());
		ajouterVitesse(4 * vitesse());
		if (!_texture.loadFromFile("graphics/nyancat.gif"))
		{
			// error...
		}
		_sprite.setTexture(_texture);

		std::shared_ptr<sf::SoundBuffer> buffer0 = std::make_shared<sf::SoundBuffer>();
		buffer0->loadFromFile("./song/nyancat.ogg");
		_allBuffers.push_back(buffer0);
		_allSounds.push_back(sf::Sound(*buffer0));
		_allSounds[0].play();
	}
	else if (difficulte == 10) {
		ajouterVie(vie());
		ajouterVitesse(vitesse() * 2);
		if (!_texture.loadFromFile("graphics/Ballerina-Capuchina.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	if (id == 21) {
		if (!_texture.loadFromFile("graphics/Perle.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	_difficulte = difficulte;
}
void Lapin::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) {
	int choix = choixAttaque();
	int DEGATS;

	if (_difficulte == 3) {
		_allSounds[1].play();
	}
	if (_difficulte == 4) {
		_allSounds[0].play();
	}
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
		if (_difficulte == 4) {
			_allSounds[1].play();
		}
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
		if (_difficulte == 4) {
			_allSounds[1].play();
		}
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
	if (_difficulte == 4) {
		_allSounds[2].play();
	}
}
