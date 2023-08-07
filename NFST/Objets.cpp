#include "Objets.h"
#include <fstream>
#include "Affichage.h"
#include "Bouton.h"

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
	_listeObjets.push_back(Objet());
	_listeObjets.push_back(Objet("Antidote", 1, 100000, "Rend insensible au poison"));
	_listeObjets.push_back(Objet("Voile de feu", 2, 100000, "Les brûlures vous soignent"));
	_listeObjets.push_back(Objet("Bénédiction", 3, 1000, "Augmente la vie Maximum de 50%"));
	_listeObjets.push_back(Objet("Sceptre de druide", 4, 1000, "20% de chance qu'un soins donne également du bouclier, 10% de chance qu'ajouter du bouclier ocrtoire une protection."));
	_listeObjets.push_back(Objet("Malediction", 5, 100, "Consomme votre bouclier et reduit votre vie de 10% de votre vie max chaque tour mais augmente vos dégats de 150%"));
	_listeObjets.push_back(Objet("Cape habilete", 6, 10000, "+10% coup habile, 10% de chance que les coup habile fassent 3 fois plus de dégats et 5% de chance qu'elle fassent 4 fois plus de dégats"));
	_listeObjets.push_back(Objet("Patte de lapin", 7, 100000, "+33% vitesse, l'experience gagner au comba par ce personnage est augmenter de 33%"));
	_listeObjets.push_back(Objet("Beuh", 8, 10000, "-80% vitesse, l'experience gagner par ce personnage est multiplier par 2"));
	_listeObjets.push_back(Objet("Voile miroir", 9, 1000, "+ 6% de chance de deviation, les attaques devier sont 50% plus puissantes"));
	_listeObjets.push_back(Objet("Marshmallow", 10, 1000, "10% de chance d'absorber une attaque ennemi et de transformer les dégats en bouclier"));
	_listeObjets.push_back(Objet("Armure du protecteur", 11, 100000, "+10% de reduction de dégats, 25% de chance de recevoir une attaque qui cible un allier a sa place"));
	_listeObjets.push_back(Objet("Kunai", 12, 1000, "Toute les 3 attaques voient leurs dégats augmenter de 30%"));
	_listeObjets.push_back(Objet("Flèche transpercante", 13, 10000, "Après chaque attaques vous infliger une attaque brute avec 5% à 10% de votre force"));
	_listeObjets.push_back(Objet("Armure de Sakeratsu", 14, 100000, "+10% de reduction de dégats, renvoie 10% des dégats reçu sous forme de dégats brut a l'ennemi"));
	_listeObjets.push_back(Objet("Cape de ninja", 15, 10000, "+10% de chance d'esquive, +5% de chance de coup critique, effectuer une esquive augmente vos dégats critique de 5%"));
	_listeObjets.push_back(Objet("Dague de ninja", 16, 10000, "Augmente les dégats de 20%, après avoir effectuer une esquive vous faites une attaque brute sur l'ennemi le plus faible a hauteur de 20% à 40% de votre force "));
	_listeObjets.push_back(Objet("Soie de lapin", 17, 10, "+10% de vitesse"));
	_listeObjets.push_back(Objet("Sauciflar", 18, 100, "+5% chance de coup critique"));
	_listeObjets.push_back(Objet("J&B", 19, 100, "+10 points dans chaque stats"));
	_listeObjets.push_back(Objet("Colère de Florian ", 20, 1000, "+100 points dans chaque stats"));
	_listeObjets.push_back(Objet("Trinité", 21, 10000, "+1000 points dans chaque stats"));
	_listeObjets.push_back(Objet("Debardeur de Nicolas ", 22, 100, "+5% d'attaque"));
	_listeObjets.push_back(Objet(" Jue de pomme", 23, 100, "+5% de vie max"));
	_listeObjets.push_back(Objet("Les chaussetes de FLO", 24, 100000, "+10% force,+5% chance critique,+10% dégats critiques, 1 chance sur 5 000 d'ifnliger poison lors d'une attaque"));
	_listeObjets.push_back(Objet(" Gilet par balle", 25, 10000," Les dégats sont reduit de 1 par niveau du personnage "));
	_listeObjets.push_back(Objet("EXCALIBUR", 26, 10000, "+10000 points dans chaque stats"));
	_listeObjets.push_back(Objet("Flèches tranchantes", 27, 10000, "+7% de chance de ricochet, les ricochet font 30% de plus de dégats."));
	_listeObjets.push_back(Objet("Cote du sadomaso", 28, 10000, "Reduit de 1(+ 1 tout les 100 niveau) les dégats par coup reçu."));
	_listeObjets.push_back(Objet("Fléau du sadique", 29, 10000, "Ajoute 1(+1 tout les 100 niveau) de dégats par attaques réaliser."));
	_listeObjets.push_back(Objet("Totem immunitée", 30, 100000, "Permet de revivre avec toute sa vie une fois."));
	_listeObjets.push_back(Objet("MEMEMTOM", 31, 10000, "A chaque attaque vous avez : 1/10 de lancer une nouvelle attaque 1-10% de vos dégats attaque, 1/100 => 10-100%,1/1000 => 100-1000%"));
	_listeObjets.push_back(Objet("Jeu NES", 32, 1000, "Un jeux vidéo Nes, The Legend Of Zelda"));
	_listeObjets.push_back(Objet("Sablier", 33, 1000, "Reduit le temps des combats de moitié"));
	_listeObjets.push_back(Objet("Tardis", 34, 100000, "Reduit considérablement le temps des combats"));
	_listeObjets.push_back(Objet("Lame maléfique", 35, 1000, "+50% de dégats, reçois deux fois plus de dégats"));
	_listeObjets.push_back(Objet("Mégamorph", 36, 1000, "Recever deux fois plus de dégats quand vie superieur a 50% de votre vie maximum sinon deux fois moins"));
	_listeObjets.push_back(Objet("Némésis", 37, 10000, "Faites 50% plus de dégats a l'ennemi qui a la même position dans son equipe que vous dans la votre et recever deux fois moins de dégats de sa part"));
	_listeObjets.push_back(Objet("Casse-noix", 38, 1000, "Vous faites 50% de dégats en plus a un ennemi qui possède un bouclier et 100% a un ennemis qui possede tout son bouclier"));
	_listeObjets.push_back(Objet("Esprit du guerrier", 39, 1000, "Vous faites 1% de dégats en plus pour chaque pourceentage de point de vie qu'ils vous manquent"));
	_listeObjets.push_back(Objet("T6wins", 40, 10000, "Un ricochet envoie 2 attaques au lieu d'une"));
	_listeObjets.push_back(Objet("Oeil d'aigle", 41, 100000, "Vos attaques font des dégats supplémentaires équivalent a 1% de la vie actuelle de l'ennemi "));
	_listeObjets.push_back(Objet("Peau épaisse", 42, 100000, "Vous recever des dégats en moins équivalent a 1% de votre vie maximum "));
	_listeObjets.push_back(Objet("Dildo", 43, 100000, "Vos attaques passent a travers de la reduction de dégats et des blocages "));
	_listeObjets.push_back(Objet("Oeuf de Tortue", 44, 10000, "Permet de jouer un nouveau personnage, pas besoin de l'équiper "));
	_listeObjets.push_back(Objet("Cendre de Phénix", 45, 10000, "Permet de jouer un nouveau personnage, pas besoin de l'équiper  "));
	_listeObjets.push_back(Objet("Hantise", 46, 1000, "Le personnage equiper fais 3 fois plus de dégats s'il est KO"));
	_listeObjets.push_back(Objet("Magic 8 ball", 47, 100000, "+8% Force Vie et Vitesse et +8 dans les stats fixes"));
	_listeObjets.push_back(Objet("Spartan armor", 48, 10000, "Vous faites plus de dégats en fonction du montant d'armure actuelle jusqu'a +100%"));


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
	_tableLoot[8].push_back(_listeObjets[47]);
	for (int i = 1;i <= 8;i++) {
		_tableLoot[88].push_back(_listeObjets[47]);
	}

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