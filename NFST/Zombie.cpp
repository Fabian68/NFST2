#include "Zombie.h"
#include "Affichage.h"
#include "AffichageCombat.h"

Zombie::Zombie(int LVL, std::string nom, int difficulte, int animal, int rareteAnimal) : Personnage(LVL, nom, 8, 1, 1, 50, 50, 90, 0, 95, 0, 0, animal, rareteAnimal)
{
	ajouterVie(9 * vie());
	status().ajouterCompteurProteger(10);
	if (difficulte == 1) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(9 * vie());
	}
	if (difficulte == 2) {
		ajouterForce(force());
		ajouterVitesse(vitesse());
		ajouterVie(19 * vie());
		ajouterReduction(99);
	}
}


void Zombie::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;
	int cible1;
	int cible2;
	int dernier;
	
	DEGATS = degats(1.0, 5.0);
	Affichage().dessinerTexte(nom() + " mords ",window);
	cible1 = equipeEnnemi().plusProcheVivant()->indiceEquipe();
	
	if (!equipeEnnemi().plusProcheVivant()->status().estEmpoisoner() && !equipeEnnemi().plusProcheVivant()->possedeBouclier()) {
		equipeEnnemi().plusProcheVivant()->status().appliquerPoison();
		equipeEnnemi().plusProcheVivant()->status().contamination();
		equipeEnnemi().plusProcheVivant()->status().ajouterCompteurFragile(10);
	}
	AttaqueBrut(DEGATS, equipeEnnemi().plusProcheVivant(),window);
	if (equipeEnnemi().estEnVie()) {
		cible2 = equipeEnnemi().plusProcheVivant()->indiceEquipe();
		if (cible1 != cible2 && equipeAllier().taille() < 10) {
			Affichage().dessinerTexte(nom() + " zombification ! ",window);
			equipeAllier().ajouterPerso(new Zombie(equipeEnnemi()[cible1]->niveau(), equipeEnnemi()[cible1]->nom()+ " zombie"));
			dernier = equipeAllier().taille() - 1;
			equipeAllier()[dernier]->setEnnemis(equipeEnnemi());
			equipeAllier()[dernier]->setAllier(equipeAllier());
			equipeAllier()[dernier]->setId(-2);
			//Affichage().dessinerEquipeIA(equipeAllier(),window);
		}

		if (attaqueDouble() && equipeEnnemi().estEnVie()) {
			DEGATS = degats(0.5, 2.5);
			Affichage().dessinerTexte(nom() + " mords ",window);
			cible1 = equipeEnnemi().plusProcheVivant()->indiceEquipe();
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			if (equipeEnnemi().estEnVie()) {
				cible2 = equipeEnnemi().plusProcheVivant()->indiceEquipe();
				if (cible1 != cible2 && equipeAllier().taille() < 10) {
					Affichage().dessinerTexte(nom() + " zombification ! ",window);
					equipeAllier().ajouterPerso(new Zombie(equipeEnnemi()[cible2]->niveau(), equipeEnnemi()[cible2]->nom()+ " zombie"));
					dernier = equipeAllier().taille() - 1;
					equipeAllier()[dernier]->setEnnemis(equipeEnnemi());
					equipeAllier()[dernier]->setAllier(equipeAllier());
					equipeAllier()[dernier]->setId(-2);
					//Affichage().dessinerEquipeIA(equipeAllier(),window);
				}
			}
		}
	}
	if (this->equipeAllier().ia() == false) {
		AffichageCombat().dessinerDeuxEquipes(this->equipeAllier(), this->equipeEnnemi(), window);
	}
	else {
		AffichageCombat().dessinerDeuxEquipes(this->equipeEnnemi(), this->equipeAllier(), window);
	}
		ajouterMana(1);
}

void Zombie::passif(int tour, sf::RenderWindow* window)
{
	int dernier;
	for (int i = 0;i < equipeEnnemi().taille();i++) {
		if (!equipeEnnemi()[i]->estEnVie() && equipeEnnemi()[i]->status().estContaminer()) {
			std::string str = equipeEnnemi()[i]->nom();
			equipeEnnemi()[i]->status().decontamination();
			equipeAllier().ajouterPerso(new Zombie(equipeEnnemi()[i]->niveau(),str + " zombie"));
			dernier = equipeAllier().taille() - 1;
			equipeAllier()[dernier]->setEnnemis(equipeEnnemi());
			equipeAllier()[dernier]->setAllier(equipeAllier());
			equipeAllier()[dernier]->setId(-2);
			//Affichage().dessinerEquipeIA(equipeAllier(),window);
		}
	}
	for (int i = 0; i < equipeAllier().taille()&&equipeEnnemi().estEnVie(); i++) {
		if (equipeAllier()[i] != this) {
			if (equipeAllier()[i]->id() == -2) {
				equipeAllier()[i]->attaqueEnnemis(window);
			}
		}
	}
	if (tour % 10 == 0) {
		int SOINS = soins(0.5, 1.0);
		bouclier(SOINS, this,window);
	}
	if (this->equipeAllier().ia() == false) {
		AffichageCombat().dessinerDeuxEquipes(this->equipeAllier(), this->equipeEnnemi(), window);
	}
	else {
		AffichageCombat().dessinerDeuxEquipes(this->equipeEnnemi(), this->equipeAllier(), window);
	}
}

void Zombie::passifDefensif(sf::RenderWindow* window)
{
	ajouterForce(1);
	int SOINS = soins(0.02, 0.06);
	bouclier(SOINS, this,window);
}
