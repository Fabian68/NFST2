#include "Moustick.h"
#include "Affichage.h"

Moustick::Moustick(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(4, E, O, A, Obj, "Moustick", 3, 4, 3, 0, 0, 0, 0, 0, 0, 0) {

	status().devientEnmagasineur();

}


void Moustick::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;

	int ratio = 100 * static_cast<int>(1.0 - (vie() * 1.0) / (vieMax() * 1.0));
	ratio = std::min(99, ratio);
	int ratioPositif = static_cast<int>((vieMax() * 1.0) / (vie() * 1.0))+1;
	ratioPositif = std::min(ratioPositif, 30);
	setReduction(ratio);
	
	switch (choix) {

	case 0:
		

	
		Affichage().dessinerTexte(nom() + " attaque de base",window);
		
		for (int i = 0; i < ratioPositif&&equipeEnnemi().estEnVie(); i++) {
			DEGATS = degats(ratioPositif / 8.0, ratioPositif / 4.0);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			ajouterMana(1);
		}
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " attaque enrage",window);
		DEGATS = degats(ratioPositif / 5.0, ratioPositif / 2.5);
		if (bouclier() > bouclierMax() / 2) {
			DEGATS += static_cast<int>(bouclier() * 0.2);
			ajouterBouclier(-bouclierMax() / 2);
			
		}
		DEGATS += status().enmagasination();
		status().retirerEmagasination(status().enmagasination());
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + "attaques puissante ! ",window);
		for (int i = 0; i < ratioPositif && equipeEnnemi().estEnVie(); i++) {
			DEGATS = degats(ratioPositif / 6.0, ratioPositif / 3.0);
			equipeEnnemi().plusProcheVivant()->status().ajouterCompteurFragile(5);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			ajouterMana(1);
		}
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " nuit de folie ",window);
		status().ajoutEnmagasination((int)vie() / 2);
		status().ajouterCompteurProteger(20);
		reduireVie(vie() / 2);
		ajouterMana(-3);
		attaqueEnnemis(window);
		break;
	}
}

void Moustick::passif(int tour, sf::RenderWindow* window)
{
	reduireVie(static_cast<int>(vie() / 20.0));

	int ratio = 100*static_cast<int>(1.0-(vie() * 1.0) / (vieMax() * 1.0));
	ratio = std::min(99, ratio);
	setReduction(ratio);
}

void Moustick::passifDefensif(sf::RenderWindow* window)
{
	int ratio = 100 * static_cast<int>(1.0 - (vie() * 1.0) / (vieMax() * 1.0));
	ratio = std::min(99, ratio);
	setReduction(ratio);
	
}
