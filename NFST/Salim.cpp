#include "Salim.h"
#include "Affichage.h"
#include "Aleatoire.h"

Salim::Salim(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(15, E, O, A, Obj, "Salim", 6, 3, 1, 0, 25, 25, 0, 25, 0, 0), estTransformer{ false }, superTransformation{ false } {}


void Salim::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	int nb;
	
	switch (choix) {

	case 0:

		Affichage().dessinerTexte(nom() + " racine poignard ",window);
		DEGATS = (int)(Aleatoire(0.03, 0.06).decimal() * (double)vieMax() + degats(0.2, 0.4));
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
		if (habile()&&equipeEnnemi().estEnVie()) {
			DEGATS = (int)(Aleatoire(0.01, 0.02).decimal() * (double)vieMax() + degats(0.05, 0.15));
			AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			ajouterMana(2);
		}
		ajouterMana(1);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " SUPERSOIN ! ",window);
		nb = equipeAllier().nbEnVie();
		SOINS = soins(2.0 / nb, 6.0 / nb);
		for (int i = 0;i < equipeAllier().taille();i++) {
			SOINS = soins(2.0 / nb, 6.0 / nb);
			soigner(SOINS, equipeAllier()[i],window);
			SOINS = soins(1.0 / nb, 3.0 / nb);
			bouclier(SOINS, equipeAllier()[i],window);
		}
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " endormissement ",window);
		SOINS = soins(0.5, 5.0);
		bouclier(SOINS, this,window);
		SOINS = soins(0.25, 2.5);
		soigner(SOINS, this,window);
		ajouterReduction(5);
		ajouterMana(-2);
		break;
	case 3:
		if (!estTransformer) {
			Affichage().dessinerTexte(nom() + " TRANSFORMATION ! ",window);
			reduireVieMax((vieMax() / 10) * 9);
			ajouterForce(force() * 2);
			setNom("GRAND SALIMALEKUM");
			estTransformer = true;
			ajouterReduction(10);
		}
		else if (!superTransformation && mana() > 9) {
			Affichage().dessinerTexte(nom() + "SUUUPPEEEERR TRANSFORMATION ! ",window);
			reduireVieMax((vieMax() / 10) * 9);
			ajouterForce(force() * 2);
			setNom("GRAND SALIMALEKUM DIEUX DES TERRES ET DES OCEANS");
			superTransformation = true;
			ajouterReduction(20);
		}
		else {
			Affichage().dessinerTexte(nom() + " rejuvenation ! ",window);
			ajouterVieMax(niveau()*10);
			SOINS = soins(0.2, 1.2);
			soigner(SOINS, this,window);
			SOINS = soins(0.1, 0.6);
			bouclier(SOINS, this,window);
		}
		ajouterMana(-3);
		break;
	}
}

void Salim::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int DEGATS;

	if (habile()) {
		ajouterVieMax(force() / 5);
		if (habile()) {
			ajouterVieMax(force());
		}
	}
	ajouterVieMax(force() / 10);
	if ((tour + 1) % 100 == 0) {
		Affichage().dessinerTexte(nom() + " jugement dernier ! ",window);
		for (int i = 0;i < equipeEnnemi().taille();i++) {
			DEGATS = degats(1.0, 11.0);
			if (habile()) {
				AttaqueBrut(DEGATS, equipeEnnemi()[i],window);
			}
			else {
				Attaque(DEGATS, equipeEnnemi()[i],window,allSounds);
			}
		}
	}
}

void Salim::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
	if (habile()) {
		ajouterVieMax(force() / 5);
		if (habile()) {
			ajouterVieMax(force());
		}
	}
	ajouterVieMax(force()/10);
}
