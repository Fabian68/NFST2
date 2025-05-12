#include "Evan.h"

Evan::Evan(Experiences E, Orbes O, Animaux A, Objets Obj) : Personnage(ID_EVAN, E, O, A, Obj, "Evan La Terreur", 1, 1, 1, 5, 5, 0, 0, 0, 0, 1)
{
	ajouterVitesse(vitesse() / 10);
	ajouterDegatsCritique(-45);
	if (!_texture.loadFromFile("graphics/thevan.png"))
	{
		// error...
	}
	_sprite.setTexture(_texture);
}

void Evan::attaqueEnnemis(Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)
{
	ajouterVitesse(vitesse() / 100);
	status().setAdducteur(force() / 100 + status().adducteur() / 100);
	int choix = choixAttaque();
	int DEGATS;

	std::string a = nom();


	switch (choix) {

	case 0:
		DEGATS = degats(0.1, 0.3);
		Attaque(DEGATS, equipeEnnemi().plusLoinVivant(), C, window, allSounds);

		DEGATS = degats(0.1, 0.3);
		Attaque(DEGATS, equipeEnnemi().plusLoinVivant(), C, window, allSounds);

		if (attaqueDouble()) {
			DEGATS = degats(0.1, 0.3);
			Attaque(DEGATS, equipeEnnemi().plusLoinVivant(), C, window, allSounds);

			DEGATS = degats(0.1, 0.3);
			Attaque(DEGATS, equipeEnnemi().plusLoinVivant(), C, window, allSounds);
		}
		ajouterMana(1);
		break;
	case 1:

		DEGATS = degats(0.1, 0.3) + (int)(equipeEnnemi().plusProcheVivant()->vie()/30) + (int)(equipeEnnemi().plusProcheVivant()->vieMax() / 100);
		Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(0.1, 0.3) + (int)(equipeEnnemi().plusProcheVivant()->vie() / 30) + (int)(equipeEnnemi().plusProcheVivant()->vieMax() / 100);
			Attaque(DEGATS, equipeEnnemi().plusProcheVivant(), C, window, allSounds);
		}
		ajouterMana(-1);
		break;
	case 2:
		ajouterChanceRicochet(3);
		break;
	case 3:
		DEGATS = degats(0.3, 0.6) + degats(0.1, 0.4, CHOIXVITESSE);
		Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		if (attaqueDouble()) {
			DEGATS = degats(0.3, 0.6) + degats(0.1, 0.4, CHOIXVITESSE);
			Attaque(DEGATS, equipeEnnemi().plusFaible(), C, window, allSounds);
		}
		ajouterMana(-3);
		break;
	}
}

void Evan::passif(int tour, Combat& C, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds)
{
	ajouterCoupCritique(1);
	ajouterDegatsCritique(3);
	
}

void Evan::passifDefensif(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds, Combat& C, int degats, Personnage* P)
{

	ajouterChanceDoubleAttaque(1);
	ajouterChanceHabileter(1);
}
