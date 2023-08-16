#include "Florian.h"
#include "Affichage.h"
#include "Aleatoire.h"

Florian::Florian(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(11, E, O, A, Obj, "Florian", 5, 2, 1, 20, 0, 5, 0, 0, 0, 0) {

	floppy = false;
	floppylegende = false;
	if (possedeObjetNumero(32)) {
		floppy = true;
	}
	//si possede obj 32
	if (floppy == true) {
		setNom("Floppy");
		ajouterChanceHabileter(20);
		ajouterForce(niveau());
		ajouterVitesse(3 * niveau());
		ajouterEsquive(20);
	}
}

void Florian::attaqueEnnemis(Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	
	switch (choix) {

	case 0:
		if (floppy == true) {
			Affichage().dessinerTexte(nom() + " coup épée ",window);
			Attaque(force(), equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			if ((attaqueDouble() && equipeEnnemi().estEnVie())) {
				Attaque(force(), equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			}
		}
		else {
			SOINS = soins(0.25, 0.75);
			Affichage().dessinerTexte(nom() + " se détend ",window);
			bouclier(SOINS, C, this, window);

			if ((attaqueDouble() && equipeEnnemi().estEnVie()) || (vie() == vieMax() && equipeEnnemi().estEnVie())) {

				Affichage().dessinerTexte(nom() + " se trompe ",window);
				DEGATS = degats(0.37, 0.97);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
			}
			
		}
		ajouterMana(1);
		break;
	case 1:
		if (floppy) {
			Affichage().dessinerTexte(nom() + " envoie une bombe",window);
			equipeEnnemi().attaqueZone(force(), this, C,window, allSounds);
		}
		else {
			Affichage().dessinerTexte(nom() + " bois un coup",window);

			SOINS = degats(0.45, 0.85);
			soigner(SOINS, C, this, window);

			if ((habile() && equipeEnnemi().estEnVie())|| (vie() == vieMax() && equipeEnnemi().estEnVie())) {
				Affichage().dessinerTexte(nom() + " rote ",window);
				DEGATS = degats(0.15, 0.25);
				DEGATS += static_cast<int>(Aleatoire(0.01, 0.03).decimal() * vieMax()+ Aleatoire(0.03, 0.09).decimal() * vie()) ;
				equipeEnnemi().attaqueZone(DEGATS, this,C ,window, allSounds);
			}
		}
		
		ajouterMana(-1);
		break;
	case 2:
		if (floppy) {
			Affichage().dessinerTexte(nom() + " envoie des fleches ",window);
			for (int i = 0;i <3 && equipeEnnemi().estEnVie();i++) {
				Attaque(degats(0.5, 1.5), equipeEnnemi().plusFort(), C, window, allSounds);
			}
			if ( attaqueDouble()  && equipeEnnemi().estEnVie()) {
				for (int i = 0;i < 3 && equipeEnnemi().estEnVie();i++) {
					Attaque(degats(0.5, 1.5), equipeEnnemi().plusFort(), C, window, allSounds);
				}
			}
			ajouterMana(-2);
		}
		else {
			Affichage().dessinerTexte(nom() + " sert l'apero ",window);
			for (int i = 0;i < equipeAllier().taille();i++) {
				SOINS = soins(0.25, 0.50);
				soigner(SOINS, C, equipeAllier()[i], window);
			
			}
			if ((habile() && attaqueDouble()) || (vie() == vieMax() && equipeEnnemi().estEnVie())) {
				Affichage().dessinerTexte(nom() + " est fauché et fauche les ennemis ",window);
				DEGATS = degats(0.20, 0.60) + static_cast<int>(Aleatoire(0.6, 1.8).decimal() * vitesse());
				equipeEnnemi().attaqueZone(DEGATS, this,C ,window, allSounds);
			}
		}
	
		ajouterMana(-2);
		
		break;
	case 3:
		if (floppy) {
			Affichage().dessinerTexte(nom() + " Attque de la sainte trinité ! ",window);
			DEGATS = degats(0.33, 0.99)+degats(0.033,0.099,CHOIXVIEMAX)+degats(0.33,0.99,CHOIXVITESSE);
			Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		}
		else {
			Affichage().dessinerTexte(nom() + " fait du bilboquet et touche un ennemi ! ",window);
			DEGATS = degats(0.05, 3.5);
			Attaque(DEGATS, equipeEnnemi().aleatoireEnVie(), C, window, allSounds);
		}
	
		ajouterMana(-3);
		break;
	}
}

void Florian::passif(int tour, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (floppy && tour % 10 == 0) {
		status().ajouterCompteurRessurections();
	}
	else if ((tour + 1) % 10 == 0) {
		Affichage().dessinerTexte(nom() + " joue sa piece de théatre ! ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			equipeAllier()[i]->ajouterChanceDoubleAttaque(2);
			equipeAllier()[i]->ajouterChanceHabileter(2);
			equipeAllier()[i]->ajouterCoupCritique(2);
			equipeAllier()[i]->ajouterDegatsCritique(6);
			if (habile()) {
				equipeAllier()[i]->ajouterChanceDoubleAttaque(1);
				equipeAllier()[i]->ajouterChanceHabileter(1);
				equipeAllier()[i]->ajouterCoupCritique(1);
				equipeAllier()[i]->ajouterDegatsCritique(3);
			}
		}
	}
	if(floppy && !floppylegende){
		if (Aleatoire(0, 10001).entier() == 1) {
			floppylegende = true;
			setNom("The Legend of Floppiny");
			ajouterForce(3 * niveau());
			ajouterVieMax(30 * niveau());
			ajouterReduction(33);
			status().setReducteur(3 * niveau());
		}
		//1 chance sur 10 000 de devenir legendefloppy
		//changer nom
		//augmenter stats
	}
}

void Florian::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, Combat & C, int degats, Personnage* P)
{
	if (floppy) {
		if (habile()) {
			Affichage().dessinerTexte(nom() + " protege avec son bouclier ! ",window);
			status().ajouterCompteurProteger(1);
		}	
	}
	else {
		Affichage().dessinerTexte(nom() + " est protéger par jesus ! ",window);
		int SOINS = soins(0.2, 0.8);
		soigner(SOINS, C, this, window);
	}
}

