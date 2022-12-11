#include "Phenix.h"
#include "Affichage.h"
#include "Aleatoire.h"
Phenix::Phenix(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(16, E, O, A, Obj, "Malcolm", 1, 2, 4, 5, 3, 0, 0, 0, 2, 1)
{
	int un = 1;
	FILE* file = fopen("phstd.txt", "r");
	if (file == NULL) {
		std::ofstream os("phstd.txt", std::ios::binary);
		os.write((char*)&un, sizeof(un));
		//os << 1 << std::endl;
		os.close();
	}
	else {
		fclose(file);
	}
	std::ifstream is("phstd.txt", std::ios::binary);
	is.read((char*)&_stack, sizeof(_stack));
	if (_stack >= 1000000000) {
		_taille = 4;
	}
	else if (_stack >= 1000000) {
		_taille = 3;
	}
	else if (_stack >= 1000) {
		_taille = 2;
	}
	else {
		_taille = 1;
	}
	if (_taille == 4) {
		setNom("Ancien Phenix");
		ajouterForce(3 * niveau());
		ajouterVitesse(12 * niveau());
		ajouterVie((long long int)70 * niveau());
		ajouterReduction(30);
		ajouterChanceDoubleAttaque(15);
		ajouterChanceHabileter(27);
		ajouterChanceRicochet(8);
	}
	else if (_taille == 3) {
		setNom("Phénix Adulte");
		ajouterForce(2 * niveau());
		ajouterVitesse(8 * niveau());
		ajouterVie((long long int)30 * niveau());
		ajouterReduction(20);
		ajouterChanceDoubleAttaque(10);
		ajouterChanceHabileter(9);
		ajouterChanceRicochet(4);
	}
	else if (_taille == 2) {
		setNom("Jeune Phénix");
		ajouterForce(1 * niveau());
		ajouterVitesse(4 * niveau());
		ajouterVie((long long int)10 * niveau());
		ajouterReduction(10);
		ajouterChanceDoubleAttaque(5);
		ajouterChanceHabileter(3);
		ajouterChanceRicochet(2);
	}
	else {
		setNom("Bebe Phénix");
	}
	status().setReducteur(1 * niveau());
	status().setAdducteur(1 * niveau());
	
}

void Phenix::attaqueEnnemis(sf::RenderWindow* window)
{
	int choix = choixAttaque();
	int DEGATS;
	int SOINS;
	switch (choix) {

	case 0:
		Affichage().dessinerTexte(nom() + " Boule de feux ! ",window);
		for (int i = 1;i <= _taille;i++) {
			if (equipeEnnemi().estEnVie()) {
				DEGATS = degats(0.45, 0.85);
				Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
			}
		}
		if (attaqueDouble()) {
			for (int i = 1;i <= _taille;i++) {
				if (equipeEnnemi().estEnVie()) {
					DEGATS = degats(0.45, 0.85);
					Attaque(DEGATS, equipeEnnemi().plusProcheVivant(),window);
				}
			}
		}

		ajouterMana(1);
		break;
	case 1:
		status().soignerBrulure();
		status().soignerPoison();
		if (_taille >= 2) {
			Affichage().dessinerTexte(nom() + " Soins de phenix ! ",window);
			SOINS = soins(0.20 * (double)(_taille - 1), 0.40 * (double)(_taille - 1));
			equipeAllier().soignerZone(SOINS, this,window);
			if (attaqueDouble()) {
				SOINS = soins(0.20 * (_taille - 1), 0.40 * (_taille - 1));
				equipeAllier().soignerZone(SOINS, this,window);
			}
			ajouterMana(-1);
		}
		else {
			attaqueEnnemis(window);
		}

		break;
	case 2:
		if (_taille >= 3) {
			Affichage().dessinerTexte(nom() + " renforce le courage des allier !  ",window);
			for (int i = 0;i < equipeAllier().taille();i++) {
				equipeAllier()[i]->status().ajouterCompteurProteger(_taille * 2);
				equipeAllier()[i]->ajouterChanceDoubleAttaque(_taille);
				equipeAllier()[i]->ajouterChanceHabileter(_taille);
				equipeAllier()[i]->ajouterChanceRicochet(_taille / 2);
				equipeAllier()[i]->ajouterCoupCritique(_taille);
				equipeAllier()[i]->ajouterDegatsCritique(_taille * 2 + 2);
				equipeAllier()[i]->ajouterReduction(_taille / 2);
			}
			ajouterMana(-2);
		}
		else {
			attaqueEnnemis(window);
		}

		break;
		if (_taille == 4) {
			Affichage().dessinerTexte(nom() + " MAELSTROM !  ",window);
			DEGATS = (2.0, 4.0);
			equipeEnnemi().attaqueZone(DEGATS, this,window);
			ajouterMana(-3);
		}
		else {
			attaqueEnnemis(window);
		}
		break;
	}
}

void Phenix::passif(int tour, sf::RenderWindow* window)
{
	soigner((int)(vieMax() - vie()) / 10, this,window);
	bouclier((bouclierMax() - bouclier()) / 10, this,window);
	if (_stack < 2000000000) {
		_stack++;
	}
	sauvegarderCharge();
}

void Phenix::passifDefensif(sf::RenderWindow* window)
{
	if (equipeEnnemi().estEnVie()) {

		AttaqueBrut(degats(0.01 * _taille, 0.02 * _taille + 0.02), equipeEnnemi().plusProcheVivant(),window);
	}
}

void Phenix::sauvegarderCharge()
{
	int un = 1;
	std::ifstream is("phstd.txt", std::ios::binary);
	is.read((char*)&_stack, sizeof(_stack));
	is.close();
}

void Phenix::remettreAZero()
{
	_stack = 1;
	sauvegarderCharge();
}
