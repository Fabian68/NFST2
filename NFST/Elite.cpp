#include "Elite.h"
#include "Affichage.h"

Elite::Elite(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 2, 4, 4, 20, 20, 50, 0, 0, 20, 0, animal, rareteAnimal)
{
	ajouterVie( vie());
	ajouterBouclier(bouclierMax());

	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
	if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(49 * vie());
		status().setReducteur(10 * niveau());
	}
	pause = 0;
}


void Elite::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;

	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " Mitraillette alien",window);
		for (int i = 0;i < 10 && equipeEnnemi().estEnVie();i++) {
			DEGATS = degats(0.2, 0.3);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			if (attaqueDouble() && equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.2, 0.3 );
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
				
			}
		}
		if (attaqueDouble()) {
			for (int i = 0;i < 10 && equipeEnnemi().estEnVie();i++) {
				DEGATS = degats(0.2, 0.3);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
				if (attaqueDouble() && equipeEnnemi().estEnVie()) {
					DEGATS = degats(0.2, 0.3);
					Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);

				}
			}
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " coup épée ",window);
		DEGATS = degats(2.0, 4.0);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(1.5, 3.0);
			Attaque(DEGATS, equipeEnnemi().plusFaible(),window);

		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " WUT WUT WUT ",window);
		equipeEnnemi().plusProcheVivant()->ajouterReduction(-10);
		ajouterMana(1);
		break;
	case 3:

		Affichage().dessinerTexte(nom() + " U DADA ",window);
		this->ajouterForce(force() /5);
		ajouterMana(-3);
		break;
	}
}

void Elite::passif(int tour, sf::RenderWindow* window)
{
	if ((pause + 1) % 4 == 0) {
		bouclier(bouclierMax(), this,window);
		status().ajouterCompteurProteger(10);
	}
	pause++;
}

void Elite::passifDefensif(sf::RenderWindow* window)
{
	pause = 0;
}
