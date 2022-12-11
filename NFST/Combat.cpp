#include "Combat.h"
#include "Affichage.h"
#include "Experiences.h"
#include <iostream>
#include "Aleatoire.h"
#include "Delais.h"
#include "AffichageCombat.h"


Combat::Combat(Equipes  & Joueur, Equipes  & Ia,Zones & Z,Animaux & A,Orbes & O, sf::RenderWindow* window) : _joueur{Joueur}, _ia{Ia},_tour{0}
{


	/*for (int i = 0;i < _joueur.taille();i++) {
		_joueur[i]->appliquerEffets();
	}*/

	int somme = 0;
	int max = INT_MIN;
	int nombrePersonnages = _joueur.taille() + _ia.taille();
	std::cout << nombrePersonnages << " ";
	int xp;
	xp = _ia.xpDonner();
	std::vector<int> nombreTourJoueur(_joueur.taille());
	std::vector<int> nombreTourIa(_ia.taille());
	Delais delais = Delais();
	int del = 50;
	
	for (int i = 0;i < _joueur.taille();i++) {
		somme += _joueur.perso(i)->vitesse();
		if (_joueur.perso(i)->possedeObjetNumero(33)) {
			del = std::min(25, del);
		}
		if (_joueur.perso(i)->possedeObjetNumero(34)) {
			del = std::min(0, del);
		}
	}
	delais.setDelais(del);

	for (int i = 0;i < _ia.taille();i++) {
		somme += _ia.perso(i)->vitesse();
	}
	int moyenne = static_cast<int>(somme / (nombrePersonnages*1.0));
	std::cout << moyenne << " ";
	for (int i = 0;i < _joueur.taille();i++) {
		nombreTourJoueur[i] = ceil(((double)_joueur.perso(i)->vitesse()) / ((double)moyenne));
		if (nombreTourJoueur[i] > max) {
			max = nombreTourJoueur[i];
		}
	}
	
	for (int i = 0;i < _ia.taille();i++) {
		nombreTourIa[i] = ceil(((double)_ia.perso(i)->vitesse()) / ((double)moyenne));
		if (nombreTourIa[i] > max) {
			max = nombreTourIa[i];
		}
	}
	std::cout << max << " ";
	for (int j = max;j > 0;j--) {
		for (int i = 0;i < _joueur.taille();i++) {
			if (nombreTourJoueur[i] >= j) {
				_quiJoue.push_back(_joueur.perso(i));
			}
		}
		for (int i = 0;i < _ia.taille();i++) {
			if (nombreTourIa[i] >= j) {
				_quiJoue.push_back(_ia.perso(i));
			}
		}
	}
	AffichageCombat AC;
	AC.dessinerDeuxEquipes(_joueur, _ia,window);
	int nbFoisJouer = 0;
	int nbJouerPourAugmenterTour = nombrePersonnages / 2;

	//AC.afficherTour quand dessiner deux equipes
	//AC.mettreAjour tour
	Affichage().affichageTexte(5, 5, "Tour : " + std::to_string(_tour + 1),sf::Color::Magenta,window);
	while (_joueur.estEnVie() && _ia.estEnVie()) {
		for (int i = 0;i < (int)_quiJoue.size();i++) {
			if ((_joueur.estEnVie() && _ia.estEnVie())) {
					if (_quiJoue[i]->estEnVie()) {
						nbFoisJouer++;
						nombrePersonnages = _joueur.nbEnVie() + _ia.nbEnVie();
						nbJouerPourAugmenterTour = nombrePersonnages / 2;
						if (nbFoisJouer%nbJouerPourAugmenterTour == 0) {
							_tour++;
							//AC.mettreAjour tour
							Affichage().affichageTexte(5, 3, "Tour : " + std::to_string(_tour+1),sf::Color::Magenta,window);
							for (int i = 0; i < _joueur.taille(); i++) {
								if (_joueur[i]->estEnVie()) {
									_joueur[i]->passif(_tour,window);
									if (_joueur[i]->possedeObjetNumero(1)) {
										_joueur[i]->status().soignerPoison();
									}
									if (_joueur[i]->possedeObjetNumero(2)) {
										_joueur[i]->status().soignerBrulure();
									}
									if (_joueur[i]->possedeObjetNumero(5)) {
										_joueur[i]->reduireVie(_joueur[i]->vieMax() /10);
										_joueur[i]->reduireBouclier(_joueur[i]->bouclierMax());
									}
									_joueur[i]->status().effetBrulure();
									_joueur[i]->status().effetPoison();
								}
								else if (_joueur[i]->id() == 16) {
									int un = 1;
									std::ifstream is("phstd.txt", std::ios::binary);
									is.read((char*)&un, sizeof(un));
									is.close();
								}
							}
							for (int i = 0; i < _ia.taille(); i++) {
								if (_ia[i]->estEnVie()) {
									_ia[i]->passif(_tour,window);
									if (_ia[i]->possedeObjetNumero(1)) {
										_ia[i]->status().soignerPoison();
									}
									if (_ia[i]->possedeObjetNumero(2)) {
										_ia[i]->status().soignerBrulure();
									}
									_ia[i]->status().effetBrulure();
									_ia[i]->status().effetPoison();
								}
							}
							
							//AffichageCombat().dessinerDeuxEquipes(_joueur, _ia,window);
						}
						_quiJoue[i]->attaqueEnnemis(window);
					}
			}
		}
	}
	if (_joueur.estEnVie()) {
		Z.niveauBattu();
		Experiences E;
		
		_joueur.ajouterExperience(xp, E);
		tirageRecompenses(Z, A, O, window);
	}
	//Affichage().dessinerDeuxEquipes(_joueur, _ia,window);
	
}

void Combat::tirageRecompenses(Zones Z,Animaux A,Orbes O, sf::RenderWindow* window) {
	int indiceJoueur;

	int chanceTirage;
	//Pour chaque perso
	for (int i = 0; i < _joueur.taille(); i++) {
		//Pour chaque animal
		indiceJoueur = _joueur[i]->id();
		for (int j = 0; j < 9; j++) {
			//Pour chaque rarete animal
			chanceTirage = 10000 +90000 - 900 * Z.niveauActuel() - 90 * Z.niveauMax();
			for (int k = 1; k <= 5; k++) {
				if (Aleatoire(0, chanceTirage).entier() ==1) {
					if (!A.animalDebloquer(indiceJoueur, j, k)) {
						A.deblocageAnimal(indiceJoueur, j, k, _joueur[i]->nom(),window);
					}
				}
				//detecting overflow
				if (chanceTirage > (int)(INT_MAX / 10.0 -1)) {
					chanceTirage = INT_MAX;
				
					//std::cout << "Overflow possible loot animal";
				}
				else {
					chanceTirage *= 10;
				}
				std::cout << " " << chanceTirage;
				//chanceTirage = max(chanceTirage * 10,chanceTirage); nope
			}
			std::cout << std::endl;
		}
		//Pour chaque rareter d'orbe

		chanceTirage = 1000 + 9000 - 90 * Z.niveauActuel()-9*Z.niveauMax();
		for (int j = 1; j <= 5; j++) {
			if (Aleatoire(0, chanceTirage).entier() == 1) {
				if (!O.orbeDebloquer(indiceJoueur,j)) {
					O.deblocageOrbe(indiceJoueur, j, _joueur[i]->nom(),window);
				}
			}
			if (chanceTirage > (int)(INT_MAX / 10.0 -1)) {
				//std::cout << "Overflow possible loot orbe" << std::endl;
			}
			chanceTirage *= 10; 
			
		}
	}
	
	Objets obj;
	std::vector<Objet> objets= obj.objetsDuNiveau(Z.niveauActuel());
	for (int i = 0;i<(int)objets.size();i++) {
		if (!obj.estDebloquer(objets[i])) {
			if (objets[i].numero() == 34 ) {
				if (_joueur.comprendPersonnage(1) && Aleatoire(0, objets[i].rareter() + 1).entier() == 1) {
					obj.deblocageObjet(objets[i].numero(),window);
				}
			}
			else if (Aleatoire(0, objets[i].rareter() + 1).entier()==1) {
				obj.deblocageObjet(objets[i].numero(),window);
			}
		}
	}
}
Combat::~Combat()
{
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

