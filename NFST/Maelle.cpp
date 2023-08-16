#include "Maelle.h"
#include "Affichage.h"

Maelle::Maelle(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(13, E, O, A, Obj, "Maelle", 3, 3, 1, 30, 30, -20, 0, 20, 0, 0)
{
	estTransformer = false;
}

void Maelle::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;

	int compteur;
	double k = 1.0;
	if (habile()) {
		switch (choix) {

		case 0:
			compteur = 1;
			Affichage().dessinerTexte(nom() + " s'enerve ! ",window);
			while (habile() && equipeEnnemi().estEnVie()&&compteur<=6) {
				DEGATS = degats(0.0025 * k, 0.025 * k);
				Attaque(DEGATS + force() / 20, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
				k *= 2;
				compteur++;
			}
			if (attaqueDouble()) {
				compteur = 1;
				k =k/2.0;
				while (habile() && equipeEnnemi().estEnVie() && compteur <= 6) {
					DEGATS = degats(0.0025 * k, 0.025 * k);
					Attaque(DEGATS + force() / 20, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
					k *= 2;
					compteur++;
				}
			}
			ajouterMana(1);
			break;
		case 1:
			Affichage().dessinerTexte(nom() + " fait du tapis roulant !  ",window);
			for (double i = 1.0;i <= 25.0&&this->estEnVie();i += 1.0) {
				DEGATS = degats(i/100.0, i/50.0);
				Attaque(DEGATS,this, C, window, allSounds);
				SOINS = soins(i / 200.0, i / 100.0);
				soigner(SOINS, C, this, window);
				ajouterVieMax(niveau() / 100);
			}
			ajouterMana(-1);
			break;
		case 2:

			Affichage().dessinerTexte(nom() + " joue a la tablette !  ",window);
			
			if (habile()) {
				ajouterCoupCritique(6);
				ajouterDegatsCritique(12);
			}
			else {
				ajouterCoupCritique(3);
				ajouterDegatsCritique(6);
			}
			ajouterMana(-2);
			break;
		case 3:
			if (estTransformer == false) {
				Affichage().dessinerTexte(nom() + " Se transforme en dinausore ! ",window);
				setNom("Maellosaure");
				ajouterForce(force());
				ajouterVitesse(vitesse());
				ajouterVieMax(9 * vieMax());
				ajouterChanceHabileter(20);
				ajouterMana(-3);
				estTransformer = true;
			}
			else {
				ajouterMana(3);
			}
			break;
		}
	}
	else {
		Affichage().dessinerTexte(nom() + " ne fait rien !  ",window);
		ajouterMana(1);
	}
}

void Maelle::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if ((tour + 1) % 10 == 0) {
		Affichage().dessinerTexte(nom() + " Les graisses de Maelle la guerrissent ! ",window);
		soigner((int)vie()/5, C, this, window);
	}
}

void Maelle::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	bouclier((int)vieMax()/100+niveau(), C, this, window);
}
