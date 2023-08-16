#include "Isidore.h"
#include "Affichage.h"

Isidore::Isidore(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(7, E, O, A, Obj, "Isidore", 1, 1, 8, 10, 10, 10, 10, 10, 10, 10) {}


void Isidore::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
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
		Attaque(DEGATS, equipeEnnemi()[cible],window,allSounds);

		if (habile() && equipeEnnemi()[cible]->estEnVie()) {


			Affichage().dessinerTexte(nom() + "saute sur " + equipeEnnemi()[cible]->nom(),window);
			DEGATS = degats(1.0, 6.0);
		
			Attaque(DEGATS, equipeEnnemi()[cible],window,allSounds);
			ajouterMana(2);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " ganbade",window);
		for (double i = 0; i < 1.0; i += 0.01) {
			if (habile()) {
				SOINS = soins(i / 10.0, i / 10.0 + 0.01);
				soigner(SOINS, this,window);
			
				ajouterVieMax(vieMax()/1000);
			}
		}
		ajouterMana(1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + "embete les ennemis ",window);
		for (int i = 0; i < equipeEnnemi().taille(); i++) {

			equipeEnnemi()[i]->ajouterReduction(-3);

		}
		ajouterMana(-2);
		break;
	case 3:
		cible = equipeEnnemi().aleatoireEnVie()->indiceEquipe();
		Affichage().dessinerTexte(nom() + " encule " + equipeEnnemi()[cible]->nom(),window);
		DEGATS = degats(1.0, 2.5)+degats(1.0,2.5,CHOIXVITESSE);
		Attaque(DEGATS, equipeEnnemi()[cible],window,allSounds);
		ajouterMana(-3);
		break;
	}
}

void Isidore::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	ajouterVieMax(niveau()/10);
	if ((tour + 1) % 5 == 0) {
		if (habile() || attaqueDouble()) {
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
		soigner((int)vieMax(), this,window);
		bouclier(bouclierMax(), this,window);
	}
	
}

void Isidore::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
}
