#include "Tellurique.h"
#include "Affichage.h"

Tellurique::Tellurique(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal, int id) : Personnage(LVL, nom, 4, 4, 2, 20, 20, 20, 2, 20, 2, 12, animal, rareteAnimal), premiereFoisToucher{false}
{
	setId(id);
	ajouterVie(9 * vie());
	if (difficulte == 1) {
		
		ajouterVie(19 * vie());
	}
	status().setReducteur(niveau() * 3);

	if (difficulte == 2) {

		ajouterVie(49 * vie());
		status().setReducteur(niveau() * 10);
	}
}

void Tellurique::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	int nb = equipeAllier().nbEnVie();
	double ratio = (double)(vieMax() / vie());
	int indice;
	int mult1=0, mult2=0;
	switch (choix) {

	case 0:
		DEGATS = degats(0.7+pourcentageReduction()/100.0, 1.4 + pourcentageReduction() / 20.0);
		Affichage().dessinerTexte(nom() + " charge ",window);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);

		ajouterCoupCritique(2);
		ajouterDegatsCritique(6);
		ajouterMana(1);
		break;
	case 1:

		SOINS = soins(ratio, ratio*2);
		Affichage().dessinerTexte(nom() + " ressource terrienne !  ",window);
		equipeAllier().soignerZone(SOINS, this,window);
		ajouterMana(1);
		break;
	case 2:

		Affichage().dessinerTexte(nom() + " Telluriforce !  ",window);
		for (int i = 0; i <= equipeEnnemi().taille() / 2; i++) {
			DEGATS = degats(0.10+mult1/80, 0.20+mult1/40 );
			mult1 += equipeEnnemi()[i]->pourcentageReduction();
			Attaque(DEGATS, equipeEnnemi()[i],window,allSounds);

			DEGATS = degats(0.10 + mult2 / 80, 0.20 + mult2 / 40);
			indice = abs(equipeEnnemi().taille() - 1 - i);
			mult2 += equipeEnnemi()[indice]->pourcentageReduction();
			Attaque(DEGATS, equipeEnnemi()[indice],window,allSounds);
		}
		ajouterChanceHabileter(3);
		ajouterMana(1);
		break;
	case 3:
		Affichage().dessinerTexte(nom() + " eruption ! ",window);
		if (habile()) {
			
			for (int i = 0;i < equipeEnnemi().taille();i++) {
				if (i <= 4) {
					DEGATS = degats(8.0 - 2.0 * i, 10.0 - 2.0 * i);
				}
				else {
					DEGATS = degats( i/2, i);
				}
				Attaque(DEGATS, equipeEnnemi()[i],window,allSounds);
				equipeEnnemi()[i]->status().ajouterCompteurFragile(1);
			}
		}
		else {
			for (int i = 0;i < equipeEnnemi().taille();i++) {
				DEGATS = degats( i,  i+2.0);
			}
		}
		ajouterVieMax(bouclier());
		reduireBouclier(bouclier());
		ajouterMana(-3);
		break;
	}
}

void Tellurique::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	AjouterBouclier(bouclierMax() / 10,window);
	status().ajouterCompteurProteger(1);
	ajouterVieMax( vie()/100);
}

void Tellurique::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
	for (int i = 0;i < equipeAllier().taille();i++) {
		equipeAllier()[i]->ajouterReduction(1);
		equipeAllier()[i]->status().ajouterCompteurProteger(1);
	}
	if (premiereFoisToucher == false) {
		for (int i = 0;i < equipeEnnemi().taille();i++) {
			if (equipeEnnemi()[i]->estEnVie()) {
				AttaqueBrut((int)equipeEnnemi()[i]->vieMax() / 5, equipeEnnemi()[i],window);
				if (!equipeEnnemi()[i]->status().estBruler()) {
					equipeEnnemi()[i]->status().appliquerBrulure();
				}
			}
		}
		premiereFoisToucher = true;
	}
}
