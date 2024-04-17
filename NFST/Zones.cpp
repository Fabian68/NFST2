#include "Zones.h"
#include "Lapin.h"
#include "Sanglier.h"
#include <iostream>
#include "Cerf.h"
#include "Zombie.h"
#include "SqueletteArcher.h"
#include "Creeper.h"
#include "Ghast.h"
#include "WitherSquelette.h"
#include "Wither.h"
#include "Grognard.h"
#include "Elite.h"
#include "Brute.h"
#include "Chasseur.h"
#include "Rapace.h"
#include "Dragon.h"
#include "Tellurique.h"
#include "Magicien.h"
#include "TortueE.h"
#include "PhenixE.h"
#include <SFML/Audio.hpp>

Zones::Zones()
{
	int un = 1;
	FILE* file = fopen("Zones.txt", "r");
	if (file == NULL) {
		std::ofstream os("Zones.txt", std::ios::binary);
		os.write((char*)&un, sizeof(un));
		//os << 1 << std::endl;
		os.close();
	}
	else {
		fclose(file);
	}
	std::ifstream is("Zones.txt", std::ios::binary);
	is.read((char*)&_niveauMax, sizeof(_niveauMax));
	//is >> _niveauMax;
	is.close();
}

void Zones::ecrireZone()
{
	std::ofstream os("Zones.txt", std::ios::binary);
	os.write((char*)&_niveauMax, sizeof(_niveauMax));
	//os << _niveauMax << std::endl;
	os.close();
}

void Zones::equipeEnZone(int i,Equipes & E)
{
	Objets obj = Objets();
	switch (i)
	{
	case 1:
		E.ajouterPerso(new Lapin(1, "Lapin nain"));
		break;
	case 2:
		E.ajouterPerso(new Lapin(2, "Lapin nain"));
		E.ajouterPerso(new Lapin(1, "Lapin nain"));
		break;
	case 3:
		E.ajouterPerso(new Lapin(2, "Lapin nain"));
		E.ajouterPerso(new Lapin(3, "Petit lapin"));
		E.ajouterPerso(new Lapin(1, "Lapin nain"));
		break;
	case 4:
		E.ajouterPerso(new Lapin(2, "Lapin nain"));
		E.ajouterPerso(new Lapin(4, "Petit lapin"));
		E.ajouterPerso(new Lapin(2, "Lapin nain"));
		break;
	case 5:
		E.ajouterPerso(new Lapin(3, "Petit lapin"));
		E.ajouterPerso(new Lapin(5, "Jojo le lapin", 1, 0, 5));
		E.ajouterPerso(new Lapin(3, "Petit lapin"));
		break;
	case 6:
		E.ajouterPerso(new Sanglier(8, "Petit sanglier"));
		E.ajouterPerso(new Lapin(4, "Lapin"));
		E.ajouterPerso(new Lapin(4, "Lapin"));
		break;
	case 7:
		E.ajouterPerso(new Sanglier(10, "Petit sanglier"));
		E.ajouterPerso(new Lapin(6, "Lapin"));
		E.ajouterPerso(new Sanglier(8, "Petit sanglier"));
		E.ajouterPerso(new Lapin(2, "Lapin nain"));
		E.ajouterPerso(new Lapin(3, "Petit lapin"));
		E.ajouterPerso(new Lapin(1, "Lapin nain"));
		E.ajouterPerso(new Lapin(4, "Petit lapin"));
		E.ajouterPerso(new Lapin(2, "Lapin nain"));
		E.ajouterPerso(new Lapin(4, "Petit lapin"));
		E.ajouterPerso(new Lapin(2, "Lapin nain"));
		break;
	case 8:
		E.ajouterPerso(new Sanglier(12, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(10, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(10, "Petit sanglier"));
		break;
	case 9:
		E.ajouterPerso(new Sanglier(12, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(15, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(12, "Petit sanglier"));
		E.ajouterPerso(new TortueE(9, ""));
		break;
	case 10:
		E.ajouterPerso(new Sanglier(16, "SANGLINOLANT", 1, 9, 1));
		E.ajouterPerso(new Sanglier(15, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(12, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(15, "SANGLOT", 1, 9, 1));
		break;
	case 11:
		E.ajouterPerso(new Sanglier(22, "Sanglier"));
		E.ajouterPerso(new Lapin(26, "Lapin"));
		E.ajouterPerso(new Cerf(20, "Cerf a rien"));
		E.ajouterPerso(new Lapin(25, "Teddy"));
		E.ajouterPerso(new PhenixE(32, "phephe"));
		break;
	case 12:
		E.ajouterPerso(new Sanglier(25, "Sanglier"));
		E.ajouterPerso(new Lapin(28, "Lapinot"));
		E.ajouterPerso(new Cerf(31, "Cerf volant"));
		E.ajouterPerso(new Cerf(33, "Cerfsceau"));
		break;
	case 13:
		E.ajouterPerso(new Sanglier(35, "Sanglier"));
		E.ajouterPerso(new Cerf(34, "Cerftrude"));
		E.ajouterPerso(new Cerf(36, "Cerftoi"));
		E.ajouterPerso(new Cerf(38, "Dans sa maison un grand cerf"));
		break;
	case 14:
		E.ajouterPerso(new Sanglier(37, "Sanglier"));
		E.ajouterPerso(new Cerf(38, "Cerftrude"));
		E.ajouterPerso(new Cerf(39, "Cerftoi"));
		E.ajouterPerso(new Cerf(38, "Dans sa maison un grand cerf"));
		E.ajouterPerso(new TortueE(41, ""));
		break;
	case 15:
		E.ajouterPerso(new Cerf(42, "Cerf d'acier",2,8,2));
		E.ajouterPerso(new Cerf(45, "CerfLaPince",1,3,3));
		E.ajouterPerso(new Cerf(50, "Cerf gilet jaune",1,3,2));
		E.ajouterPerso(new Cerf(40, "Cerf"));
		break;
	case 16:
		E.ajouterPerso(new Sanglier(50, "Sanglier"));
		E.ajouterPerso(new Cerf(52, "Cerf"));
		E.ajouterPerso(new Cerf(57, "Cerf"));
		E.ajouterPerso(new Lapin(59, "Lapin"));
		E.ajouterPerso(new PhenixE(65, "Phenwick",2));
		break;
	case 17:
		E.ajouterPerso(new Sanglier(60, "Sanglier"));
		E.ajouterPerso(new Sanglier(62, "Sanglier"));
		E.ajouterPerso(new Cerf(63, "Cerf"));
		E.ajouterPerso(new Lapin(65, "Lapin"));
		break;
	case 18:
		E.ajouterPerso(new Sanglier(80, "Sanglier"));
		E.ajouterPerso(new Sanglier(74, "Sanglier"));
		E.ajouterPerso(new Cerf(78, "Cerf"));
		E.ajouterPerso(new Sanglier(76, "Sanglier"));
		break;
	case 19:
		E.ajouterPerso(new Sanglier(86, "Sanglier"));
		E.ajouterPerso(new Lapin(89, "Lapin"));
		E.ajouterPerso(new Cerf(84, "Cerf"));
		E.ajouterPerso(new Sanglier(87, "Sanglier"));
		break;
	case 20:
		E.ajouterPerso(new Lapin(90, "Lapinou",2,9,5));
		E.ajouterPerso(new Lapin(95, "Lapinouboss",1,2,1));
		E.ajouterPerso(new Cerf(99, "Cerfa",1,3,2));
		E.ajouterPerso(new Sanglier(92, "ROi des Sangliers",2,5,2));
		E.ajouterPerso(new TortueE(99, ""));
		E.perso(0)->setObjets(obj.objetNumero(10), obj.objetNumero(11));
		break;
	case 21:
		E.ajouterPerso(new Zombie(100, "Zombie"));
		E.ajouterPerso(new Zombie(100, "Zombie"));
		E.ajouterPerso(new Zombie(100, "Zombie"));
		E.perso(0)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		E.perso(1)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		E.perso(2)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 22:
		E.ajouterPerso(new Zombie(100, "Zombie"));
		E.ajouterPerso(new Zombie(102, "Zombie"));
		E.ajouterPerso(new Zombie(105, "Zombie"));
		E.ajouterPerso(new Zombie(102, "Zombie"));
		E.ajouterPerso(new PhenixE(115, "phephe",2));
		break;
	case 23:
		E.ajouterPerso(new Zombie(115, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(105, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(110, "Squelette archer"));
		break;
	case 24:
		E.ajouterPerso(new Zombie(125, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(130, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(120, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(130, "Squelette archer"));
		break;
	case 25:
		E.ajouterPerso(new Zombie(140, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(145, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(125, "Squelette archer"));
		E.ajouterPerso(new Zombie(135, "Zombie",0,1,3));
		E.perso(3)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 26:
		E.ajouterPerso(new Zombie(150, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(145, "Squelette archer"));
		E.ajouterPerso(new Creeper(150, "Cripeur"));
		E.ajouterPerso(new Zombie(145, "Squelette archer", 0, 1, 3));
		E.perso(3)->setObjets(obj.objetNumero(12), obj.objetNumero(29));
		break;
	case 27:
		E.ajouterPerso(new Zombie(160, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(155, "Squelette archer"));
		E.ajouterPerso(new Creeper(155, "Creeper"));
		E.ajouterPerso(new Creeper(160, "Creeper"));
		break;
	case 28:
		E.ajouterPerso(new Zombie(180, "Zombie"));
		E.ajouterPerso(new Creeper(175, "Creeper"));
		E.ajouterPerso(new Creeper(165, "Creeper"));
		E.ajouterPerso(new Creeper(170, "Creeper"));
		break;
	case 29:
		E.ajouterPerso(new Zombie(190, "Zombie"));
		E.ajouterPerso(new Creeper(180, "Creeper"));
		E.ajouterPerso(new Lapin(199, "Lapin",0,1,5));
		E.ajouterPerso(new Creeper(175, "Creeper"));
		E.perso(3)->setObjets(obj.objetNumero(15), obj.objetNumero(16));
		break;
	case 30:
		E.ajouterPerso(new Zombie(200, "Zombie Cochon",3,1,3));
		E.ajouterPerso(new Creeper(199, "Creeper",1));
		E.ajouterPerso(new Ghast(200, "Ghast"));
		E.ajouterPerso(new WitherSquelette(200, "Wither Squelette"));
		E.perso(0)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 31:
		E.ajouterPerso(new Zombie(210, "Zombie Cochon", 3, 1, 3));
		E.ajouterPerso(new Ghast(215, "Ghast"));
		E.ajouterPerso(new Ghast(210, "Ghast"));
		E.ajouterPerso(new WitherSquelette(220, "Wither Squelette"));
		E.perso(0)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 32:
		E.ajouterPerso(new Zombie(220, "Zombie Cochon", 3, 1, 3));
		E.ajouterPerso(new WitherSquelette(225, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(230, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(222, "Wither Squelette"));
		E.perso(0)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 33:
		E.ajouterPerso(new Wither(230, "Wither lvl 1"));
		E.ajouterPerso(new WitherSquelette(235, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(230, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(225, "Wither Squelette"));
		E.ajouterPerso(new PhenixE(250, "phephe", 3));
		break;
	case 34:
		E.ajouterPerso(new WitherSquelette(240, "Wither Squelette GOD ",1));
		E.ajouterPerso(new WitherSquelette(245, "Wither Squelette"));
		E.ajouterPerso(new Wither(250, "Super WITHER",1));
		E.ajouterPerso(new WitherSquelette(245, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(240, "Wither Squelette"));
		E.perso(0)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		E.perso(2)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 35:
		E.ajouterPerso(new Grognard(250, "Grognard"));
		E.ajouterPerso(new Grognard(250, "Grognard"));
		E.ajouterPerso(new Grognard(250, "Super Grognard",1,2,5));
		E.perso(2)->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		E.perso(2)->setObjets2(obj.objetNumero(29), obj.objetNumero(43));
		E.ajouterPerso(new Grognard(250, "Grognard"));
		E.ajouterPerso(new Grognard(250, "Grognard"));
		break;
	case 36:
		E.ajouterPerso(new Grognard(255, "Grognard"));
		E.ajouterPerso(new Grognard(255, "Grognard"));
		E.ajouterPerso(new Elite(255, "Elite"));
		E.ajouterPerso(new Grognard(255, "Grognard"));
		E.ajouterPerso(new Grognard(255, "Grognard"));
		break;
	case 37:
		E.ajouterPerso(new Elite(262, "Elite"));
		E.ajouterPerso(new Grognard(260, "Grognard"));
		E.ajouterPerso(new Grognard(267, "Grognard"));
		E.ajouterPerso(new Grognard(263, "Grognard"));
		E.ajouterPerso(new Elite(263, "Elite"));
		break;
	case 38:
		E.ajouterPerso(new Elite(273, "Elite"));
		E.ajouterPerso(new Grognard(265, "Grognard"));
		E.ajouterPerso(new Grognard(270, "Grognard"));
		E.ajouterPerso(new Rapace(272, "Rapace"));
		E.ajouterPerso(new Elite(275, "Elite"));
		break;
	case 39:
		E.ajouterPerso(new Elite(285, "Elite"));
		E.ajouterPerso(new Rapace(273, "Rapace"));
		E.ajouterPerso(new Grognard(290, "Grognard"));
		E.ajouterPerso(new Rapace(280, "Rapace"));
		E.ajouterPerso(new Elite(282, "Elite"));
		break;
	case 40:
		E.ajouterPerso(new Chasseur(300, "Chasseur"));
		E.ajouterPerso(new Chasseur(300, "Chasseur"));
		E.ajouterPerso(new Tellurique(300, "TARDIS",2));
		break;
	case 41:
		E.ajouterPerso(new Brute(310, "Brute"));
		E.ajouterPerso(new Brute(310, "Brute"));
		E.ajouterPerso(new Grognard(320, "Grognard"));
		E.ajouterPerso(new Rapace(315, "Rapace"));
		E.ajouterPerso(new Rapace(315, "Rapace"));
		break;
	case 42:
		E.ajouterPerso(new Brute(320, "Brute"));
		E.ajouterPerso(new Brute(320, "Brute"));
		E.ajouterPerso(new Brute(324, "Brute"));
		E.ajouterPerso(new Rapace(323, "Rapace"));
		E.ajouterPerso(new Rapace(325, "Rapace"));
		break;
	case 43:
		E.ajouterPerso(new Brute(333, "Brute"));
		E.ajouterPerso(new Brute(328, "Brute"));
		E.ajouterPerso(new Brute(335, "Brute"));
		E.ajouterPerso(new Grognard(338, "Grognard"));
		E.ajouterPerso(new Grognard(331, "Grognard"));
		break;
	case 44:
		E.ajouterPerso(new Chasseur(340, "Chasseur"));
		E.ajouterPerso(new Chasseur(344, "Chasseur"));
		E.ajouterPerso(new Brute(345, "Brute"));
		E.ajouterPerso(new Rapace(342, "Rapace"));
		E.ajouterPerso(new Rapace(343, "Rapace"));
		E.ajouterPerso(new PhenixE(375, "phephe", 4));
		break;
	case 45:
		E.ajouterPerso(new Chasseur(350, "Âne"));
		E.ajouterPerso(new Chasseur(351, "JO le cariste",2));
		E.ajouterPerso(new Elite(355, "Not Fabian",2));
		E.ajouterPerso(new Grognard(350, "Chef Yannick",2));
		E.ajouterPerso(new Grognard(353, "Burdukrai",1));
		break;
	case 46:
		E.ajouterPerso(new Grognard(360, "Grognardmaggedon",1));
		E.ajouterPerso(new Grognard(365, "Grognardmaggedon",1));
		E.ajouterPerso(new Grognard(370, "Grognardmaggedon",1));
		E.ajouterPerso(new Grognard(360, "Grognardmaggedon",1));
		E.ajouterPerso(new Grognard(365, "Grognardmaggedon",1));
		E.perso(0)->setObjets(obj.objetNumero(29), obj.objetNumero(12));
		E.perso(4)->setObjets(obj.objetNumero(29), obj.objetNumero(12));
		E.perso(1)->setObjets(obj.objetNumero(29), obj.objetNumero(12));
		E.perso(2)->setObjets(obj.objetNumero(29), obj.objetNumero(12));
		E.perso(3)->setObjets(obj.objetNumero(29), obj.objetNumero(12));
		break;
	case 47:
		E.ajouterPerso(new Elite(360, "Elite"));
		E.ajouterPerso(new Elite(362, "Elite"));
		E.ajouterPerso(new Elite(364, "Elite"));
		E.ajouterPerso(new Elite(366, "Elite"));
		E.ajouterPerso(new Elite(368, "Elite"));
		break;
	case 48:
		E.ajouterPerso(new Brute(370, "Brute"));
		E.ajouterPerso(new Brute(372, "Brute"));
		E.ajouterPerso(new Brute(374, "Chef Brute (LTOUCA)",1));
		E.ajouterPerso(new Brute(376, "Brute"));
		E.ajouterPerso(new Brute(378, "Brute"));
		E.perso(2)->setObjets(obj.objetNumero(12), obj.objetNumero(35));
		break;
	case 49:
		E.ajouterPerso(new Chasseur(380, "Chasseur"));
		E.ajouterPerso(new Chasseur(380, "Chasseur"));
		E.ajouterPerso(new Chasseur(390, "Chasseur"));
		E.ajouterPerso(new Chasseur(390, "Chasseur"));
		break;
	case 50:
		E.ajouterPerso(new Chasseur(400, "Chasseur LTOUCA",1));
		E.ajouterPerso(new Chasseur(400, "Chasseur LTOUCA",1));
		E.ajouterPerso(new Elite(400, "Elite LTOUCA",1));
		E.ajouterPerso(new Elite(400, "Elite LTOUCA",1));
		E.ajouterPerso(new Rapace(400, "Rapace LTOUCA",1));
		E.ajouterPerso(new Rapace(400, "Rapace LTOUCA",1));
		break;
	case 51:
		E.ajouterPerso(new Dragon(420, "Poupou le dragon"));
		E.ajouterPerso(new TortueE(999, ""));
		break;
	case 52:
		E.ajouterPerso(new Brute(437, "Brutasse",5));
		E.ajouterPerso(new Creeper(439, "Bombe humaine"));
		E.ajouterPerso(new Creeper(424, "Bombre humaine"));
		E.ajouterPerso(new Creeper(420, "Bombe humaine"));
		E.ajouterPerso(new Elite(436, "Arbiter"));
		E.ajouterPerso(new Grognard(421, "Grognard lache"));
		break;
	case 53:
		E.ajouterPerso(new WitherSquelette(453, "Wither Epais", 5));
		E.ajouterPerso(new Elite(446, "Elite du nether"));
		E.ajouterPerso(new Sanglier(451, "Sanglier perdu"));
		E.ajouterPerso(new Cerf(445, "Pain perdu"));
		E.ajouterPerso(new SqueletteArcher(440, "Skelletor"));
		E.ajouterPerso(new Elite(453, "Elitas travel"));
		break;
	case 54:
		E.ajouterPerso(new Grognard(470, "Grognard dans un mur", 5));
		E.ajouterPerso(new Lapin(480, "Lap1",0,9,5));
		E.ajouterPerso(new SqueletteArcher(470, ".",0,5,5));
		E.ajouterPerso(new Grognard(482, "Grognard perdu",0,2,5));
		E.ajouterPerso(new SqueletteArcher(475, "Cov19",0,5,5));
		E.ajouterPerso(new Ghast(476, "Terroriste",0,4,5));
		break;
	case 55:
		E.ajouterPerso(new WitherSquelette(483, "Wither Epais", 5,6,5));
		E.ajouterPerso(new Cerf(499, "Cerf 500",0,3,5));
		E.ajouterPerso(new Grognard(490, "Grognardou",0,2,5));
		E.ajouterPerso(new Lapin(488, "Lapinois",0,9,5));
		E.ajouterPerso(new Zombie(487, "Zombille",0,1,5));
		E.ajouterPerso(new Sanglier(503, "Sangline",0,9,5));
		E.ajouterPerso(new Grognard(502, "Groslourd",0,2,5));
		break;
	case 56:
		E.ajouterPerso(new Lapin(400, "Petit lapin"));
		E.ajouterPerso(new Lapin(500, "Jojo le lapin LE RETOUR", 1, 0, 5));
		E.ajouterPerso(new Lapin(400, "Petit lapin"));
		break;
	case 57:
		E.ajouterPerso(new Cerf(512, "Nerf d'acier",5,9,5));
		E.ajouterPerso(new Elite(514, "Elit",0,9,5));
		E.ajouterPerso(new Lapin(530, "Lapin",0,9,5));
		E.ajouterPerso(new Creeper(524, "Cri-peur",0,4,5));
		E.ajouterPerso(new Chasseur(516, "Chasseuse",0,1,5));
		E.ajouterPerso(new SqueletteArcher(526, "Lapin squelette",0,5,5));
		break;
	case 58:
		E.ajouterPerso(new Lapin(552, "Robot lapin",5,9,5));
		E.ajouterPerso(new SqueletteArcher(562, "Squelletor",0,5,5));
		E.ajouterPerso(new Sanglier(550, "Petit sanglier",0,9,5));
		E.ajouterPerso(new Creeper(550, "Petit creeper",0,4,5));
		E.ajouterPerso(new Chasseur(544, "Lapin chasseur ",0,1,5));
		E.ajouterPerso(new Grognard(553, "Petit sanglier grognardesque",0,2,5));
		break;
	case 59:
		E.ajouterPerso(new Lapin(590, "Lapin robot",5,9,5));
		E.ajouterPerso(new Lapin(573, "Lapin robot",5,9,5));
		E.ajouterPerso(new Dragon(597, "Petit dragon"));
		E.ajouterPerso(new Grognard(595, "Petit grognard",0,2,5));
		E.ajouterPerso(new Sanglier(607, "Petit sanglier",0,9,5));
		E.ajouterPerso(new Chasseur(573, "Petit chasseur",0,1,5));
		break;
	case 60:
		E.ajouterPerso(new Elite(12, "Sebastien"));	
		break;
	case 61:
		E.ajouterPerso(new Sanglier(480, "SANGLINOLANT LE RETOUR", 1, 9, 1));
		E.ajouterPerso(new Sanglier(350, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(120, "Petit sanglier"));
		E.ajouterPerso(new Sanglier(370, "SANGLOT", 1, 9, 1));
		break;
	case 62:
		E.ajouterPerso(new Sanglier(598, "Sanglier",0,9,5));
		E.ajouterPerso(new Lapin(602, "Lapin",0,9,5));
		E.ajouterPerso(new Cerf(595, "Cerf a rien",0,3,5));
		E.ajouterPerso(new Lapin(619, "Super Teddy",1,9,5));
		break;
	case 63:
		E.ajouterPerso(new Chasseur(626, "Chasseur"));
		E.ajouterPerso(new Chasseur(626, "Chasseur"));
		E.ajouterPerso(new WitherSquelette(616, "azezaehhdfgs"));
		E.ajouterPerso(new Cerf(618, "Cerfsceau",0,3,5));
		E.ajouterPerso(new WitherSquelette(615, "Sanglier heu non witherSquellete"));
		E.ajouterPerso(new Rapace(613, "Oiseau de ses morts"));
		E.ajouterPerso(new Chasseur(612, "Chasseur"));
		E.ajouterPerso(new Elite(635, "Elite"));
		break;
	case 64:
		E.ajouterPerso(new Grognard(656, "La petite Ginette", 0, 2, 5));
		E.ajouterPerso(new Grognard(639, "Petit grognard", 0, 2, 5));
		E.ajouterPerso(new Grognard(676, "Petit grognard", 0, 2, 5));
		E.ajouterPerso(new Grognard(654, "Petit grognard", 0, 2, 5));
		E.ajouterPerso(new Grognard(665, "Petit grognard", 0, 2, 5));
		E.ajouterPerso(new Grognard(649, "Petit grognard", 0, 2, 5));
		E.ajouterPerso(new Grognard(653, "Le grand René", 0, 2, 5));
		E.ajouterPerso(new Grognard(669, "Petit grognard", 0, 2, 5));
		E.ajouterPerso(new Grognard(645, "Petit grognard", 0, 2, 5));
		E.ajouterPerso(new Grognard(680, "Petit grognard", 0, 2, 5));
		break;
	case 65:
		E.ajouterPerso(new Sanglier(700, "Sanglier",5,9,5));
		E.ajouterPerso(new Cerf(677, "Cerftrude",0,3,5));
		E.ajouterPerso(new Cerf(677, "Cerftoi",0,3,5));
		E.ajouterPerso(new Cerf(694, "Dans sa maison un grand cerf",0,3,5));
		break;
	case 66:
		E.ajouterPerso(new Cerf(777, "Cerf d'acier LE RETOUR", 2, 8, 5));
		//E[0]->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 67:
		E.ajouterPerso(new Wither(692, "Wither"));
		E.ajouterPerso(new Wither(706, "Wither"));
		E.ajouterPerso(new Wither(727, "Wither"));
		//E[0]->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		//E[1]->setObjets(obj.objetNumero(35), obj.objetNumero(5));
		//E[2]->setObjets(obj.objetNumero(6), obj.objetNumero(36));
		break;
	case 68:
		E.ajouterPerso(new Wither(770, "SUPER Wither",1));
		//E[0]->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 69:
		E.ajouterPerso(new Dragon(797, "Dragon de l'END",1));
		//E[0]->setObjets(obj.objetNumero(28), obj.objetNumero(30));
		break;
	case 70:
		E.ajouterPerso(new Sanglier(860, "Ancien Sanglier de la mise a jour"));
		E.ajouterPerso(new Lapin(89, "Lapin"));
		E.ajouterPerso(new Cerf(84, "Cerf"));
		E.ajouterPerso(new Sanglier(87, "Sanglier"));
		break;
	case 71:
		E.ajouterPerso(new Tellurique(800, "GOLEM"));
		E.ajouterPerso(new Tellurique(825, "Telluriforce"));
		E.ajouterPerso(new Tellurique(804, "GOLEM"));
		break;
	case 72:
		E.ajouterPerso(new Tellurique(814, "GOLEM"));
		E.ajouterPerso(new Magicien(828, "blbl"));
		E.ajouterPerso(new Tellurique(815, "GOLEM"));
		break;
	case 73:
		E.ajouterPerso(new Tellurique(830, "GOLEM"));
		E.ajouterPerso(new Tellurique(833, "Telluriforce"));
		E.ajouterPerso(new Magicien(840, "blbl"));
		E.ajouterPerso(new Magicien(832, "blbl"));
		E.ajouterPerso(new Tellurique(830, "Telluriforce"));
		E.ajouterPerso(new Tellurique(850, "GOLEM"));
		break;
	case 74:
		E.ajouterPerso(new Tellurique(890, "GOLEM"));
		E.ajouterPerso(new Tellurique(863, "Telluriforce"));
		E.ajouterPerso(new Tellurique(893, "Telluriforce"));
		E.ajouterPerso(new Magicien(921, "blbl"));
		E.ajouterPerso(new Magicien(1000, "blbl"));
		E.ajouterPerso(new Magicien(940, "blbl"));
		E.ajouterPerso(new Tellurique(850, "Telluriforce"));
		E.ajouterPerso(new Tellurique(889, "Telluriforce"));
		E.ajouterPerso(new TortueE(1002, ""));
		//E[8]->setObjets(obj.objetNumero(25), obj.objetNumero(28));

		break;
	case 75:
		E.ajouterPerso(new Tellurique(1190, "GOLEM"));
		E.ajouterPerso(new Tellurique(1163, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1154, "Telluriforce"));
		E.ajouterPerso(new Magicien(1152, "blbl"));
		E.ajouterPerso(new Magicien(1200, "blbl"));
		E.ajouterPerso(new Magicien(1156, "blbl"));
		E.ajouterPerso(new Tellurique(1145, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1146, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1169, "GOLEM"));
		break;
	case 76:
		E.ajouterPerso(new Tellurique(1290, "GOLEM"));
		E.ajouterPerso(new Tellurique(1263, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1254, "Telluriforce"));
		E.ajouterPerso(new Magicien(1252, "blbl"));
		E.ajouterPerso(new Magicien(1299, "blbl"));
		E.ajouterPerso(new Dragon(1300, "blbl"));
		E.ajouterPerso(new Tellurique(1245, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1246, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1269, "GOLEM"));
		break;
	case 77:
		E.ajouterPerso(new Tellurique(1390, "GOLEM"));
		E.ajouterPerso(new Tellurique(1363, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1354, "Telluriforce"));
		E.ajouterPerso(new Magicien(1352, "blbl"));
		E.ajouterPerso(new Magicien(1399, "blbl"));
		E.ajouterPerso(new Dragon(1400, "blbl"));
		E.ajouterPerso(new Tellurique(1345, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1346, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1369, "GOLEM"));
		break;
	case 78:
		E.ajouterPerso(new Tellurique(1490, "GOLEM"));
		E.ajouterPerso(new Tellurique(1463, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1454, "Telluriforce"));
		E.ajouterPerso(new Magicien(1452, "blbl"));
		E.ajouterPerso(new Magicien(1499, "blbl"));
		E.ajouterPerso(new Dragon(1500, "blbl"));
		E.ajouterPerso(new Tellurique(1445, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1446, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1469, "GOLEM"));
		break;
	case 79:
		E.ajouterPerso(new Tellurique(1590, "Tellurique de la mise a jour"));
		E.ajouterPerso(new Tellurique(1563, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1554, "Telluriforce"));
		E.ajouterPerso(new Magicien(1552, "blbl"));
		E.ajouterPerso(new Magicien(1599, "blbl"));
		E.ajouterPerso(new Dragon(1600, "blbl"));
		E.ajouterPerso(new Tellurique(1545, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1546, "Telluriforce"));
		E.ajouterPerso(new Tellurique(1569, "GOLEM"));
		break;
	case 80:
		E.ajouterPerso(new Brute(1674, "BRUTUS",1));
		E.ajouterPerso(new Magicien(1670, "MAGIE"));
		E.ajouterPerso(new Cerf(1679, "Cerffi",0,9,5));
		E.ajouterPerso(new SqueletteArcher(1610, "Squelletor"));
		E.ajouterPerso(new Zombie(1615, "Zombie",0,9,5));
		E.ajouterPerso(new Ghast(1670, "Ghaston"));
		E.ajouterPerso(new Sanglier(1682, "Sangline",0,9,5));
		E.ajouterPerso(new Cerf(1649, "Cerfouille",0,9,5));
		E.ajouterPerso(new Lapin(1688, "Lapin",0,9,5));
		E.ajouterPerso(new Brute(1620, "Brutglu"));
		break;
	case 81:
		E.ajouterPerso(new Grognard(1830, "Grohny"));
		E.ajouterPerso(new Chasseur(1838, "Chasseur"));
		E.ajouterPerso(new Elite(1858, "Elitoi", 0, 9, 5));
		E.ajouterPerso(new SqueletteArcher(1814, "Squelletor"));
		E.ajouterPerso(new SqueletteArcher(1849, "Squelltor", 0, 9, 5));
		E.ajouterPerso(new Zombie(1868, "Zomby",0,9,5));
		E.ajouterPerso(new WitherSquelette(1806, "Wither Squelette", 0, 9, 5));
		E.ajouterPerso(new Grognard(1872, "Grogny", 0, 9, 5));
		E.ajouterPerso(new Wither(1892, "Wither", 0, 9, 5));
		E.ajouterPerso(new Rapace(1819, "Rapacy"));
		break;
	case 82:
		E.ajouterPerso(new Tellurique(2024, "MUR TELLURIQUE",0,9,5));
		E.ajouterPerso(new Tellurique(2098, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2004, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2006, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2052, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2048, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2017, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2038, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2081, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2009, "MUR TELLURIQUE", 0, 9, 5));
		break;
	case 83:
		E.ajouterPerso(new Tellurique(2279, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2204, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Dragon(2257, "DRAGON TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2208, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Magicien(2228, "MAGICIEN TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Dragon(2260, "DRAGON TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2266, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Magicien(2298, "MAGICIEN TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Dragon(2209, "DRAGON TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2244, "MUR TELLURIQUE", 0, 9, 5));
		break;
	case 84:
		E.ajouterPerso(new Tellurique(2579, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2504, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Dragon(2557, "DRAGON TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2508, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Magicien(2528, "MAGICIEN TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Dragon(2560, "DRAGON TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2566, "MUR TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Magicien(2598, "MAGICIEN TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Dragon(2509, "DRAGON TELLURIQUE", 0, 9, 5));
		E.ajouterPerso(new Tellurique(2544, "MUR TELLURIQUE", 0, 9, 5));
		break;
	case 85:
		E.ajouterPerso(new Lapin(2690, "Lapinou", 2, 9, 5));
		E.ajouterPerso(new Lapin(2695, "Lapin", 0, 2, 1));
		E.ajouterPerso(new Cerf(2699, "Cerf", 0, 3, 2));
		E.ajouterPerso(new Sanglier(2692, "Sanglier", 0, 5, 2));
		E.ajouterPerso(new Zombie(2700, "Zombie"));
		E.ajouterPerso(new Zombie(2700, "Zombie"));
		E.ajouterPerso(new Zombie(2700, "Zombie"));
		break;
	case 86:
		E.ajouterPerso(new Zombie(2800, "Zombie"));
		E.ajouterPerso(new Zombie(2802, "Zombie"));
		E.ajouterPerso(new Zombie(2805, "Zombie"));
		E.ajouterPerso(new Zombie(2802, "Zombie"));
		E.ajouterPerso(new Zombie(2915, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(2905, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(2900, "Squelette archer"));
		break;
	case 87:
		E.ajouterPerso(new Zombie(3025, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(3030, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(3020, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(3030, "Squelette archer"));
		E.ajouterPerso(new Zombie(3140, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(3145, "Squelette archer"));
		E.ajouterPerso(new SqueletteArcher(3125, "Squelette archer"));
		E.ajouterPerso(new Zombie(3135, "Zombie", 0, 1, 3));
		break;
	case 88:
		E.ajouterPerso(new Zombie(3250, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(3245, "Squelette archer"));
		E.ajouterPerso(new Creeper(3250, "Cripeur"));
		E.ajouterPerso(new Zombie(3245, "Squelette archer", 0, 1, 3));
		E.ajouterPerso(new Zombie(3260, "Zombie"));
		E.ajouterPerso(new SqueletteArcher(3255, "Squelette archer"));
		E.ajouterPerso(new Creeper(3255, "Creeper"));
		E.ajouterPerso(new Creeper(3260, "Creeper"));
		break;
	case 89:
		E.ajouterPerso(new Zombie(3380, "Zombie"));
		E.ajouterPerso(new Creeper(3375, "Creeper"));
		E.ajouterPerso(new Creeper(3365, "Creeper"));
		E.ajouterPerso(new Creeper(3370, "Creeper"));
		E.ajouterPerso(new Zombie(3390, "Zombie"));
		E.ajouterPerso(new Creeper(3380, "Creeper"));
		E.ajouterPerso(new Lapin(3399, "Lapin", 0, 1, 5));
		E.ajouterPerso(new Creeper(3375, "Creeper"));
		E.ajouterPerso(new PhenixE(4000, "phephe", 4));
		break;
	case 90:
		E.ajouterPerso(new Zombie(3400, "Zombie Cochon", 0, 1, 3));
		E.ajouterPerso(new Creeper(3499, "Creeper", 1));
		E.ajouterPerso(new Ghast(3400, "Ghast"));
		E.ajouterPerso(new WitherSquelette(3400, "Wither Squelette"));
		E.ajouterPerso(new Zombie(3410, "Zombie Cochon", 0, 1, 3));
		E.ajouterPerso(new Ghast(3415, "Ghast"));
		E.ajouterPerso(new Ghast(3410, "Ghast"));
		E.ajouterPerso(new WitherSquelette(3420, "Wither Squelette"));
		break;
	case 91:
		E.ajouterPerso(new Zombie(3520, "Zombie Cochon", 0, 1, 3));
		E.ajouterPerso(new WitherSquelette(3525, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(3530, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(3522, "Wither Squelette"));
		E.ajouterPerso(new Wither(3530, "Wither lvl 1"));
		E.ajouterPerso(new WitherSquelette(3535, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(3530, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(3525, "Wither Squelette"));
		break;
	case 92:
		E.ajouterPerso(new WitherSquelette(3640, "Wither Squelette GOD "));
		E.ajouterPerso(new WitherSquelette(3645, "Wither Squelette"));
		E.ajouterPerso(new Wither(3650, " WITHER"));
		E.ajouterPerso(new WitherSquelette(3645, "Wither Squelette"));
		E.ajouterPerso(new WitherSquelette(3640, "Wither Squelette"));
		E.ajouterPerso(new Grognard(3650, "Grognard"));
		E.ajouterPerso(new Grognard(3650, "Grognard"));
		E.ajouterPerso(new Grognard(3650, "Grognard"));
		E.ajouterPerso(new Grognard(3650, "Grognard"));
		E.ajouterPerso(new Grognard(3650, "Grognard"));
		break;
	case 93:
		E.ajouterPerso(new Grognard(3755, "Grognard"));
		E.ajouterPerso(new Grognard(3755, "Grognard"));
		E.ajouterPerso(new Elite(3755, "Elite"));
		E.ajouterPerso(new Grognard(3755, "Grognard"));
		E.ajouterPerso(new Grognard(3755, "Grognard"));
		E.ajouterPerso(new Elite(3762, "Elite"));
		E.ajouterPerso(new Grognard(3760, "Grognard"));
		E.ajouterPerso(new Grognard(3767, "Grognard"));
		E.ajouterPerso(new Grognard(3763, "Grognard"));
		E.ajouterPerso(new Elite(3763, "Elite"));
		break;
	case 94:
		E.ajouterPerso(new Elite(4073, "Elite"));
		E.ajouterPerso(new Grognard(4065, "Grognard"));
		E.ajouterPerso(new Grognard(4070, "Grognard"));
		E.ajouterPerso(new Rapace(4072, "Rapace"));
		E.ajouterPerso(new Elite(4075, "Elite"));
		E.ajouterPerso(new Elite(4085, "Elite"));
		E.ajouterPerso(new Rapace(4073, "Rapace"));
		E.ajouterPerso(new Grognard(4090, "Grognard"));
		E.ajouterPerso(new Rapace(4080, "Rapace"));
		E.ajouterPerso(new Elite(4082, "Elite"));
		break;
	case 95:
		E.ajouterPerso(new Chasseur(4500, "Chasseur"));
		E.ajouterPerso(new Chasseur(4500, "Chasseur"));
		E.ajouterPerso(new Brute(4510, "Brute"));
		E.ajouterPerso(new Brute(4510, "Brute"));
		E.ajouterPerso(new Grognard(4520, "Grognard"));
		E.ajouterPerso(new Rapace(4515, "Rapace"));
		E.ajouterPerso(new Rapace(4515, "Rapace"));
		break;
	case 96:
		E.ajouterPerso(new Brute(5020, "Brute"));
		E.ajouterPerso(new Brute(5020, "Brute"));
		E.ajouterPerso(new Brute(5024, "Brute"));
		E.ajouterPerso(new Rapace(5023, "Rapace"));
		E.ajouterPerso(new Rapace(5025, "Rapace"));
		E.ajouterPerso(new Brute(5033, "Brute"));
		E.ajouterPerso(new Brute(5028, "Brute"));
		E.ajouterPerso(new Brute(5035, "Brute"));
		E.ajouterPerso(new Grognard(5038, "Grognard"));
		E.ajouterPerso(new Grognard(5031, "Grognard"));
		break;
	case 97:
		E.ajouterPerso(new Chasseur(5540, "Chasseur"));
		E.ajouterPerso(new Chasseur(5544, "Chasseur"));
		E.ajouterPerso(new Brute(5545, "Brute"));
		E.ajouterPerso(new Rapace(5542, "Rapace"));
		E.ajouterPerso(new Rapace(5543, "Rapace"));
		E.ajouterPerso(new Chasseur(5550, "Chasseur"));
		E.ajouterPerso(new Chasseur(5551, "Chasseur"));
		E.ajouterPerso(new Elite(5555, "Elite"));
		E.ajouterPerso(new Grognard(5550, "Grognard"));
		E.ajouterPerso(new Grognard(5553, "Grognard"));
		break;
	case 98:
		E.ajouterPerso(new Grognard(6060, "Grognardmaggedon"));
		E.ajouterPerso(new Grognard(6065, "Grognardmaggedon"));
		E.ajouterPerso(new Grognard(6070, "Grognardmaggedon"));
		E.ajouterPerso(new Grognard(6060, "Grognardmaggedon"));
		E.ajouterPerso(new Grognard(6065, "Grognardmaggedon"));
		E.ajouterPerso(new Elite(6060, "Elite"));
		E.ajouterPerso(new Elite(6062, "Elite"));
		E.ajouterPerso(new Elite(6064, "Elite"));
		E.ajouterPerso(new Elite(6066, "Elite"));
		E.ajouterPerso(new Elite(6068, "Elite"));
		break;
	case 99:
		E.ajouterPerso(new Brute(6570, "Brute"));
		E.ajouterPerso(new Brute(6572, "Brute"));
		E.ajouterPerso(new Brute(6574, "Chef Brute "));
		E.ajouterPerso(new Brute(6576, "Brute"));
		E.ajouterPerso(new Brute(6578, "Brute"));
		E.ajouterPerso(new Chasseur(6580, "Chasseur"));
		E.ajouterPerso(new Chasseur(6580, "Chasseur"));
		E.ajouterPerso(new Chasseur(6590, "Chasseur"));
		E.ajouterPerso(new Chasseur(6590, "Chasseur"));
		break;
	case 100:
		E.ajouterPerso(new Chasseur(7000, "Chasseur "));
		E.ajouterPerso(new Chasseur(7000, "Chasseur"));
		E.ajouterPerso(new Elite(7000, "Elite"));
		E.ajouterPerso(new Elite(7000, "Elite"));
		E.ajouterPerso(new Rapace(7000, "Rapace "));
		E.ajouterPerso(new Rapace(7000, "Rapace "));
		break;
	case 101:
		E.ajouterPerso(new Dragon(8888, "SUPER Dragon de l'END", 2));
		break;
	}

	
}

void Zones::choixNiveau(int i)
{
	if (i > _niveauMax) {
		_niveauActuel = _niveauMax;
	}
	else {
		_niveauActuel = i;
	}
}

int Zones::niveauActuel() const
{
	return _niveauActuel;
}

int Zones::niveauMax() const
{
	return _niveauMax;
}

int Zones::nbPersoJouable() const
{
	int nb = 1;
	if (_niveauMax >= 3) {
		nb++;
	}
	if (_niveauMax >= 6) {
		nb++;
	}
	if (_niveauMax >= 11) {
		nb++;
	}
	if (_niveauMax >= 21) {
		nb++;
	}
	if (_niveauMax >= 31) {
		nb++;
	}
	if (_niveauMax >= 41) {
		nb++;
	}
	if (_niveauMax >= 51) {
		nb++;
	}
	if (_niveauMax >= 61) {
		nb++;
	}
	if (_niveauMax >= 76) {
		nb++;
	}
	return nb;
}

void Zones::niveauBattu()
{
	if (_niveauActuel == _niveauMax) {
		_niveauMax++;
		ecrireZone();
	}
}

void Zones::zoneBattue()
{
}
