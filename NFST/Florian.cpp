#include "Florian.h"
#include "Affichage.h"
#include "Aleatoire.h"

Florian::Florian(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(11, E, O, A, Obj, "Florian", 6, 3, 1, 20, 20, 20, 0, 0, 0, 0) {

	floppy = false;
	floppylegende = false;
	if (possedeObjetNumero(32)) {
		floppy = true;
	}
	//si possede obj 32
	if (floppy == true) {
		setNom("Floppy");
		ajouterChanceHabileter(10);
		ajouterVitesse(3 * niveau());
		ajouterEsquive(20);
	}
}

void Florian::attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	
	switch (choix) {

	case 0:
		if (floppy == true) {
			Affichage().dessinerTexte(nom() + " coup épée ",window);
			Attaque(force(), equipeEnnemi().plusProcheVivant(),window,allSounds);
			if ((attaqueDouble() && equipeEnnemi().estEnVie())) {
				Attaque(force(), equipeEnnemi().plusProcheVivant(),window,allSounds);
			}
		}
		else {
			SOINS = degats(0.25, 0.75);
			Affichage().dessinerTexte(nom() + " se détend ",window);
			bouclier(SOINS, this,window);

			if ((attaqueDouble() && equipeEnnemi().estEnVie()) || (vie() == vieMax() && equipeEnnemi().estEnVie())) {

				Affichage().dessinerTexte(nom() + " se trompe ",window);
				DEGATS = degats(0.37, 1.37);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window,allSounds);
				ajouterMana(-2);
			}
			
		}
		ajouterMana(3);
		break;
	case 1:
		if (floppy) {
			Affichage().dessinerTexte(nom() + " envoie une bombe",window);
			equipeEnnemi().attaqueZone(2 * force(), this,window,allSounds);
			ajouterMana(-4);
		}
		else {
			Affichage().dessinerTexte(nom() + " bois un coup",window);

			SOINS = degats(0.75, 1.75);
			soigner(SOINS, this,window);

			if ((habile() && equipeEnnemi().estEnVie())|| (vie() == vieMax() && equipeEnnemi().estEnVie())) {
				Affichage().dessinerTexte(nom() + " rote ",window);
				DEGATS = degats(0.15, 0.25);
				DEGATS += static_cast<int>(Aleatoire(0.02, 0.07).decimal() * vieMax()+ Aleatoire(0.04, 0.14).decimal() * vie()) ;
				equipeEnnemi().attaqueZone(DEGATS, this,window,allSounds);
				ajouterMana(-4);
			}
		}
		
		ajouterMana(3);
		break;
	case 2:
		if (floppy) {
			Affichage().dessinerTexte(nom() + " envoie des fleches ",window);
			for (int i = 0;i <3 && equipeEnnemi().estEnVie();i++) {
				if (habile()) {
					Attaque(degats(1.0, 3.0), equipeEnnemi().plusFort(),window,allSounds);
				}
				else {
					Attaque(degats(0.5, 1.5), equipeEnnemi().plusFort(),window,allSounds);
				}
			}
			if ( attaqueDouble()  && equipeEnnemi().estEnVie()) {
				for (int i = 0;i < 3 && equipeEnnemi().estEnVie();i++) {
					if (habile()) {
						Attaque(degats(1.0, 3.0), equipeEnnemi().plusFort(),window,allSounds);
					}
					else {
						Attaque(degats(0.5, 1.5), equipeEnnemi().plusFort(),window,allSounds);
					}
				}
			}
			ajouterMana(-3);
		}
		else {
			Affichage().dessinerTexte(nom() + " sert l'apero ",window);
			for (int i = 0;i < equipeAllier().taille();i++) {
				SOINS = soins(0.33, 0.99);
				soigner(SOINS, equipeAllier()[i],window);
			
			}
			if ((habile() && attaqueDouble()) || (vie() == vieMax() && equipeEnnemi().estEnVie())) {
				Affichage().dessinerTexte(nom() + " est fauché et fauche les ennemis ",window);
				DEGATS = degats(0.20, 0.60) + static_cast<int>(Aleatoire(0.6, 2.6).decimal() * vitesse());
				equipeEnnemi().attaqueZone(DEGATS, this,window,allSounds);
				ajouterMana(-2);
			}
		}
	
		ajouterMana(1);
		
		break;
	case 3:
		if (floppy) {
			Affichage().dessinerTexte(nom() + " Attque de la sainte trinité ! ",window);
			DEGATS = degats(0.3, 3.0)+degats(0.03,0.3,CHOIXVIEMAX)+degats(0.3,3.0,CHOIXVITESSE);
			Attaque(DEGATS, equipeEnnemi().plusFaible(),window,allSounds);
		}
		else {
			Affichage().dessinerTexte(nom() + " fait du bilboquet et touche un ennemi ! ",window);
			DEGATS = degats(0.65, 6.5);
			Attaque(DEGATS, equipeEnnemi().aleatoireEnVie(),window,allSounds);
		}
	
		ajouterMana(-3);
		break;
	}
}

void Florian::passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	if (floppy && tour % 10 == 0) {
		status().ajouterCompteurRessurections();
	}
	if ((tour + 1) % 20 == 0) {
		Affichage().dessinerTexte(nom() + " joue sa piece de théatre ! ",window);
		for (int i = 0;i < equipeAllier().taille();i++) {
			equipeAllier()[i]->ajouterChanceDoubleAttaque(5);
			equipeAllier()[i]->ajouterChanceHabileter(5);
			equipeAllier()[i]->ajouterCoupCritique(5);
			equipeAllier()[i]->ajouterDegatsCritique(10);
			if (habile()) {
				equipeAllier()[i]->ajouterChanceDoubleAttaque(3);
				equipeAllier()[i]->ajouterChanceHabileter(3);
				equipeAllier()[i]->ajouterCoupCritique(3);
				equipeAllier()[i]->ajouterDegatsCritique(10);
			}
			if (attaqueDouble()) {
				equipeAllier()[i]->ajouterChanceDoubleAttaque(3);
				equipeAllier()[i]->ajouterChanceHabileter(3);
				equipeAllier()[i]->ajouterCoupCritique(3);
				equipeAllier()[i]->ajouterDegatsCritique(10);
				
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

void Florian::passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int degats, Personnage* P)
{
	if (floppy) {
		if (habile()) {
			Affichage().dessinerTexte(nom() + " protege avec son bouclier ! ",window);
			status().ajouterCompteurProteger(1);
		}
		
	}
	else {
		Affichage().dessinerTexte(nom() + " est protéger par jesus ! ",window);
		int SOINS = soins(0.2, 2.0);
		soigner(SOINS, this,window);
	}
}

