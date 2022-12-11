
#include "Point.h"
#include <ctime>
#include <cstdlib>
#include "Combat.h"
#include "Aleatoire.h"
#include "Fabian.h"
#include "Nicolas.h"
#include "Thomas.h"
#include "Lapin.h"
#include "Experiences.h"
#include "Zones.h"
#include "Animaux.h"
#include <iostream>
#include "Affichage.h"
#include "Bouton.h"
#include "Fiona.h"
#include "Moustick.h"
#include "Bryan.h"
#include "David.h"
#include "Isidore.h"
#include "Sebastien.h"
#include "Cloe.h"
#include "Amine.h"
#include "Florian.h"
#include "JeanBaptiste.h"
#include "Maelle.h"
#include "Tortue.h"
#include "Salim.h"
#include "Conseils.h"
#include <SFML/Audio.hpp>
#include"AffichageCombat.h"
#define PI 3.14159265

void reinitListeEquipe(Equipes& Liste) {
	Experiences E;
	Orbes O;
	Animaux A;
	Objets Obj;
	Zones Z;
	Liste.liberer();

	Liste.ajouterPerso(new Fabian(E, O, A, Obj));
	Liste.ajouterPerso(new Nicolas(E, O, A, Obj));
	Liste.ajouterPerso(new Thomas(E, O, A, Obj));
	Liste.ajouterPerso(new Fiona(E, O, A, Obj));
	Liste.ajouterPerso(new Moustick(E, O, A, Obj));
	Liste.ajouterPerso(new Bryan(E, O, A, Obj));
	Liste.ajouterPerso(new David(E, O, A, Obj));
	Liste.ajouterPerso(new Isidore(E, O, A, Obj));
	Liste.ajouterPerso(new Sebastien(E, O, A, Obj));
	Liste.ajouterPerso(new Cloe(E, O, A, Obj));
	Liste.ajouterPerso(new Amine(E, O, A, Obj));
	Liste.ajouterPerso(new Florian(E, O, A, Obj));
	Liste.ajouterPerso(new JeanBaptiste(E, O, A, Obj));
	Liste.ajouterPerso(new Maelle(E, O, A, Obj));
	Liste.ajouterPerso(new Tortue(E, O, A, Obj));
	Liste.ajouterPerso(new Salim(E, O, A, Obj));
}

void reinitEquipe(Equipes& monEquipe, Equipes& ListePerso) {
	monEquipe.vider();
	monEquipe.chargerEquipe(ListePerso);
}
int main()
{
	srand(time(0));

	sf::Music buffer;
	if (!buffer.openFromFile("dry-fart.ogg")) {
		std::cout << "Son fonctionne pas" << std::endl;
	}
	else {
		//buffer.setLoop(true);
		buffer.play();
		std::cout << "Son fonctionne " << std::endl;
	}
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1200, 800), "My window");
	(*window).setActive(true);
	//(*window).setVerticalSyncEnabled(true);
	//(*window).setFramerateLimit(10);
	//(* window).setFramerateLimit(60);
	//(* window).display();

	Equipes  Gentil(false);
	Equipes choix(false);
	Equipes Meuchant(true);
	Conseils C;
	
	Bouton modifierEquipe(500.f, 50.f, "Modifier equipe");
	Bouton AfficherJoueurs(500.f, 100.f, "AfficherJoueurs");
	Bouton AfficherAnimaux(500.f, 150.f, "AfficherAnimaux");
	Bouton Jouer(500.f, 200.f, "Jouer");
	Bouton Secret(900.f, 700.f, "Boing");
	Bouton Conseil(100.f, 300.f, C.conseilAleatoire());
	
	float x, y;
	sf::Color couleurTexte = sf::Color::White;
	sf::Color couleurFond = sf::Color::Black;
	Affichage H;
	while ((* window).isOpen()) {
		
		Zones Z;
		Orbes O;
		Animaux A;
		Objets Obj;
		
		H.dessinerTexte("Version 4.0 ", window);

		Meuchant.liberer();
		reinitListeEquipe(choix);
		reinitEquipe(Gentil, choix);
		modifierEquipe.afficher(window);
		AfficherJoueurs.afficher(window);
		AfficherAnimaux.afficher(window);
		Conseil.afficher(window);

		if (Gentil.taille() > 0) {
			Jouer.afficher(window);
		}
		else {
			H.afficherTexte(250.f, 400.f, "Modifier votre equipe pour pouvoir jouer ! ", couleurTexte, window);
		}
		sf::Event event;
		
		while ((* window).pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition((*window));
				x = (float)position.x;
				y = (float)position.y;
				std::cout << '(' << x << ',' << y << ')' << std::endl;

				if (AfficherJoueurs.comprendLesCoord(x, y)) {
					(*window).clear();
					H.afficherJoueurs(0, choix, window);
				}
				else if (AfficherAnimaux.comprendLesCoord(x, y)) {
					(*window).clear();
					H.afficherAnimaux(A, window);
				}
				else if (Jouer.comprendLesCoord(x, y) && Gentil.taille() > 0) {
					(*window).clear();
					int niveauChoisit = Z.niveauActuel();
					int repetition = 1;
					H.choixNiveau(Z, Obj, niveauChoisit, repetition, window);
					Z.choixNiveau(niveauChoisit);
				
					for (int i = 0; i < repetition; i++) {
						Orbes O;
						Animaux A;
						Meuchant.liberer();
						reinitListeEquipe(choix);
						reinitEquipe(Gentil, choix);
						Z.equipeEnZone(Z.niveauActuel(), Meuchant);
						Gentil.setAllierEtEnnemis(Meuchant);
						Meuchant.setAllierEtEnnemis(Gentil);
						Combat C(Gentil, Meuchant, Z, A, O, window);
						//(*window).display();
						//(*window).clear();
					}	
					(*window).display();
					(*window).clear();
					Bouton Continuer(500, 700, "Continuer");
					Continuer.afficher(window);
					AffichageCombat H2;
					H2.afficherStats(Gentil, window);
				
					(*window).display();
					do {
						while ((*window).pollEvent(event))
						{
							if (event.type == sf::Event::MouseButtonPressed) {
								sf::Vector2i position = sf::Mouse::getPosition((*window));
								x = (float)position.x;
								y = (float)position.y;
								std::cout << '(' << x << ',' << y << ')' << std::endl;
							}
						}
					} while (!Continuer.comprendLesCoord(x, y));

					(*window).display();
					(*window).clear();
				
					//afficherstats
				}
				else if (modifierEquipe.comprendLesCoord(x, y)) {
					(*window).clear();
					H.menuModifierEquipe(Gentil, choix, Z.nbPersoJouable() - Gentil.taille(), window);
					
				}
				else if (Secret.comprendLesCoord(x, y)) {
					H.afficherTexte(Aleatoire(20, 1100).entier(), Aleatoire(20, 700).entier(), "BOING", sf::Color::Red, window);
				}
			}
		}
		//(*window).clear();
		(*window).display();
	}

	return 0;
}

