#include "Moustick.h"
#include "Affichage.h"

Moustick::Moustick(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(4, E, O, A, Obj, "Moustick", 1, 3, 3, 0, 10, 0, 0, 0, 0, 0) {

	status().devientEnmagasineur();

}


void Moustick::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
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
		
		for (int i = 0; i < (1 + ratioPositif/2)&&equipeEnnemi().estEnVie(); i++) {
			DEGATS = degats(ratioPositif / 30.0, ratioPositif / 15.0);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			ajouterMana(1);
		}
		ajouterMana(1+ratio/10);
		break;
	case 1:
		Affichage().dessinerTexte(nom() + " attaque enrage",window);
		DEGATS = degats(ratioPositif / 8.0, ratioPositif / 4.0);
		if (bouclier() > bouclierMax() / 2) {
			DEGATS += static_cast<int>(bouclier() * 0.2);
			AjouterBouclier(-bouclierMax() / 2, C, window);
			
		}
		DEGATS += status().enmagasination();
		status().retirerEmagasination(status().enmagasination());
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		ajouterMana(-1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + "attaques puissante ! ",window);
		for (int i = 0; i < ratioPositif && equipeEnnemi().estEnVie(); i++) {
			DEGATS = degats(ratioPositif / 10.0, ratioPositif / 5.0);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(-2);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " nuit de folie ",window);
		status().ajoutEnmagasination((int)vie() / 10);
		status().ajouterCompteurProteger(10);
		reduireVie(vie() / 2);
		ajouterMana(-3);
		
		attaqueEnnemis(C,window,allSounds);
		break;
	}
}

void Moustick::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	reduireVie(static_cast<int>(vie() / 20.0));

	int ratio = 100*static_cast<int>(1.0-(vie() * 1.0) / (vieMax() * 1.0));
	ratio = std::min(99, ratio);
	setReduction(ratio);
}

void Moustick::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	int ratio = 100 * static_cast<int>(1.0 - (vie() * 1.0) / (vieMax() * 1.0));
	ratio = std::min(99, ratio);
	setReduction(ratio);
	
}
