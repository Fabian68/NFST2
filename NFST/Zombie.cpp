#include "Zombie.h"
#include "Affichage.h"
#include "AffichageCombat.h"
#include "Objets.h"

Zombie::Zombie(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 8, 2, 1, 50, 50, 90, 0, 95, 0, 0, animal, rareteAnimal)
{
	ajouterVie(9 * vie());
	status().ajouterCompteurProteger(10);
	if (!_texture.loadFromFile("graphics/lapin2.png"))
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
		ajouterReduction(99);
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
	if (tour % 10 == 0) {
		int SOINS = soins(0.5, 1.0);
		bouclier(SOINS, C, this, window);
	}
}

void Zombie::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	ajouterForce(1);
	int SOINS = soins(0.02, 0.06);
	bouclier(SOINS, C, this, window);
}
