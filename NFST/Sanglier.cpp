#include "Sanglier.h"
#include "Affichage.h"
#include "Aleatoire.h"
#include "Objets.h"
#include <iostream>

Sanglier::Sanglier(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal,int id) : Personnage(LVL, nom, 4, 4, 2, 0, 25, 25, 3, 25, 0, 0, animal, rareteAnimal)
{
	std::shared_ptr<sf::SoundBuffer> buffer0 = std::make_shared<sf::SoundBuffer>();
	
	setId(id);
	status().setReducteur(niveau());
	bool song_boucle = false;

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
	else if (difficulte == 3) {
		ajouterForce(force());
		ajouterVie(29 * vie());
		//Glonk
		Objets obj;
		setObjets(obj.objetNumero(OBJET_MALEDICTION), obj.objetNumero(OBJET_MALADRESSE));
		if (!_texture.loadFromFile("graphics/glonk.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 4) {
		ajouterVie(9 * vie());
		Objets obj;
		setObjets(obj.objetNumero(OBJET_MARHSMALLOW), obj.objetNumero(OBJET_CHAUSSETTES_FLO));
		if (!_texture.loadFromFile("graphics/schnappi.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
		buffer0->loadFromFile("./song/Schnappi.ogg");
		_allBuffers.push_back(buffer0);
		_allSounds.push_back(sf::Sound(*buffer0));
		song_boucle = true;
	}
	else if (difficulte == 5) {
		ajouterForce((int)(-force() * 0.99));
		ajouterVie(49 * vie());
		ajouterReduction(55);
		Objets obj;
		ajouterDeviation(-3);
		setObjets(obj.objetNumero(OBJET_BEUH), obj.objetNumero(OBJET_BEUH));
		setObjets2(obj.objetNumero(OBJET_BEUH), obj.objetNumero(OBJET_BEUH));
		if (!_texture.loadFromFile("graphics/toto_lescargot.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
		buffer0->loadFromFile("./song/Toto_lescargot.ogg");
		_allBuffers.push_back(buffer0);
		_allSounds.push_back(sf::Sound(*buffer0));
		song_boucle = true;
	}
	else if (difficulte == 6) {
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
		Objets obj;
		setObjets(obj.objetNumero(OBJET_PEAU_EPAISSE), obj.objetNumero(OBJET_ESPRIT_GUERRIER));
		if (!_texture.loadFromFile("graphics/pingu.png"))
		{
			// error...
		}
		buffer0->loadFromFile("./song/nootnoot.ogg");
		_allBuffers.push_back(buffer0);
		_allSounds.push_back(sf::Sound(*buffer0));
		_allSounds[0].play();
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 7) {
		ajouterForce((int)(-force()*0.9));
		ajouterVie(14 * vie());
		ajouterReduction(50);
		Objets obj;
		ajouterDeviation(-3);
		setObjets(obj.objetNumero(OBJET_BEUH), obj.objetNumero(OBJET_MARHSMALLOW));
		if (!_texture.loadFromFile("graphics/Brr-Brr-Patapim.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 8) {
		ajouterVie(9 * vie());
		ajouterReduction(25);
		ajouterForce(force());
		if (!_texture.loadFromFile("graphics/Udin-Din-Din-Dun.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 9) {
		ajouterForce((int)(-force() * 0.67));
		ajouterVie(39 * vie());
		ajouterReduction(45);
		ajouterVitesse(2* vitesse());
		ajouterForce(force());
		if (!_texture.loadFromFile("graphics/train_thomas.png"))
		{
			// error...
		}
		buffer0->loadFromFile("./song/train_thomas.ogg");
		_allBuffers.push_back(buffer0);
		_allSounds.push_back(sf::Sound(*buffer0));
		song_boucle = true;
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 10) {
		ajouterVie(9 * vie());
		ajouterReduction(15);
		if (!_texture.loadFromFile("graphics/capybara.png"))
		{
			// error...
		}
		int alea = Aleatoire(0, 3).entier();
		std::cout << "Alea" << alea << std::endl;
		std::string nom_musique;
		switch (alea)
		{
		case 0:
			nom_musique = "./song/capybara1.ogg";
			break;
		case 1:
			nom_musique = "./song/capybara2.ogg";
			break;
		case 2:
			nom_musique = "./song/capybara3.ogg";
			break;
		default:
			break;
		}
		if (!buffer0->loadFromFile(nom_musique))
		{
			std::cout << "Erreur chargement musique :" << nom_musique << std::endl;
		}
		else {
			buffer0->loadFromFile(nom_musique);
			_allBuffers.push_back(buffer0);
			_allSounds.push_back(sf::Sound(*buffer0));
			song_boucle = true;
		}
	
		_sprite.setTexture(_texture);
		}
	else if (difficulte == 11) {
		ajouterVie(4 * vie());
		ajouterReduction(15);
		ajouterForce(force()/2);
		ajouterVitesse(vitesse() / 2);
		if (!_texture.loadFromFile("graphics/Tralalero-tralala.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	else if (difficulte == 12) {
		ajouterVie(49 * vie());
		ajouterReduction(65);
		ajouterForce(force());
		ajouterVitesse(-(vitesse() / 2));
		if (!_texture.loadFromFile("graphics/GARDIEN_PORTE.png"))
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
	}
	if (id == 22) {
		if (!_texture.loadFromFile("graphics/Oxanne.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
	}
	_difficulte = difficulte;
	if (song_boucle == true) {
		_allSounds[0].setLoop(true);
		_allSounds[0].play();
	}
}




void Sanglier::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	if (_difficulte == 6) {
		_allSounds[0].play();
	}
	switch (choix) {

	case 0:
		DEGATS = degats(0.9, 1.2);
		Affichage().dessinerTexte(nom() + " charge ",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);

		ajouterMana(1);
		break;
	case 1:

		SOINS = soins(0.5, 0.75);
		Affichage().dessinerTexte(nom() + " se repose !  ",window);
	    status().ajouterCompteurProteger(5);
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

		ajouterChanceHabileter(2);
		equipeEnnemi().plusProcheVivant()->status().ajouterCompteurFragile(3);
		ajouterForce(force() / 10);
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
