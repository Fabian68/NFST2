#include "Combat.h"
#include "Affichage.h"
#include "Experiences.h"
#include <iostream>
#include "Aleatoire.h"
#include "Delais.h"
#include "AffichageCombat.h"
#include "Succes.h"
#include "Lapin.h"
#include "Sanglier.h"

Combat::Combat(Equipes & Joueur, Equipes & Ia, Zones& Z, Animaux& A, Orbes& O, std::vector< sf::Sound >& allSounds) : _joueur{ Joueur }, _ia{ Ia }, _tour{ 0 }
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1200, 825), "Combat");
	if (!_backgroundTexture.loadFromFile("graphics/img1.png"))
	{
		// Erreur
		std::cout << "Erreur durant le chargement de l'image de background." << std::endl;
	}
	else {
		_background.setTexture(_backgroundTexture);
	}
		
	window->setActive();
	window->setFramerateLimit(1);

	int xp;
	xp = _ia.xpDonner();

	Delais delais = Delais();
	int del = 100;

	for (int i = 0;i < _joueur.taille();i++) {
		if (_joueur[i]->possedeObjetNumero(OBJET_AVANCE_RAPIDE)) {
			del = std::min(50, del);
		}
		if (_joueur[i]->possedeObjetNumero(OBJET_SABLIER)) {
			del = std::min(25, del);
		}
		if (_joueur[i]->possedeObjetNumero(OBJET_TARDIS)) {
			del = std::min(1, del);
		}
	}
	Succes S;
	if (S.estDebloque(SUCCES_10SUCCES)) {
		del = (int)((double)del * 0.75);
	}
	delais.setDelais(del);

	modifierQuiJoue();

	AffichageCombat AC;
	
	int nbFoisJouer = 0;

	AC.dessinerDeuxEquipes(_joueur, _ia, *this, window);
	
	while (_joueur.estEnVie() && _ia.estEnVie()) {
		for (int i = 0;i < (int)_quiJoue.size();i++) {
			_quiJoueIndex = i;
			if ((_joueur.estEnVie() && _ia.estEnVie())) {
				if (_quiJoue[i]->estEnVie()) {
					_quiJoue[i]->changeTour(true);
					nbFoisJouer++;			
					if (nbFoisJouer % _nbJouerPourAugmenterTour == 0) {
						_tour++;
						for (int t = 0; t < _joueur.taille(); t++) {
							if (_joueur.perso(t)->estEnVie()) {
								_joueur.perso(t)->passif(_tour,*this, window, allSounds);
								if (_joueur.perso(t)->possedeObjetNumero(OBJET_ANTIDOTE)) {
									_joueur.perso(t)->status().soignerPoison();
								}
								if (_joueur.perso(t)->possedeObjetNumero(OBJET_VOILE_FEU)) {
									_joueur.perso(t)->status().soignerBrulure();
								}
								if (_joueur.perso(t)->possedeObjetNumero(OBJET_MALEDICTION)) {
									_joueur.perso(t)->reduireVie(_joueur.perso(t)->vieMax() / 10);
									_joueur.perso(t)->reduireBouclier(_joueur.perso(t)->bouclierMax());
								}
								if (_joueur.perso(t)->possedeObjetNumero(OBJET_VASE_ANTIQUE_MAGIQUE)) {
									_joueur.perso(t)->ajouterMana(1);
								}
								_joueur.perso(t)->status().effetBrulure();
								_joueur.perso(t)->status().effetPoison();
							}
							else if (_joueur.perso(t)->id() == 16) {
								int un = 1;
								std::ifstream is("phstd.txt", std::ios::binary);
								is.read((char*)&un, sizeof(un));
								is.close();
							}
							if (_joueur.perso(t)->id() == 3 && _joueur.perso(t)->estEnVie() && _tour == 25) {
								Personnage* L = new Lapin(_joueur.perso(t)->niveau(), "Perle", 0, 9, 5, 21);
								L->ajouterVie(_joueur.perso(t)->vieMax() / 10);
								L->ajouterForce(_joueur.perso(t)->force() / 10);
								L->ajouterVitesse(_joueur.perso(t)->vitesse() / 10);
								_joueur.ajouterPerso(L);
								_joueur.setAllierEtEnnemis(_ia);
								_ia.setAllierEtEnnemis(_joueur);
							}
							if (_joueur.perso(t)->id() == 3 && _joueur.perso(t)->estEnVie() && _tour == 50) {
								Personnage* S = new Sanglier(_joueur.perso(t)->niveau(), "Oxanne", 0, 9, 5, 22);
								S->ajouterVie(_joueur.perso(t)->vieMax() / 10);
								S->ajouterForce(_joueur.perso(t)->force() / 10);
								S->ajouterVitesse(_joueur.perso(t)->vitesse() / 10);
								_joueur.ajouterPerso(S);
								_joueur.setAllierEtEnnemis(_ia);
								_ia.setAllierEtEnnemis(_joueur);
							}
						}
						for (int k = 0; k < _ia.taille(); k++) {
							if (_ia.perso(k)->estEnVie()) {
								_ia.perso(k)->passif(_tour,*this, window, allSounds);
								if (_ia.perso(k)->possedeObjetNumero(OBJET_ANTIDOTE)) {
									_ia.perso(k)->status().soignerPoison();
								}
								if (_ia.perso(k)->possedeObjetNumero(OBJET_VOILE_FEU)) {
									_ia.perso(k)->status().soignerBrulure();
								}
								if (_ia.perso(k)->possedeObjetNumero(OBJET_VASE_ANTIQUE_MAGIQUE)) {
									_ia.perso(k)->ajouterMana(1);
								}
								_ia.perso(k)->status().effetBrulure();
								_ia.perso(k)->status().effetPoison();
							}
						}

						//AffichageCombat().dessinerDeuxEquipes(_joueur, _ia,window);
					}
					_quiJoue[i]->attaqueEnnemis(*this,window, allSounds);
					_quiJoue[i]->changeTour(false);
				}
			}
		}
		modifierQuiJoue();
	}
	if (_joueur.estEnVie()) {
		Z.niveauBattu();
		Experiences E;

		_joueur.ajouterExperience(xp, E);
		Succes succes;
		int niveau_actuel = Z.niveauActuel();
		int succes_id = -1;
		switch (niveau_actuel) {
		case 1:
			succes_id = SUCCES_NIV1;
			break;
		case 5:
			succes_id = SUCCES_NIV5;
			break;
		case 10:
			succes_id = SUCCES_NIV10;
			break;
		case 15:
			succes_id = SUCCES_NIV15;
			break;
		case 20:
			succes_id = SUCCES_NIV20;
			break;
		case 25:
			succes_id = SUCCES_NIV25;
			break;
		};
		if (succes_id >= 0 && !succes.estDebloque(succes_id)) {
			succes.debloquerSucces(succes_id);
			succes.affichageDeblocageSucces(succes_id, allSounds);
		}


		tirageRecompenses(Z, A, O, window, allSounds);
	}
	window->close();
}

void Combat::modifierQuiJoue() {
	_quiJoue.resize(0);
	int somme = 0;
	int nombrePersonnages = _joueur.taille() + _ia.taille();
	int nombrePersoEnVie = _joueur.nbEnVie() + _ia.nbEnVie();
	_nbJouerPourAugmenterTour = nombrePersonnages / 2;
	_quiJoue.reserve(nombrePersoEnVie);
	int max = INT_MIN;
	std::vector<int> nombreTourJoueur(_joueur.taille());
	std::vector<int> nombreTourIa(_ia.taille());

	int somme_vitesses_joueur = 0;
	for (int i = 0;i < _joueur.taille();i++) {
		if (_joueur[i]->estEnVie()) {
			somme_vitesses_joueur += _joueur[i]->vitesse();
		}
	}

	int somme_vitesse_ia = 0;
	for (int i = 0;i < _ia.taille();i++) {
		if (_ia[i]->estEnVie()) {
			somme_vitesse_ia += _ia[i]->vitesse();
		}
	}
	somme = somme_vitesses_joueur + somme_vitesse_ia;
	int moyenne = static_cast<int>(somme / (nombrePersoEnVie * 1.0));
	for (int i = 0;i < _joueur.taille();i++) {
		if (_joueur[i]->estEnVie()) {
			nombreTourJoueur[i] = ceil(((double)_joueur[i]->vitesse()) / ((double)moyenne));
			if (nombreTourJoueur[i] > max) {
				max = nombreTourJoueur[i];
			}
		}
	}

	for (int i = 0;i < _ia.taille();i++) {
		if (_ia[i]->estEnVie()) {
			nombreTourIa[i] = ceil(((double)_ia[i]->vitesse()) / ((double)moyenne));
			if (nombreTourIa[i] > max) {
				max = nombreTourIa[i];
			}
		}
	}
	if (somme_vitesses_joueur > somme_vitesse_ia) {
		for (int j = max;j > 0;j--) {
			for (int i = 0;i < _joueur.taille();i++) {
				if (_joueur[i]->estEnVie()) {
					if (nombreTourJoueur[i] >= j) {
						_quiJoue.push_back(_joueur[i]);
					}
				}
			}
			for (int i = 0;i < _ia.taille();i++) {
				if (_ia[i]->estEnVie()) {
					if (nombreTourIa[i] >= j) {
						_quiJoue.push_back(_ia[i]);
					}
				}
			}
		}
	}
	else {
		for (int j = max;j > 0;j--) {
			for (int i = 0;i < _ia.taille();i++) {
				if (_ia[i]->estEnVie()) {
					if (nombreTourIa[i] >= j) {
						_quiJoue.push_back(_ia[i]);
					}
				}
			}

			for (int i = 0;i < _joueur.taille();i++) {
				if (_joueur[i]->estEnVie()) {
					if (nombreTourJoueur[i] >= j) {
						_quiJoue.push_back(_joueur[i]);
					}
				}
			}
		}
	}
}
void Combat::tirageRecompenses(Zones Z, Animaux A, Orbes O, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) {
	int indiceJoueur;

	int chanceTirage;
	//Pour chaque perso
	for (int i = 0; i < _joueur.taille(); i++) {
		//Pour chaque animal
		indiceJoueur = _joueur[i]->id();
		for (int j = 0; j < 9; j++) {
			//Pour chaque rarete animal
			chanceTirage = 10000 + 90000 - 900 * Z.niveauActuel() - 90 * Z.niveauMax();
			for (int k = 1; k <= 5; k++) {
				if (Aleatoire(0, chanceTirage).entier() == 1) {
					if (!A.animalDebloquer(indiceJoueur, j, k)) {
						A.deblocageAnimal(indiceJoueur, j, k, _joueur[i]->nom(), window, allSounds);
					}
				}
				//detecting overflow
				if (chanceTirage > (int)(INT_MAX / 10.0 - 1)) {
					chanceTirage = INT_MAX;

					//std::cout << "Overflow possible loot animal";
				}
				else {
					chanceTirage *= 10;
				}
			
				//chanceTirage = max(chanceTirage * 10,chanceTirage); nope
			}
			
		}
		//Pour chaque rareter d'orbe

		chanceTirage = 1000 + 9000 - 90 * Z.niveauActuel() - 9 * Z.niveauMax();
		for (int j = 1; j <= 5; j++) {
			if (Aleatoire(0, chanceTirage).entier() == 1) {
				if (!O.orbeDebloquer(indiceJoueur, j)) {
					O.deblocageOrbe(indiceJoueur, j, _joueur[i]->nom(), window, allSounds);
				}
			}
			if (chanceTirage > (int)(INT_MAX / 10.0 - 1)) {
				//std::cout << "Overflow possible loot orbe" << std::endl;
			}
			chanceTirage *= 10;

		}
	}

	Objets obj;
	std::vector<Objet> objets = obj.objetsDuNiveau(Z.niveauActuel());
	for (int i = 0;i < (int)objets.size();i++) {
		if (!obj.estDebloquer(objets[i])) {
			if (objets[i].numero() == 34) {
				if (_joueur.comprendPersonnage(1) && Aleatoire(0, objets[i].rareter() + 1).entier() == 1) {
					obj.deblocageObjet(objets[i].numero(), window, allSounds);
				}
			}
			else if (Aleatoire(0, objets[i].rareter() + 1).entier() == 1) {
				obj.deblocageObjet(objets[i].numero(), window, allSounds);
			}
		}
	}
}
Combat::~Combat()
{
}

sf::Sprite Combat::fond()const {
	return _background;
}
int Combat::tour() const
{
	return _tour;
}

std::vector<Personnage*> Combat::quiJoue() const
{
	return _quiJoue;
}

int Combat::quiJoueIndex() const
{
	return _quiJoueIndex;
}



/*
void InitQuiJoue(){
	long long int somme = 0;
	for(int i=PREMIER;i<=CINQUIEME;i++) {
		somme+=PersoCarac[Equipe[TEAM1][i]][AGILITE];
		somme+=PersoCarac[Equipe[TEAM2][i]][AGILITE];
	}
	int Ratio[10];
	for(int i=0;i<=4;i++) {
		Ratio[i]=static_cast<int>(PersoCarac[Equipe[TEAM1][i]][AGILITE]/(1.0*somme/12));
		Ratio[i+5]=static_cast<int>(PersoCarac[Equipe[TEAM2][i]][AGILITE]/(1.0*somme/12));
	}

  for(double i=0.9;i>-0.1;i=i-0.1) {
	for(int j=0;j<=4;j++) {
		if(Ratio[j]>=i) {
			QuiJoue.push_back(Equipe[TEAM1][j]);
		  }
		if(Ratio[j+5]>=i) {
			QuiJoue.push_back(Equipe[TEAM2][j]);
		  }
	  }

  }
}
*/

