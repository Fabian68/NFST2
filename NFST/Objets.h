#pragma once
#include "Objet.h"
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int OBJET_ANTIDOTE = 1;
const int OBJET_VOILE_FEU = 2;
const int OBJET_BENEDICTION = 3;
const int OBJET_SCEPTRE_DRUIDE = 4;
const int OBJET_MALEDICTION = 5;
const int OBJET_CAPE_HABILETE = 6;
const int OBJET_PATTE_LAPIN = 7;
const int OBJET_BEUH = 8;
const int OBJET_VOILE_MIROIR = 9;
const int OBJET_MARHSMALLOW = 10;
const int OBJET_ARMURE_PROTECTEUR = 11;
const int OBJET_KUNAI = 12;
const int OBJET_FLECHE_TRANSPERCANTE = 13;
const int OBJET_ARMURE_SAKERATSU = 14;
const int OBJET_CAPE_NINJA = 15;
const int OBJET_DAGUE_NINJA = 16;
const int OBJET_SOIE_LAPIN = 17;
const int OBJET_SAUCIFLAR = 18;
const int OBJET_J_B = 19;
const int OBJET_COLERE_FLORIAN = 20;
const int OBJET_TRINITE = 21;
const int OBJET_DEBARDEUR_NICOLAS = 22;
const int OBJET_JUS_POMME = 23;
const int OBJET_CHAUSSETTES_FLO = 24;
const int OBJET_GILET_PARBALLE = 25;
const int OBJET_EXCALIBUER = 26;
const int OBJET_FLECHES_TRANCHANTES = 27;
const int OBJET_COTE_SADO = 28;
const int OBJET_FLEAU_SADIQUE = 29;
const int OBJET_TOTEM_IMMUNITE = 30;
const int OBJET_MEMEMTOM = 31;
const int OBJET_JEU_NES = 32;
const int OBJET_SABLIER = 33;
const int OBJET_TARDIS = 34;
const int OBJET_LAME_MALEFIQUE = 35;
const int OBJET_MEGAMORPH = 36;
const int OBJET_NEMESIS = 37;
const int OBJET_CASSE_NOIX = 38;
const int OBJET_ESPRIT_GUERRIER = 39;
const int OBJET_TWINS = 40;
const int OBJET_OEIL_AIGLE = 41;
const int OBJET_PEAU_EPAISSE = 42;
const int OBJET_DILDO = 43;
const int OBJET_OEUF_TORTUE = 44;
const int OBJET_CENDRE_PHENIX = 45;
const int OBJET_HANTISE = 46;
const int OBJET_HUIT_BALL = 47;
const int OBJET_SPARTAN_ARMOR = 48;
const int OBJET_AVANCE_RAPIDE = 49;
const int OBJET_VASE_ANTIQUE_MAGIQUE = 50;


class Objets
{
public:
	Objets();

	void objetsDuPersonnage(int numero, Objet& obj1, Objet& obj2)const;
	void objetsDuPersonnage2(int numero, Objet& obj1, Objet& obj2)const;
	void sauvegarderObjetsEquiper();
	void equiperObjetDuPersonnage(int numero, Objet obj, bool premier);
	void equiperObjetDuPersonnage2(int numero, Objet obj, bool premier);
	std::vector<Objet> objetsDuNiveau(int numero);
	bool estDebloquer(Objet obj) const;
	int nombreObjets() const;
	Objet  objetNumero(int numero);
	void deblocageObjet( int indiceObjet, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds);
	void sauvegarderObjetsDebloquer();
private:
	std::vector<std::vector<Objet>> _tableLoot;

	std::vector<int> _objetsDebloquer;

	std::vector<Objet> _listeObjets;

	std::vector<std::pair<int, int>> _listeObjetEquiper;
	std::vector<std::pair<int, int>> _listeObjetEquiper2;
};

