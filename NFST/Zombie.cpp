#include "Zombie.h"
#include "Affichage.h"
#include "AffichageCombat.h"
#include "Objets.h"

Zombie::Zombie(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 15, 2, 1, 50, 50, 75, 0, 75, 0, 0, animal, rareteAnimal)
{
	status().ajouterCompteurProteger(10);
	if (!_texture.loadFromFile("graphics/zombie.png"))
	{
		// error...
	}
	_sprite.setTexture(_texture);
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
	else if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(19 * vie());
		ajouterReduction(80);
	}
	else if (difficulte == 3) {
		ajouterVitesse(vitesse()*2);
		ajouterVie(4 * vie());
		ajouterChanceRicochet(75); 
		//Skin
		Objets obj;
		setObjets(obj.objetNumero(OBJET_GILET_PARBALLE), obj.objetNumero(OBJET_MARHSMALLOW));
		if (!_texture.loadFromFile("graphics/steve.png"))
		{
			// error...
		}
		_sprite.setTexture(_texture);
		std::shared_ptr<sf::SoundBuffer> buffer0 = std::make_shared<sf::SoundBuffer>();
		buffer0->loadFromFile("./song/steve.ogg");
		_allBuffers.push_back(buffer0);
		_allSounds.emplace_back(*buffer0);
		_allSounds[0].setLoop(true);
		_allSounds[0].play();
	}
}


void Zombie::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;	
	DEGATS = degats(1.0, 2.0);
	Affichage().dessinerTexte(nom() + " mords ",window);

	
	if (!equipeEnnemi().plusProcheVivant()->status().estEmpoisoner() && !equipeEnnemi().plusProcheVivant()->possedeBouclier()) {
		equipeEnnemi().plusProcheVivant()->status().appliquerPoison();
		equipeEnnemi().plusProcheVivant()->status().contamination();
		equipeEnnemi().plusProcheVivant()->status().ajouterCompteurFragile(10);
	}
	AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),C,window);
	
	if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.5, 2.5);
			Affichage().dessinerTexte(nom() + " lance-ghoule ",window);
			Attaque(DEGATS, equipeEnnemi().plusLoinVivant(), C, window, allSounds);
	}
	ajouterMana(1);
}

void Zombie::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
}

void Zombie::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	ajouterForce(1);
}
