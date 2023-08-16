#include "Bryan.h"
#include "Aleatoire.h"
#include "Affichage.h"

Bryan::Bryan(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(5, E, O, A, Obj, "Bryan", 1, 4, 4, 15, 15, -100, 0, 0, 20, 3) {
	ajouterCoupCritique(5);
	ajouterDegatsCritique(25);
}

void Bryan::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	int indice;
	double RATIO;
	DEGATS = static_cast<int>(degats(0.05, 0.25) * (1.0 + degatsCritiques() / 100.0));
	Affichage().dessinerTexte(nom() + "Attaque critique",window);
	Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
	switch (choix) {

	case 0:
		if (equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.45, 0.75);
			Affichage().dessinerTexte(nom() + " coup de dague ! ",window);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.12, 0.24);
				AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),C,window);
			}
		}
		ajouterMana(2);
		break;
	case 1:
		if (equipeEnnemi().estEnVie()) {
			Affichage().dessinerTexte(nom() + " vise le plus faible",window);
			DEGATS = degats(0.15, 0.45);
			indice = equipeEnnemi().plusFaible()->indiceEquipe();
			RATIO = (equipeEnnemi().perso(indice)->vieMax() * 1.0) / (equipeEnnemi().perso(indice)->vie() * 1.0);
			RATIO = std::min(RATIO, 20.0);
			DEGATS = static_cast<int>(DEGATS * RATIO);
			Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		}
		ajouterMana(-1);
		break;
	case 2:
		if (equipeEnnemi().estEnVie()) {
			Affichage().dessinerTexte(nom() + " attaque par derrière ",window);
			DEGATS = degats(0.75, 1.75);
			AttaqueBrut(DEGATS, equipeEnnemi().plusLoinVivant(),C,window);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.5, 1.5,CHOIXVITESSE);
				AttaqueBrut(DEGATS, equipeEnnemi().plusFaible(),C,window);
			}
		}
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " ce boost ! ",window);
		ajouterCoupCritique(1);
		ajouterDegatsCritique(5);
		if (habile()) {
			ajouterCoupCritique(1);
			ajouterDegatsCritique(5);
		}
		SOINS = soins(0.5, 2.5);
		if (vie() == vieMax()) {
			bouclier(SOINS / 2, C, this, window);
		}
		else {
			soigner(SOINS, C, this, window);
		}
		
		ajouterMana(-3);
		break;
	}
}

void Bryan::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (status().estEmpoisoner()) {
		status().soignerPoison();
	}
	if (tour % 10 == 0) {
		ajouterCoupCritique(1);
		ajouterDegatsCritique(2);
	}
}

void Bryan::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	if (Aleatoire(0, 101).entier() < pourcentageEsquive()) {
		int SOINS = static_cast<int>(0.25 * vitesse());
		bouclier(SOINS, C, this, window);
	}
}
