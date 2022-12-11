#include "Tortue.h"

#include "Affichage.h"
#include "Aleatoire.h"
Tortue::Tortue(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(14, E, O, A, Obj, "Tortue", 2, 2, 4, 0, 10, 10, 10, 100, 0, 3)
{
	if (niveau() > 999) {
		setNom("Ancienne tortue");
		ajouterForce(6 * niveau());
		ajouterVitesse(-3*niveau());
		ajouterVie((long long int)520 * niveau());
		ajouterReduction(80);
	}
	else if (niveau() > 99) {
		setNom("Adulte tortue");
		ajouterForce(4 * niveau());
		ajouterVitesse(-2*niveau());
		ajouterVie((long long int)160 * niveau());
		ajouterReduction(50);
	}
	else if (niveau() > 9) {
		setNom("Jeune tortue");
		ajouterForce(2 * niveau());
		ajouterVitesse(-niveau());
		ajouterVie((long long int)40 * niveau());
		ajouterReduction(20);
	}
	else {
		setNom("Bebe tortue");
	}
	status().setReducteur(2 * niveau());
	status().devientEnmagasineur();
}

void Tortue::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;
	switch (choix) {

	case 0:
		DEGATS = degats(0.31, 0.62)+status().enmagasination()/10;
		status().retirerEmagasination(status().enmagasination());
		Affichage().dessinerTexte(nom() + " Morsure ! ",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
	
		ajouterMana(1);
		break;
	case 1:
		if (bouclier() == bouclierMax()) {
			Affichage().dessinerTexte(nom() + " emagasine !  ",window);
			status().ajoutEnmagasination(bouclierMax());
			ajouterMana(-1);
		}
		else {
			Affichage().dessinerTexte(nom() + " remplie bouclier !  ",window);
			bouclier(bouclierMax(), this,window);
			ajouterMana(-1);
		}
		
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " se soigne !  ",window);
		status().soignerBrulure();
		status().soignerPoison();
		soigner((int)vieMax() / 10, this,window);
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " coup de queue ! ",window);
		for (int i = 0; i < equipeEnnemi().taille(); i++) {
			DEGATS =(int)( 0.015 * (double)vie() + 0.005 * (double)vieMax() + 0.5 * (double)force() + 1.0 * (double)vitesse());
			Attaque(DEGATS, equipeEnnemi()[i],window);
		}
		ajouterMana(-3);
		break;
	}
}

void Tortue::passif(int tour, sf::RenderWindow* window)
{
	soigner((int)(vieMax()-vie())/10, this,window);
	bouclier((bouclierMax() - bouclier()) / 10, this,window);
}

void Tortue::passifDefensif(sf::RenderWindow* window)
{
	if (Aleatoire(0, 101).entier() <= chanceHabileter()) {
		Attaque((int)vieMax()/100, equipeEnnemi().plusProcheVivant(),window);
		equipeAllier().moinsResistant()->ajouterReduction(1);
		equipeAllier().moinsResistant()->status().ajouterCompteurProteger(1);
	}
}
