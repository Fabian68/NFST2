#include "Objets.h"
#include <fstream>
#include "Affichage.h"
#include "Bouton.h"
#include "Succes.h"

Objets::Objets()
{
	int zero = 0;
	FILE* file = fopen("objdblc.txt", "r");
	if (file == NULL) {
		std::ofstream os("objdblc.txt",std::ios::binary);

		for (int i = 0; i < 300; i++) {
			os.write((char*)&zero, sizeof(zero));
			//os << 0;
			//os << std::endl;
		}
		os.close();
	}
	else {
		fclose(file);
	}
	_objetsDebloquer.resize(300);
	std::ifstream is("objdblc.txt", std::ios::binary);
	for (int i = 0; i < 300; i++) {
		is.read((char*)&_objetsDebloquer[i], sizeof(_objetsDebloquer[i]));
		//is >> _objetsDebloquer[i];
	}
	is.close();


	FILE* file2 = fopen("objeqp.txt", "r");
	if (file2 == NULL) {
		std::ofstream os("objeqp.txt", std::ios::binary);

		for (int i = 0; i < 30; i++) {
			os.write((char*)&zero, sizeof(zero));
			os.write((char*)&zero, sizeof(zero));
			//os << 0 <<" "<< 0;
			//os << std::endl;
		}
		os.close();
	}
	else {
		fclose(file2);
	}
	_listeObjetEquiper.resize(30);
	std::ifstream is2("objeqp.txt", std::ios::binary);
	int v1, v2;
	for (int i = 0; i < 30; i++) {
		is2.read((char*)&v1, sizeof(v1));
		is2.read((char*)&v2, sizeof(v2));
		//is2 >> v1;
		//is2 >> v2;
		_listeObjetEquiper[i].first = v1;
		_listeObjetEquiper[i].second= v2;
	}
	is2.close();

	//second set d'objets
	FILE* file3 = fopen("objeqp2.txt", "r");
	if (file3 == NULL) {
		std::ofstream os("objeqp2.txt", std::ios::binary);

		for (int i = 0; i < 30; i++) {
			os.write((char*)&zero, sizeof(zero));
			os.write((char*)&zero, sizeof(zero));
			//os << 0 <<" "<< 0;
			//os << std::endl;
		}
		os.close();
	}
	else {
		fclose(file3);
	}
	_listeObjetEquiper2.resize(30);
	std::ifstream is3("objeqp2.txt", std::ios::binary);
	
	for (int i = 0; i < 30; i++) {
		is3.read((char*)&v1, sizeof(v1));
		is3.read((char*)&v2, sizeof(v2));
		//is2 >> v1;
		//is2 >> v2;
		_listeObjetEquiper2[i].first = v1;
		_listeObjetEquiper2[i].second = v2;
	}
	is3.close();

	_listeObjets.reserve(300);
	_listeObjets.emplace_back();
	_listeObjets.emplace_back("Antidote", 1, 100000, "Rend insensible au poison");
	_listeObjets.emplace_back("Voile de feu", 2, 100000, "Les br�lures vous soignent");
	_listeObjets.emplace_back("B�n�diction", 3, 1000, "Augmente la vie Maximum de 50%");
	_listeObjets.emplace_back("Sceptre de druide", 4, 1000, "20% de chance qu'un soins donne �galement du bouclier, 10% de chance qu'ajouter du bouclier octroie une protection.");
	_listeObjets.emplace_back("Malediction", 5, 100, "Consomme votre bouclier et reduit votre vie de 10% de votre vie max chaque tour mais augmente vos d�gats de 150%");
	_listeObjets.emplace_back("Cape habilete", 6, 10000, "+10% coup habile, 6% de chance que les coup habile fassent 3 fois plus de d�gats et 3% de chance qu'elle fassent 4 fois plus de d�gats(pas pour les attaques bruts)");
	_listeObjets.emplace_back("Patte de lapin", 7, 100000, "+33% vitesse, l'experience gagner au comba par ce personnage est augmenter de 33%");
	_listeObjets.emplace_back("Beuh", 8, 10000, "-80% vitesse, l'experience gagner par ce personnage est multiplier par 2");
	_listeObjets.emplace_back("Voile miroir", 9, 1000, "+ 6% de chance de deviation, les attaques devier sont 100% plus puissantes");
	_listeObjets.emplace_back("Marshmallow", 10, 1000, "20% de chance d'absorber une attaque ennemi et de transformer les d�gats en bouclier");
	_listeObjets.emplace_back("Armure du protecteur", 11, 100000, "+10% de reduction de d�gats, 25% de chance de recevoir une attaque qui cible un allier a sa place");
	_listeObjets.emplace_back("Kunai", 12, 1000, "Toute les 3 attaques voient leurs d�gats augmenter de 30%");
	_listeObjets.emplace_back("Fl�che transpercante", 13, 10000, "Apr�s chaque attaques vous infliger une attaque brute avec 5% � 10% de votre force");
	_listeObjets.emplace_back("Armure de Sakeratsu", 14, 100000, "+10% de reduction de d�gats, renvoie 10% des d�gats re�u sous forme de d�gats brut a l'ennemi(apr�s calcul des reductions)");
	_listeObjets.emplace_back("Cape de ninja", 15, 10000, "+10% de chance d'esquive, +3% de chance de coup critique, effectuer une esquive augmente vos d�gats critique de 5%");
	_listeObjets.emplace_back("Dague de ninja", 16, 10000, "Augmente les d�gats critiques de 20%, apr�s avoir effectuer une esquive vous faites une attaque brute sur l'ennemi le plus faible a hauteur de 5% � 20% de votre force augmenter par vos d�gats critique ");
	_listeObjets.emplace_back("Soie de lapin", 17, 10, "+10% de vitesse");
	_listeObjets.emplace_back("Sauciflar", 18, 100, "+5% chance de coup critique");
	_listeObjets.emplace_back("J&B", 19, 100, "+10 points dans chaque stats");
	_listeObjets.emplace_back("Col�re de Florian ", 20, 1000, "+30 points dans chaque stats");
	_listeObjets.emplace_back("Trinit�", 21, 10000, "+75 points dans chaque stats");
	_listeObjets.emplace_back("Debardeur de Nicolas ", 22, 1000, "Attaque l'attaquant pour des d�gats de 100% votre niveau,+5% d'attaque");
	_listeObjets.emplace_back(" Jue de pomme", 23, 100, "+5% de vie max");
	_listeObjets.emplace_back("Les chaussetes de FLO", 24, 10000, " Attaque l'attaquant pour des d�gats de 100% votre niveau, 1 chance sur 10 000 d'ifnliger poison lors d'une attaque");
	_listeObjets.emplace_back(" Gilet par balle", 25, 10000," Les d�gats sont reduit de 1 par niveau du personnage ");
	_listeObjets.emplace_back("EXCALIBUR", 26, 10000, "+150 points dans chaque stats");
	_listeObjets.emplace_back("Fl�ches tranchantes", 27, 10000, "+7% de chance de ricochet, les ricochet font 37% de plus de d�gats.");
	_listeObjets.emplace_back("Cote du sadomaso", 28, 10000, "Reduit de 1(+ 1 tout les 100 niveau) les d�gats par coup re�u.");
	_listeObjets.emplace_back("Fl�au du sadique", 29, 10000, "Ajoute 1(+1 tout les 100 niveau) de d�gats par attaques r�aliser.");
	_listeObjets.emplace_back("Totem immunit�e", 30, 100000, "Permet de revivre avec toute sa vie une fois.");
	_listeObjets.emplace_back("MEMEMTOM", 31, 10000, "A chaque attaque vous avez : 1/10 de lancer une nouvelle attaque 1-10% de vos d�gats attaque, 1/100 => 10-100%,1/1000 => 100-1000%");
	_listeObjets.emplace_back("Jeu NES", 32, 1000, "Un jeux vid�o Nes, The Legend Of Zelda");
	_listeObjets.emplace_back("Sablier", 33, 10000, "Reduit le temps des combats par 4");
	_listeObjets.emplace_back("Tardis", 34, 100000, "Reduit consid�rablement le temps des combats");
	_listeObjets.emplace_back("Lame mal�fique", 35, 1000, "+50% de d�gats, re�ois deux fois plus de d�gats");
	_listeObjets.emplace_back("M�gamorph", 36, 1000, "Recever deux fois plus de d�gats quand vie superieur a 50% de votre vie maximum sinon deux fois moins");
	_listeObjets.emplace_back("N�m�sis", 37, 10000, "Faites 50% plus de d�gats a l'ennemi qui a la m�me position dans son equipe que vous dans la votre et recever deux fois moins de d�gats de sa part");
	_listeObjets.emplace_back("Casse-noix", 38, 1000, "Vous faites 50% de d�gats en plus a un ennemi qui poss�de un bouclier et 100% a un ennemis qui possede tout son bouclier");
	_listeObjets.emplace_back("Esprit du guerrier", 39, 1000, "Vous faites 1% de d�gats en plus pour chaque pourceentage de point de vie qu'ils vous manquent");
	_listeObjets.emplace_back("T6wins", 40, 10000, "Un ricochet envoie 2 attaques au lieu d'une, +2% chance de ricochets");
	_listeObjets.emplace_back("Oeil d'aigle", 41, 100000, "Vos attaques font des d�gats suppl�mentaires �quivalent a 1% de la vie actuelle de l'ennemi ");
	_listeObjets.emplace_back("Peau �paisse", 42, 100000, "Vous recever des d�gats en moins �quivalent a 1% de votre vie maximum ");
	_listeObjets.emplace_back("Dildo", 43, 100000, "Vos attaques passent a travers 50% de la reduction de d�gats et des blocages ");
	_listeObjets.emplace_back("Oeuf de Tortue", 44, 10000, "Permet de jouer un nouveau personnage, pas besoin de l'�quiper ");
	_listeObjets.emplace_back("Cendre de Ph�nix", 45, 10000, "Permet de jouer un nouveau personnage, pas besoin de l'�quiper  ");
	_listeObjets.emplace_back("Hantise", 46, 1000, "Le personnage equiper fais 3 fois plus de d�gats s'il est KO");
	_listeObjets.emplace_back("Magic 8 ball", 47, 100000, "+8% Force Vie et Vitesse et +8 dans les stats fixes");
	_listeObjets.emplace_back("Spartan armor", 48, 10000, "Vous faites plus de d�gats en fonction du montant d'armure actuelle jusqu'a +100%");
	_listeObjets.emplace_back("Avance rapide", 49, 1000, "Les combats vont deux fois plus vite");
	_listeObjets.emplace_back("Vase antique magique", 50, 100000, "+1 mana par tour, +3% de d�gats par points de mana");
	_listeObjets.emplace_back("Racine Eternel", 51, 10000, "+ 0,1-1% de votre vie en d�gats suppl�mentaires");
	_listeObjets.emplace_back("Force grandissante", 52, 10000, " -10% de d�gats critiques, +1% de d�gats critique par tour");
	_listeObjets.emplace_back("Bouclier am�lior�", 53, 10000, " reduit de 25% les d�gats subis pendant que bouclier");
	_listeObjets.emplace_back("Maladresse", 54, 1000, " +10% d�gats, +10% d�gats critiques, quand vous attaquer vous recevez une attaque �quivalent � 10% des d�gats (post reduction)");
	_listeObjets.emplace_back("Fer � cheval", OBJET_FER_CHEVAL, 10000, "+14% de forces, +25% xp");
	_listeObjets.emplace_back("Tr�fle � quattre feuilles", OBJET_TREFLE_QUATTRE, 100000, "+20% de points de vie, +50% xp");

	//_listeObjets.push_back(Objet("Antidote", 18, 100000, "Rend insensible au poison"));

	_tableLoot.resize(300);
	for (int niveau = 1;niveau < 300;niveau++) {
		_tableLoot[niveau].reserve(10);
	}
	_tableLoot[51].push_back(_listeObjets[44]);
	for (int i = 1;i <= 10;i++) {
		_tableLoot[74].push_back(_listeObjets[44]);
	}

	_tableLoot[33].push_back(_listeObjets[45]);
	for (int i = 1;i <= 10;i++) {
		_tableLoot[44].push_back(_listeObjets[45]);
	}

	_tableLoot[6].push_back(_listeObjets[46]);
	_tableLoot[9].push_back(_listeObjets[OBJET_FER_CHEVAL]);
	_tableLoot[16].push_back(_listeObjets[OBJET_TREFLE_QUATTRE]);
	_tableLoot[44].push_back(_listeObjets[47]);
	for (int i = 1;i <= 8;i++) {
		_tableLoot[88].push_back(_listeObjets[47]);
	}
	_tableLoot[13].push_back(_listeObjets[54]);
	_tableLoot[14].push_back(_listeObjets[54]);
	_tableLoot[26].push_back(_listeObjets[54]);
	_tableLoot[28].push_back(_listeObjets[54]);
	_tableLoot[39].push_back(_listeObjets[54]);

	_tableLoot[12].push_back(_listeObjets[52]);
	_tableLoot[16].push_back(_listeObjets[52]);
	_tableLoot[20].push_back(_listeObjets[52]);
	_tableLoot[20].push_back(_listeObjets[53]);
	
	_tableLoot[9].push_back(_listeObjets[51]);
	_tableLoot[18].push_back(_listeObjets[51]);
	_tableLoot[27].push_back(_listeObjets[51]);
	_tableLoot[36].push_back(_listeObjets[51]);
	_tableLoot[45].push_back(_listeObjets[51]);

	_tableLoot[10].push_back(_listeObjets[50]);
	_tableLoot[20].push_back(_listeObjets[50]);
	_tableLoot[30].push_back(_listeObjets[50]);
	_tableLoot[40].push_back(_listeObjets[50]);
	_tableLoot[50].push_back(_listeObjets[50]);

	_tableLoot[19].push_back(_listeObjets[48]);
	_tableLoot[38].push_back(_listeObjets[48]);
	_tableLoot[55].push_back(_listeObjets[48]);

	_tableLoot[20].push_back(_listeObjets[43]);
	_tableLoot[21].push_back(_listeObjets[43]);
	_tableLoot[22].push_back(_listeObjets[43]);
	_tableLoot[23].push_back(_listeObjets[43]);
	_tableLoot[24].push_back(_listeObjets[43]);
	_tableLoot[25].push_back(_listeObjets[43]);
	_tableLoot[26].push_back(_listeObjets[43]);
	_tableLoot[27].push_back(_listeObjets[43]);
	_tableLoot[28].push_back(_listeObjets[43]);
	_tableLoot[29].push_back(_listeObjets[43]);
	_tableLoot[30].push_back(_listeObjets[43]);

	_tableLoot[2].push_back(_listeObjets[40]);
	_tableLoot[4].push_back(_listeObjets[40]);
	_tableLoot[8].push_back(_listeObjets[40]);
	_tableLoot[16].push_back(_listeObjets[40]);
	_tableLoot[32].push_back(_listeObjets[40]);
	_tableLoot[68].push_back(_listeObjets[40]);

	_tableLoot[3].push_back(_listeObjets[41]);
	_tableLoot[9].push_back(_listeObjets[41]);
	_tableLoot[27].push_back(_listeObjets[41]);

	_tableLoot[3].push_back(_listeObjets[42]);
	_tableLoot[9].push_back(_listeObjets[42]);
	_tableLoot[27].push_back(_listeObjets[42]);


	_tableLoot[4].push_back(_listeObjets[38]);
	_tableLoot[6].push_back(_listeObjets[39]);
	_tableLoot[20].push_back(_listeObjets[33]);

	_tableLoot[40].push_back(_listeObjets[34]);

	_tableLoot[11].push_back(_listeObjets[36]);
	_tableLoot[22].push_back(_listeObjets[36]);
	_tableLoot[33].push_back(_listeObjets[36]);
	_tableLoot[44].push_back(_listeObjets[36]);
	_tableLoot[55].push_back(_listeObjets[36]);

	_tableLoot[3].push_back(_listeObjets[37]);
	_tableLoot[6].push_back(_listeObjets[37]);
	_tableLoot[12].push_back(_listeObjets[37]);
	_tableLoot[24].push_back(_listeObjets[37]);
	_tableLoot[48].push_back(_listeObjets[37]);

	_tableLoot[6].push_back(_listeObjets[35]);
	_tableLoot[66].push_back(_listeObjets[35]);

	_tableLoot[17].push_back(_listeObjets[32]);
	_tableLoot[34].push_back(_listeObjets[32]);
	_tableLoot[51].push_back(_listeObjets[32]);

	_tableLoot[1].push_back(_listeObjets[17]);
	_tableLoot[1].push_back(_listeObjets[8]);
	_tableLoot[1].push_back(_listeObjets[18]);

	_tableLoot[9].push_back(_listeObjets[31]);
	_tableLoot[18].push_back(_listeObjets[31]);
	_tableLoot[27].push_back(_listeObjets[31]);
	_tableLoot[36].push_back(_listeObjets[31]);
	_tableLoot[54].push_back(_listeObjets[31]);
	_tableLoot[63].push_back(_listeObjets[31]);
	_tableLoot[72].push_back(_listeObjets[31]);
	_tableLoot[81].push_back(_listeObjets[31]);

	_tableLoot[7].push_back(_listeObjets[30]);
	_tableLoot[14].push_back(_listeObjets[30]);
	_tableLoot[21].push_back(_listeObjets[30]);
	_tableLoot[28].push_back(_listeObjets[30]);
	_tableLoot[42].push_back(_listeObjets[30]);
	_tableLoot[49].push_back(_listeObjets[30]);
	_tableLoot[56].push_back(_listeObjets[30]);
	_tableLoot[63].push_back(_listeObjets[30]);

	_tableLoot[2].push_back(_listeObjets[17]);
	_tableLoot[2].push_back(_listeObjets[18]);

	_tableLoot[3].push_back(_listeObjets[17]);
	_tableLoot[3].push_back(_listeObjets[18]);

	_tableLoot[4].push_back(_listeObjets[17]);
	_tableLoot[4].push_back(_listeObjets[18]);

	_tableLoot[5].push_back(_listeObjets[17]);
	_tableLoot[5].push_back(_listeObjets[17]);
	_tableLoot[5].push_back(_listeObjets[7]);
	_tableLoot[5].push_back(_listeObjets[19]);
	_tableLoot[5].push_back(_listeObjets[28]);
	_tableLoot[5].push_back(_listeObjets[29]);

	_tableLoot[6].push_back(_listeObjets[22]);
	_tableLoot[7].push_back(_listeObjets[22]);
	_tableLoot[8].push_back(_listeObjets[22]);
	_tableLoot[9].push_back(_listeObjets[22]);
	
	_tableLoot[10].push_back(_listeObjets[14]);
	_tableLoot[10].push_back(_listeObjets[28]);
	_tableLoot[10].push_back(_listeObjets[29]);
	_tableLoot[10].push_back(_listeObjets[49]);

	_tableLoot[11].push_back(_listeObjets[23]);
	_tableLoot[12].push_back(_listeObjets[23]);
	_tableLoot[13].push_back(_listeObjets[23]);
	_tableLoot[14].push_back(_listeObjets[23]);

	_tableLoot[15].push_back(_listeObjets[3]);
	_tableLoot[15].push_back(_listeObjets[4]);
	_tableLoot[15].push_back(_listeObjets[20]);

	_tableLoot[4].push_back(_listeObjets[24]);
	_tableLoot[8].push_back(_listeObjets[24]);
	_tableLoot[12].push_back(_listeObjets[24]);
	_tableLoot[16].push_back(_listeObjets[24]);
	_tableLoot[24].push_back(_listeObjets[24]);
	_tableLoot[28].push_back(_listeObjets[24]);
	_tableLoot[32].push_back(_listeObjets[24]);
	_tableLoot[36].push_back(_listeObjets[24]);

	_tableLoot[20].push_back(_listeObjets[5]);
	_tableLoot[20].push_back(_listeObjets[9]);
	_tableLoot[20].push_back(_listeObjets[10]);
	_tableLoot[20].push_back(_listeObjets[11]);
	_tableLoot[20].push_back(_listeObjets[28]);
	_tableLoot[20].push_back(_listeObjets[29]);

	_tableLoot[21].push_back(_listeObjets[1]);
	_tableLoot[22].push_back(_listeObjets[1]);


	_tableLoot[23].push_back(_listeObjets[13]);
	_tableLoot[23].push_back(_listeObjets[12]);

	_tableLoot[24].push_back(_listeObjets[13]);
	_tableLoot[24].push_back(_listeObjets[12]);
	_tableLoot[25].push_back(_listeObjets[13]);
	_tableLoot[25].push_back(_listeObjets[12]);

	_tableLoot[26].push_back(_listeObjets[25]);
	_tableLoot[27].push_back(_listeObjets[25]);
	_tableLoot[28].push_back(_listeObjets[25]);
	_tableLoot[29].push_back(_listeObjets[25]);

	_tableLoot[30].push_back(_listeObjets[2]);
	_tableLoot[30].push_back(_listeObjets[21]);

	_tableLoot[31].push_back(_listeObjets[2]);

	_tableLoot[32].push_back(_listeObjets[25]);

	_tableLoot[33].push_back(_listeObjets[15]);
	_tableLoot[33].push_back(_listeObjets[16]);
	_tableLoot[34].push_back(_listeObjets[15]);
	_tableLoot[34].push_back(_listeObjets[16]);

	_tableLoot[35].push_back(_listeObjets[27]);
	_tableLoot[36].push_back(_listeObjets[27]);
	_tableLoot[37].push_back(_listeObjets[27]);

	_tableLoot[40].push_back(_listeObjets[28]);
	_tableLoot[40].push_back(_listeObjets[29]);
	_tableLoot[40].push_back(_listeObjets[28]);
	_tableLoot[40].push_back(_listeObjets[29]);
	_tableLoot[40].push_back(_listeObjets[28]);
	_tableLoot[40].push_back(_listeObjets[29]);

	_tableLoot[44].push_back(_listeObjets[9]);
	_tableLoot[45].push_back(_listeObjets[9]);

	_tableLoot[50].push_back(_listeObjets[6]);

	_tableLoot[100].push_back(_listeObjets[26]);
}

void Objets::objetsDuPersonnage(int numero, Objet& obj1, Objet& obj2) const
{
	obj1 = _listeObjets[_listeObjetEquiper[numero].first];
	obj2 = _listeObjets[_listeObjetEquiper[numero].second];
}

void Objets::objetsDuPersonnage2(int numero, Objet& obj1, Objet& obj2) const
{
	obj1 = _listeObjets[_listeObjetEquiper2[numero].first];
	obj2 = _listeObjets[_listeObjetEquiper2[numero].second];
}

void Objets::sauvegarderObjetsEquiper() {
	std::ofstream os("objeqp.txt", std::ios::binary);

	for (int i = 0; i < 30; i++) {
		os.write((char*)&_listeObjetEquiper[i].first, sizeof(_listeObjetEquiper[i].first));
		os.write((char*)&_listeObjetEquiper[i].second, sizeof(_listeObjetEquiper[i].second));
		//os << _listeObjetEquiper[i].first << " " << _listeObjetEquiper[i].second;
		//os << std::endl;
	}
	os.close();

	std::ofstream os2("objeqp2.txt", std::ios::binary);

	for (int i = 0; i < 30; i++) {
		os2.write((char*)&_listeObjetEquiper2[i].first, sizeof(_listeObjetEquiper2[i].first));
		os2.write((char*)&_listeObjetEquiper2[i].second, sizeof(_listeObjetEquiper2[i].second));
		//os << _listeObjetEquiper[i].first << " " << _listeObjetEquiper[i].second;
		//os << std::endl;
	}
	os2.close();
}

void Objets::equiperObjetDuPersonnage(int numero,Objet obj, bool premier) {

	if (premier == true) {
		_listeObjetEquiper[numero].first = obj.numero();
	}
	else {
		_listeObjetEquiper[numero].second = obj.numero();
	}
	sauvegarderObjetsEquiper();
}

void Objets::equiperObjetDuPersonnage2(int numero, Objet obj, bool premier) {

	if (premier == true) {
		_listeObjetEquiper2[numero].first = obj.numero();
	}
	else {
		_listeObjetEquiper2[numero].second = obj.numero();
	}
	sauvegarderObjetsEquiper();
}

std::vector<Objet> Objets::objetsDuNiveau(int numero) {
	return _tableLoot[numero];
}

bool Objets::estDebloquer(Objet obj)const {
	return _objetsDebloquer[obj.numero()] == 1;
}

int Objets::nombreObjets()const {
	return _listeObjets.size() - 1;
}

Objet  Objets::objetNumero(int numero) {
	return _listeObjets[numero];
}

void Objets::deblocageObjet(int indiceObjet, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)
{
	std::string txt = "";
	txt += "Vous avez débloquer l'objet : ";
	txt += _listeObjets[indiceObjet].nom() + " " + _listeObjets[indiceObjet].rareterTexte();
	Bouton(300.f, 400.f, txt, sf::Color::Black, sf::Color::Green, sf::Color::Green).afficher(window);

	txt = _listeObjets[indiceObjet].effet();

	Succes S;
	int rareter = _listeObjets[indiceObjet].rareter();
	if (rareter == 10000 || rareter == 100000) {
		Succes S;
		if (!S.estDebloque(SUCCES_OBJET_LEGENDAIRE)) {
			S.debloquerSucces(SUCCES_OBJET_LEGENDAIRE);
			S.affichageDeblocageSucces(SUCCES_OBJET_LEGENDAIRE, allSounds);
		}
		if (rareter == 10000) {
			allSounds[5].play();
		}
		else {
			allSounds[6].play();
		}
	}
	else {
		allSounds[4].play();
	}
	if (indiceObjet == OBJET_OEUF_TORTUE) {
		Succes S;
		S.debloquerSucces(SUCCES_OEUF_TORTUE);
		S.affichageDeblocageSucces(SUCCES_OEUF_TORTUE, allSounds);
	}
	else if (indiceObjet == OBJET_CENDRE_PHENIX) {
		Succes S;
		S.debloquerSucces(SUCCES_CENDRE_PHENIX);
		S.affichageDeblocageSucces(SUCCES_CENDRE_PHENIX, allSounds);
	}
	Bouton(300.f, 450.f, txt, sf::Color::Black, sf::Color::Green, sf::Color::Green).afficher(window);


	Bouton Continuer(340.f, 500.f, " Continuer ", sf::Color::Black, sf::Color::Green, sf::Color::Green);
	Continuer.afficher(window);

	_objetsDebloquer[indiceObjet] = 1;
	sauvegarderObjetsDebloquer();

	float  xc = 0.f, yc = 0.f;
	(*window).display();
	sf::Event event;
	do {
		while ((*window).pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition((*window));
				xc = (float)position.x;
				yc = (float)position.y;
			}
		}
	} while (!Continuer.comprendLesCoord(xc,yc,allSounds));
	(*window).display();
	(* window).clear();
}

void Objets::sauvegarderObjetsDebloquer() {
	std::ofstream os("objdblc.txt", std::ios::binary);

	for (int i = 0; i < 300; i++) {
		os.write((char*)&_objetsDebloquer[i], sizeof(_objetsDebloquer[i]));
		//os << _objetsDebloquer[i];
		//os << std::endl;
	}
	os.close();
}