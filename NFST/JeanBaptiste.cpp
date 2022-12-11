#include "JeanBaptiste.h"
#include "Affichage.h"
#include "Aleatoire.h"

JeanBaptiste::JeanBaptiste(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(12, E, O, A, Obj, "JB", 4, 1, 5, 5, 10, 50, 15, 50, 15, 5)
{
	ajouterVie(9 * vie());
}


void JeanBaptiste::attaqueEnnemis(sf::RenderWindow* window)
{
	if (equipeEnnemi().estEnVie()) {
		int choix = choixAttaque();
		int DEGATS;
		int SOINS;

		switch (choix) {

		case 0:
			if (devie()) {
				Affichage().dessinerTexte(nom() + " se défend ",window);	
				DEGATS = degats(0.5, 2.0);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			}
			else {
				ajouterMana(1);
			}
			
			
			break;
		case 1:
			Affichage().dessinerTexte(nom() + " mange sans gluten",window);

			SOINS = (int)((double)vieMax() * 0.005+(double)vie()*0.03);
			soigner(SOINS, this,window);
			ajouterMana(1);
			break;
		case 2:

			Affichage().dessinerTexte(nom() + " degustation de vin ",window);
			for (int i = 0;i < equipeAllier().taille();i++) {
				SOINS = soins(0.66, 1.22);
				soigner(SOINS, equipeAllier()[i],window);

			}
			ajouterMana(1);

			break;
		case 3:
			Affichage().dessinerTexte(nom() + " protege le plus faible ! ",window);
			equipeAllier().moinsResistant()->ajouterReduction(25);
			ajouterMana(-3);
			break;
		}
	}
}

void JeanBaptiste::passif(int tour, sf::RenderWindow* window)
{
	int xp;
	
	if ((tour + 1) % 10 == 0) {
		Affichage().dessinerTexte(nom() + " donne de l'xp a lequipe ! ",window);
		if (niveau() >= 7000) {
			xp = 7000;
		}else if (niveau() >= 700) {
			xp = 700;
		}
		else if (niveau() >= 70) {
		xp = 70;
		}
		else if (niveau() >= 7) {
			xp = 7;
		}
		else {
			xp = 1;
		}
		xp *= equipeAllier().taille();
		Experiences E;
		equipeAllier().ajouterExperience(xp, E);
	}
	if (tour == 10 || tour == 20 || tour == 30) {
		Affichage().dessinerTexte(nom() + " partage sa vie, son énergie, sa pation ! ",window);
		equipeAllier().aleatoireEnVie()->ajouterVieMax((vieMax() / 5));
		reduireVieMax((vieMax() / 10));
	}
	if (tour == 60 || tour == 80 || tour == 100) {
		Affichage().dessinerTexte(nom() + " partage sa vie, son énergie, sa pation ! ",window);
		equipeAllier().aleatoireEnVie()->ajouterVieMax((vieMax() / 4));
		reduireVieMax((vieMax() / 20));
	}
	if (tour == 130 || tour == 160 || tour == 200) {
		Affichage().dessinerTexte(nom() + " partage sa vie, son énergie, sa pation ! ",window);
		equipeAllier().aleatoireEnVie()->ajouterVieMax((vieMax() / 3));
		reduireVieMax((vieMax() / 30));
	}
	
}

void JeanBaptiste::passifDefensif(sf::RenderWindow* window)
{
}
