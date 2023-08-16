
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
#include "Succes.h"
#include "Phenix.h"
#define PI 3.14159265
#include<memory>


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
	Liste.ajouterPerso(new Phenix(E, O, A, Obj));
}

void reinitEquipe(Equipes& monEquipe, Equipes& ListePerso) {
	monEquipe.vider();
	monEquipe.chargerEquipe(ListePerso);
}

void loadSongs2(std::vector<std::shared_ptr<sf::SoundBuffer>>& allBuffers, std::vector<sf::Sound>& sounds) {
	// Charger les buffers et les stocker dans allBuffers
	std::shared_ptr<sf::SoundBuffer> buffer1 = std::make_shared<sf::SoundBuffer>();
	buffer1->loadFromFile("./song/giga-chad.ogg");
	allBuffers.push_back(buffer1);

	std::shared_ptr<sf::SoundBuffer> buffer2 = std::make_shared<sf::SoundBuffer>();
	buffer2->loadFromFile("./song/vine-boom.ogg");
	allBuffers.push_back(buffer2);

	std::shared_ptr<sf::SoundBuffer> buffer3 = std::make_shared<sf::SoundBuffer>();
	buffer3->loadFromFile("./song/bow_shoot.ogg");
	allBuffers.push_back(buffer3);

	// Créer les objets sf::Sound en utilisant les buffers stockés dans allBuffers
	sounds.push_back(sf::Sound(*buffer1));
	sounds.push_back(sf::Sound(*buffer2));
	sounds.push_back(sf::Sound(*buffer3));
}

void jouer(sf::RenderWindow* window,Zones & Z,Objets Obj, std::vector<sf::Sound>& allSounds, Affichage & H, Equipes & Meuchant, Equipes & Gentil,Equipes & choix) {
	(*window).clear();
	int niveauChoisit = Z.niveauActuel();
	int repetition = 1;
	H.choixNiveau(Z, Obj, niveauChoisit, repetition, window, allSounds);
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
		Combat C(Gentil, Meuchant, Z, A, O, allSounds);
	}
	
	Bouton Continuer(500, 700, "Continuer");
	Continuer.afficher(window);
	AffichageCombat H2;
	H2.afficherStats(Gentil, window);
	(*window).display();
	sf::Event event;
	float x=0.0, y=0.0;
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
	} while (!Continuer.comprendLesCoord(x, y, allSounds));
	(*window).display();
	(*window).clear();
}
int main()
{
	srand(time(0));

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1200, 800), "My window");

	std::vector<std::shared_ptr<sf::SoundBuffer>> allBuffers2;
	std::vector<sf::Sound> allSounds;

	loadSongs2(allBuffers2, allSounds);
	
	(*window).setActive(true);

	Equipes Gentil(false);
	Equipes choix(false);
	Equipes Meuchant(true);
	Conseils C;
	
	Bouton modifierEquipe(500.f, 50.f, "Modifier equipe");
	Bouton AfficherJoueurs(500.f, 100.f, "AfficherJoueurs");
	Bouton AfficherCompetences(500.f, 150.f, "AfficherCompetences");
	Bouton AfficherAnimaux(500.f, 200.f, "AfficherAnimaux");
	Bouton AfficherMecaniques(500.f, 250.f, "AfficherMecaniques");
	Bouton AfficherSucces(500.f, 300.f, "Succes");
	Bouton Jouer(500.f, 350.f, "Jouer");
	Bouton Secret(900.f, 700.f, "Boing");
	Bouton Conseil(150.f, 500.f, C.conseilAleatoire());
	
	float x, y;
	sf::Color couleurTexte = sf::Color::White;
	sf::Color couleurFond = sf::Color::Black;
	Affichage H;
	while ((* window).isOpen()) {
		Zones Z;
		Orbes O;
		Animaux A;
		Objets Obj;
		Succes S;
		
		H.dessinerTexte("Version 4.0 ", window);

		Meuchant.liberer();
		reinitListeEquipe(choix);
		reinitEquipe(Gentil, choix);
		modifierEquipe.afficher(window);
		AfficherJoueurs.afficher(window);
		AfficherCompetences.afficher(window);
		AfficherAnimaux.afficher(window);
		AfficherMecaniques.afficher(window);
		AfficherSucces.afficher(window);
		Conseil.afficher(window);

		if (!S.estDebloque(SUCCES_NIV25_FIONA) && choix[3]->niveau()>= 25) {
			S.debloquerSucces(SUCCES_NIV25_FIONA);
			S.affichageDeblocageSucces(SUCCES_NIV25_FIONA, allSounds);
		}
		if (!S.estDebloque(SUCCES_NIV25_NICOLAS) && choix[1]->niveau() >= 25) {
			S.debloquerSucces(SUCCES_NIV25_NICOLAS);
			S.affichageDeblocageSucces(SUCCES_NIV25_NICOLAS, allSounds);
		}

		if (!S.estDebloque(SUCCES_NIV10_FABIAN_FIONA) && choix[3]->niveau() >= 10 && choix[0]->niveau()>=10) {
			S.debloquerSucces(SUCCES_NIV10_FABIAN_FIONA);
			S.affichageDeblocageSucces(SUCCES_NIV10_FABIAN_FIONA, allSounds);
		}
		if (!S.estDebloque(SUCCES_NIV25_FABIAN_FIONA_CLOE) && choix[3]->niveau() >= 25 && choix[0]->niveau() >= 25 && choix[9]->niveau() >= 25) {
			S.debloquerSucces(SUCCES_NIV25_FABIAN_FIONA_CLOE);
			S.affichageDeblocageSucces(SUCCES_NIV25_FABIAN_FIONA_CLOE, allSounds);
		}
		if (!S.estDebloque(SUCCES_NIV10_NICOLAS_SEBASTIEN) && choix[1]->niveau() >= 10 && choix[8]->niveau() >= 10) {
			S.debloquerSucces(SUCCES_NIV10_NICOLAS_SEBASTIEN);
			S.affichageDeblocageSucces(SUCCES_NIV10_NICOLAS_SEBASTIEN, allSounds);
		}
		int nb_niv10 = 0;
		int nb_niv25 = 0;
		for (int i = 0;i < choix.taille();i++) {
			if (choix[i]->niveau() >= 10) {
				nb_niv10++;
				if (choix[i]->niveau() >= 25) {
					nb_niv25++;
				}
			}
		}
		if (!S.estDebloque(SUCCES_NIV10_2PERSOS) && nb_niv10 >= 2) {
			S.debloquerSucces(SUCCES_NIV10_2PERSOS);
			S.affichageDeblocageSucces(SUCCES_NIV10_2PERSOS, allSounds);
		}
		if (!S.estDebloque(SUCCES_NIV25_3PERSOS) && nb_niv25 >= 3) {
			S.debloquerSucces(SUCCES_NIV25_3PERSOS);
			S.affichageDeblocageSucces(SUCCES_NIV25_3PERSOS, allSounds);
		}
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

				if (AfficherJoueurs.comprendLesCoord(x, y,allSounds)) {
					(*window).clear();
					H.afficherJoueurs(0, choix, window,allSounds);
				}
				else if (AfficherCompetences.comprendLesCoord(x, y, allSounds)) {
					(*window).clear();
					H.afficherCompetences(0, choix, window, allSounds);
				}
				else if (AfficherMecaniques.comprendLesCoord(x, y, allSounds)) {
					(*window).clear();
					H.afficherMecaniques(window, allSounds);
				}
				else if (AfficherAnimaux.comprendLesCoord(x, y,allSounds)) {
					(*window).clear();
					H.afficherAnimaux(A, window,allSounds);
				}
				else if (AfficherSucces.comprendLesCoord(x, y, allSounds)) {
					(*window).clear();
					H.afficherSucces(1, S, window,allSounds);
				}
				else if (Jouer.comprendLesCoord(x, y,allSounds) && Gentil.taille() > 0) {
					jouer(window, Z, Obj, allSounds, H, Meuchant, Gentil, choix);
				}
				else if (modifierEquipe.comprendLesCoord(x, y,allSounds)) {
					(*window).clear();
					H.menuModifierEquipe(Gentil, choix,Z, Z.nbPersoJouable() - Gentil.taille(), window,allSounds);
					
				}
				else if (Secret.comprendLesCoord(x, y,allSounds)) {
					H.afficherTexte(Aleatoire(20, 1100).entier(), Aleatoire(20, 700).entier(), "BOING", sf::Color::Red, window);
					if (!S.estDebloque(0)) {
						S.debloquerSucces(0);
						S.affichageDeblocageSucces(0, allSounds);
					}
				}
			}
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}
		//(*window).clear();
		(*window).display();
	}

	return 0;
}

