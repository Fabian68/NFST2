#include "Magicien.h"
#include "Affichage.h"

Magicien::Magicien(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 1, 3, 6, 5, 5, -30, 1, 1, 1, 1, animal, rareteAnimal), stade{1}
{
	status().ajouterCompteurProteger(10);
	setNom("Petit magicien");
	ajouterVie( 4*vie());
	ajouterVitesse(vitesse());
	status().setAdducteur(2*niveau());
}

void Magicien::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	int nb = equipeAllier().nbEnVie();
	double ratio = (double)(vieMax() / vie());
	int indice;
	int mult1 = 0, mult2 = 0;
	switch (choix) {

	case 0:
		if (stade <= 3) {
			DEGATS = degats(0.6, 0.6 + 0.1 * stade * 2);
			Affichage().dessinerTexte(nom() + " boule de feu ",window);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		else if (stade == 4) {
			Affichage().dessinerTexte(nom() + " 3 boule de feu ",window);
			for (int i = 0;i < 3;i++) {
				DEGATS = degats(0.9, 1.6);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			}
		}
		else if (stade == 5) {
			Affichage().dessinerTexte(nom() + " météores ! ",window);
			for (int i = 0;i < 5;i++) {
				DEGATS = degats(2.6, 5.2);
				Attaque(DEGATS, equipeEnnemi().aleatoireEnVie(), C, window, allSounds);
			}
		}
		ajouterMana(1);
		break;
	case 1:

		if (stade <= 3) {
			equipeEnnemi().plusProcheVivant()->ajouterReduction(-stade);
			DEGATS = degats(0.8, 1.0 + 0.1 * stade * 2);
			Affichage().dessinerTexte(nom() + " pique de glace ",window);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		else if (stade == 4) {
			Affichage().dessinerTexte(nom() + " 3 pique de glace ",window);

			equipeEnnemi().plusProcheVivant()->ajouterReduction(-2*stade);
			indice = equipeEnnemi().aleatoireEnVie()->id();
			equipeEnnemi().perso(indice)->ajouterReduction(-2 * stade);
			equipeEnnemi().plusLoinVivant()->ajouterReduction(-2 * stade);
			
			DEGATS = degats(1.2, 1.9);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);

			DEGATS = degats(1.4, 2.1);
			Attaque(DEGATS, equipeEnnemi().perso(indice), C, window, allSounds);

			DEGATS = degats(1.7, 2.4);
			Attaque(DEGATS, equipeEnnemi().plusLoinVivant(), C, window, allSounds);
			
		}
		else if (stade == 5) {
			Affichage().dessinerTexte(nom() + " tempete de neige ! ",window);
			for (int i = 0;i <=30;i++) {
				DEGATS = degats(0.1, 1.0);
				indice = equipeEnnemi().aleatoireEnVie()->id();
				equipeEnnemi().perso(indice)->ajouterReduction(-3);
				AttaqueBrut(DEGATS, equipeEnnemi().perso(indice),C,window);
			}
		}
		
		ajouterMana(-1);
		break;
	case 2:

		if (stade <= 3) {
			equipeEnnemi().plusProcheVivant()->ajouterReduction(-stade);
			DEGATS = degats(0.6, 1.0 + 0.1 * stade );
			Affichage().dessinerTexte(nom() + " éclair ",window);
			AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),C, window);
		}
		else if (stade == 4) {
			Affichage().dessinerTexte(nom() + " Tonerre ",window);

			for (int i = 1;i <= 4;i++) {
				DEGATS = degats(0.4*i, 0.8*i);
				AttaqueBrut(DEGATS, equipeEnnemi().aleatoireEnVie(), C,window);
			}

		}
		else if (stade == 5) {
			Affichage().dessinerTexte(nom() + "Maelstrom ! ",window);
			for (int i = 0;i <equipeEnnemi().taille();i++) {
				DEGATS = degats(5.0, 10.0);
				AttaqueBrut(DEGATS, equipeEnnemi()[i],C,window);
			}
		}

		ajouterMana(-1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " SOINS HABILE ! ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			SOINS = soins(0.3, 0.9);
			soigner(SOINS, C, equipeAllier()[i], window);
			equipeAllier()[i]->ajouterChanceDoubleAttaque(2);
			equipeAllier()[i]->ajouterChanceHabileter(2);
			equipeAllier()[i]->ajouterCoupCritique(2);
			equipeAllier()[i]->ajouterDegatsCritique(5);
			equipeAllier()[i]->ajouterReduction(5);
			equipeAllier()[i]->ajouterVieMax(vieMax()/10);
		}
		ajouterVieMax(bouclier());
		reduireBouclier(bouclier());
		ajouterMana(-3);
		break;
	}
}

void Magicien::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (tour == 5) {
		stade = 2;
		ajouterChanceDoubleAttaque(5);
		ajouterChanceHabileter(5);
		ajouterCoupCritique(5);
		ajouterDegatsCritique(10);
		ajouterReduction(10);
		ajouterVieMax(vieMax());
		setNom("Apprenti Magicien");
		status().ajouterCompteurProteger(4);
	}
	else if (tour == 10) {
		stade = 3;
		ajouterChanceDoubleAttaque(10);
		ajouterChanceHabileter(10);
		ajouterCoupCritique(5);
		ajouterDegatsCritique(20);
		ajouterReduction(20);
		ajouterVieMax(vieMax());
		setNom("Magicien confirmé");
		status().ajouterCompteurProteger(12);
	}
	else if (tour == 20) {
		stade = 4;
		ajouterChanceDoubleAttaque(10);
		ajouterChanceHabileter(10);
		ajouterCoupCritique(5);
		ajouterDegatsCritique(40);
		ajouterReduction(30);
		ajouterVieMax(vieMax());
		setNom("Grand mage");
		status().ajouterCompteurProteger(36);
	}
	else if (tour == 40) {
		stade = 5;
		ajouterChanceDoubleAttaque(10);
		ajouterChanceHabileter(10);
		ajouterCoupCritique(5);
		ajouterDegatsCritique(80);
		ajouterReduction(40);
		ajouterVieMax(vieMax());
		setNom("Archimage");
		status().ajouterCompteurProteger(118);
	}
	if ((tour + 1) % 5 == 0) {
		bouclier((int)((double)stade * (double)bouclierMax() / 10.0), C, this, window);
		status().ajouterCompteurProteger(5);
		if (stade == 5) {
			attaqueEnnemis(C,window,allSounds);
			status().ajouterCompteurProteger(10);
		}
	}
}

void Magicien::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
}
