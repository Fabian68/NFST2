#include "Affichage.h"
#include "Equipes.h"
#include "Personnage.h"
#include "Bouton.h"
#include "Zones.h"
#include  <iostream>
#include "Delais.h"
#include "Objets.h"
#include "Succes.h"
#include "Aleatoire.h"

Affichage::Affichage()
{

}

void Affichage::afficherTexte(float x, float y, std::string texte, sf::Color couleurTexte, sf::RenderWindow* window)const {
	sf::Font _font;
	if (!_font.loadFromFile("arial.ttf"))
	{
		std::cout << "Erreur chargement font" << std::endl;
	}
	sf::Text text;
	text.setFont(_font);
	text.setString(texte);

	text.setFillColor(couleurTexte);
	text.setCharacterSize(12);
	text.setPosition(sf::Vector2f(x, y));
	(*window).draw(text);
}

void Affichage::affichageTexte(float x, float y, std::string texte, sf::Color couleurTexte, sf::RenderWindow* window) {
	sf::Font _font;
	if (!_font.loadFromFile("arial.ttf"))
	{
		std::cout << "Erreur chargement font" << std::endl;
	}
	sf::Text text;
	text.setFont(_font);
	text.setCharacterSize(12);
	text.setString(texte);
	text.setFillColor(couleurTexte);
	text.setPosition(sf::Vector2f(x, y));
	(*window).draw(text);
	//(*window).display();
}

sf::Color Affichage::colorRareter(int rareter)const {
	sf::Color C;
	switch (rareter) {
	case 1:
	case 10:
		C = sf::Color(128, 255, 0);
		break;
	case 2:
	case 100 :
		C = sf::Color::Blue;
		break;
	case 3:
	case 1000:
		C = sf::Color(204, 102, 0);
		break;
	case 4:
	case 10000:
		C = sf::Color::Yellow;
		break;
	case 5:
	case 100000:
		C = sf::Color(204, 0, 0);
		break;
	default:
		C = sf::Color::White;
	}
	return C;
}

void Affichage::afficherJoueurs(int indice, Equipes& Liste, sf::RenderWindow* window, std::vector< sf::Sound > &allSounds)const {
	float x = 50;
	float y = 20;
	std::string str;
	sf::Color couleurFond = sf::Color::Black;
	sf::Color couleurTexte = sf::Color::White;

	str = "Pseudo : " + Liste[indice]->nom();
	afficherTexte(x, y, str, couleurTexte, window);

	str = "Niveau : " + std::to_string(Liste[indice]->niveau());
	afficherTexte(x, y + 20.f, str, couleurTexte, window);

	str = "Force : " + std::to_string(Liste[indice]->force());
	afficherTexte(x, y + 40.f, str, sf::Color::Red, window);

	str = "Vie : " + std::to_string(Liste[indice]->vieMax());
	afficherTexte(x, y + 60.f, str, sf::Color::Green, window);

	str = "Vitesse : " + std::to_string(Liste[indice]->vitesse());
	afficherTexte(x, y + 80.f, str, sf::Color::Yellow, window);

	str = "Chance de double attaque : " + std::to_string(Liste[indice]->chanceDoubleAttaque());
	afficherTexte(x, y + 100.f, str, sf::Color::Yellow, window);

	str = "Chance de coup habile : " + std::to_string(Liste[indice]->chanceHabileter());
	afficherTexte(x, y + 120.f, str, sf::Color::Yellow, window);

	str = "Chance de deviation : " + std::to_string(Liste[indice]->pourcentageDeviation());
	afficherTexte(x, y + 140.f, str, sf::Color::Magenta, window);

	str = "Pourcentage de reduction de degats : " + std::to_string(Liste[indice]->pourcentageReduction());
	afficherTexte(x, y + 160.f, str, sf::Color::Green, window);

	str = "Chance de ricochet : " + std::to_string(Liste[indice]->pourcentageRicochet());
	afficherTexte(x, y + 180.f, str, sf::Color::Magenta, window);

	str = "Chance esquive : " + std::to_string(Liste[indice]->pourcentageEsquive());
	afficherTexte(x, y + 200.f, str, sf::Color::Yellow, window);

	str = "Chance de blocage : " + std::to_string(Liste[indice]->pourcentageBlocage());
	afficherTexte(x, y + 220.f, str, sf::Color::Green, window);

	float x2 = x - 20.f;

	x = x + 250.f;

	
	afficherTexte(x - 250.f, y + 350.f, Liste[indice]->objets().first.nom(), colorRareter(Liste[indice]->objets().first.rareter()), window);
	afficherTexte(x - 250.f, y + 390.f, Liste[indice]->objets().second.nom(), colorRareter(Liste[indice]->objets().second.rareter()), window);
	afficherTexte(x - 250.f, y + 430.f, Liste[indice]->objets2().first.nom(), colorRareter(Liste[indice]->objets2().first.rareter()), window);
	afficherTexte(x - 250.f, y + 470.f, Liste[indice]->objets2().second.nom(), colorRareter(Liste[indice]->objets2().second.rareter()), window);

	sf::RectangleShape rectangle(sf::Vector2f(470.f, 140.f));
	rectangle.setOutlineColor(couleurTexte);
	rectangle.setOutlineThickness(2.f);
	rectangle.setFillColor(couleurFond);
	rectangle.setPosition(sf::Vector2f(x + 80.f, y - 10.f));
	(*window).draw(rectangle);
	//rectangle(x + 80, y - 10, x + 550, y + 130);

	Animal A = Liste[indice]->animal();

	afficherTexte(x + 150.f, y, " Animal equiper : " + A.type(), couleurTexte, window);
	int rareter;
	if (A.indice() >= 0) {
		rareter = Liste[indice]->rareterAnimal();

		sf::RectangleShape rectangle2(sf::Vector2f(310.f, 40.f));
		rectangle2.setOutlineColor(couleurTexte);
		rectangle2.setOutlineThickness(2.f);
		rectangle2.setFillColor(couleurFond);
		rectangle2.setPosition(sf::Vector2f(x + 90.f, y + 70.f));
		(*window).draw(rectangle2);

		//rectangle(x + 90, y + 30, x + 400, y + 70);

		afficherTexte(x + 100.f, y + 40.f, " Ratio Min : ", couleurTexte, window);
		afficherTexte(x + 180.f, y + 40.f, std::to_string((int)(A.ratioMin(rareter) * 100)) + " %", colorRareter(rareter), window);
		afficherTexte(x + 230.f, y + 40.f, " Ratio Max : ", couleurTexte, window);
		afficherTexte(x + 310.f, y + 40.f, std::to_string((int)(A.ratioMax(rareter) * 100)) + " %", colorRareter(rareter), window);

		sf::RectangleShape rectangle3(sf::Vector2f(425.f, 30.f));
		rectangle3.setOutlineColor(couleurTexte);
		rectangle3.setOutlineThickness(2.f);
		rectangle3.setFillColor(couleurFond);
		rectangle3.setPosition(sf::Vector2f(x + 90.f, y + 110.f));
		(*window).draw(rectangle3);

		//rectangle(x + 90, y + 80, x + 515, y + 110);
		afficherTexte(x + 98.f, y + 90.f, " Pourcentage d'activation quand attaque ou est attaquer : ", couleurTexte, window);
		afficherTexte(x + 460.f, y + 90.f, std::to_string(A.pourcentageActivation(rareter)) + " %", colorRareter(rareter), window);
	}
	Animaux N;

	sf::RectangleShape rectangle4(sf::Vector2f(420.f, 460.f));
	rectangle4.setOutlineColor(couleurTexte);
	rectangle4.setOutlineThickness(2.f);
	rectangle4.setFillColor(couleurFond);
	rectangle4.setPosition(sf::Vector2f(x + 80.f, y + 600.f));
	(*window).draw(rectangle4);

	//rectangle(x + 80, y + 140, x + 500, y+600);

	x += 90.f;
	y += 150.f;
	afficherTexte(x + 100.f, y, "Liste des animaux posseder", couleurTexte, window);
	y += 50.f;
	std::string texteAnimaux;
	for (int i = 0; i < 9; i++) {
		if (N.animalDebloquer(Liste[indice]->id(), i, 1) && i != A.indice()) {
			texteAnimaux = Animal(i).type();
			rareter = N.rareteAnimal(Liste[indice]->id(), i);
			switch (rareter)
			{
			case 1:
				texteAnimaux += " commun";
				break;
			case 2:
				texteAnimaux += " rare";
				break;
			case 3:
				texteAnimaux += " epique";
				break;
			case 4:
				texteAnimaux += " legendaire";
				break;
			case 5:
				texteAnimaux += " cheater";
				break;
			}
			afficherTexte(x, y, texteAnimaux, colorRareter(rareter), window);
			Bouton(x + 275.f, y - 10.f, "Equiper", sf::Color::Black, sf::Color::White, sf::Color::White).afficher(window);
			y += 50.f;
		}
	}

	y = 170.f;
	afficherTexte(x + 500.f, 10.f, "Les orbes sont équiper que sur une seul stat", couleurTexte, window);
	afficherTexte(x + 500.f, 40.f, "Cliquer sur un bouton pour modifier le choix", couleurTexte, window);
	afficherTexte(x + 500.f, 70.f, "La changement s'applique quand vous quitter cet page", couleurTexte, window);
	afficherTexte(x + 500.f, y, "Liste des orbes equiper", couleurTexte, window);
	x += 440.f;
	Orbes O;
	std::string texteOrbe;
	bool OrbeChoisit = false;

	for (int i = 1, k = 220; i <= 5; i++) {
		if (O.orbeDebloquer(indice, i)) {
			switch (i) {
			case 1:
				texteOrbe = " commune ( 1 ";
				break;
			case 2:
				texteOrbe = " rare ( 2 ";
				break;
			case 3:
				texteOrbe = " epique ( 3 ";
				break;
			case 4:
				texteOrbe = " LEGENDAIRE ( 4 ";
				break;
			case 5:
				texteOrbe = " CHEATER ( 5 ";
				break;
			}
			texteOrbe += "S/ LVL ) Equiper : ";
			afficherTexte(x, (float)k, texteOrbe, colorRareter(i), window);
			for (int jj = 1, xpas = 0; jj <= 3; jj++) {
				if (O.choixOrbe(indice, i) != jj) {
					switch (jj) {
					case 1:
						Bouton(x + 210.f + (float)xpas, (float)k - 10.f, "ATK", sf::Color::Black, sf::Color::White, sf::Color::White).afficher(window);
						break;
					case 2:
						Bouton(x + 210.f + (float)xpas, (float)k - 10.f, "VIE", sf::Color::Black, sf::Color::White, sf::Color::White).afficher(window);
						break;
					case 3:
						Bouton(x + 210.f + (float)xpas, (float)k - 10.f, "VIT", sf::Color::Black, sf::Color::White, sf::Color::White).afficher(window);
						break;
					}
					xpas += 50;
				}
			}
			k += 50;
		}
	}
	Experiences E;

	Bouton Retour(300.f, 700.f, "RETOUR");
	Retour.afficher(window);
	Bouton Precedent(450.f, 700.f, "Precedent");
	Precedent.afficher(window);
	Bouton Suivant(600.f, 700.f, "Suivant");
	Suivant.afficher(window);

	Bouton AjouterObjet1(250.f, 350.f, "Changer");
	AjouterObjet1.afficher(window);
	Bouton AjouterObjet2(250.f, 400.f, "Changer");
	AjouterObjet2.afficher(window);

	Zones Z = Zones();

	Bouton AjouterObjet3(250.f, 450.f, "Changer");
	Bouton AjouterObjet4(250.f, 500.f, "Changer");
	if (Z.niveauMax() >= 25) {

		AjouterObjet3.afficher(window);
		AjouterObjet4.afficher(window);
	}
	bool equiperAnimal = false;


	float  xc=0.f, yc=0.f;
	(*window).display();
	sf::Event event;
	do {
		while ((*window).pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition((*window));
				xc = (float)position.x;
				yc = (float)position.y;
				for (int i = 0, k = 210; i < 9; i++) {
					if (N.animalDebloquer(Liste[indice]->id(), i, 1) && i != A.indice()) {
						if (Bouton(665.f, (float)k, "Equiper").comprendLesCoord(xc, yc,allSounds)) {

							N.setAnimalPersonnage(indice, i);
							Liste[indice]->setAnimal(Animal(i));
							equiperAnimal = true;
						}
						k += 50;
					}
				}
				for (int i = 1, k = 220; i <= 5; i++) {
					if (O.orbeDebloquer(indice, i)) {
						for (int jj = 1, xpas = 0; jj <= 3; jj++) {
							if (O.choixOrbe(indice, i) != jj) {
								if (Bouton(x + 210.f + (float)xpas, (float)k - 10.f, "ATK", sf::Color::Black, sf::Color::White, sf::Color::White).comprendLesCoord(xc, yc,allSounds)) {
									O.setChoixOrbe(indice, i, jj);
									OrbeChoisit = true;
								}
								xpas += 50;
							}
						}
						k += 50;
					}
				}
			}
		}


	} while (!Retour.comprendLesCoord(xc, yc,allSounds) && !Suivant.comprendLesCoord(xc, yc,allSounds) && !equiperAnimal && !Precedent.comprendLesCoord(xc, yc,allSounds) && !OrbeChoisit && !AjouterObjet1.comprendLesCoord(xc, yc,allSounds) && !AjouterObjet2.comprendLesCoord(xc, yc,allSounds) && !AjouterObjet3.comprendLesCoord(xc, yc,allSounds) && !AjouterObjet4.comprendLesCoord(xc, yc,allSounds));

	if (Suivant.comprendLesCoord(xc, yc,allSounds)) {
		indice = (indice + 1) % Liste.taille();
		(*window).clear();
		afficherJoueurs(indice, Liste, window,allSounds);
	}
	else if (Precedent.comprendLesCoord(xc, yc,allSounds)) {
		indice--;
		if (indice < 0) {
			indice = Liste.taille() - 1;
		}
		(*window).clear();
		afficherJoueurs(indice, Liste, window,allSounds);
	}
	else if (equiperAnimal || OrbeChoisit) {
		(*window).clear();
		afficherJoueurs(indice, Liste, window,allSounds);
	}
	else if (AjouterObjet1.comprendLesCoord(xc, yc,allSounds)) {
		Objets obj;
		(*window).clear();
		choixObjets(1, obj, true, indice, Liste, window,allSounds);
	}
	else if (AjouterObjet2.comprendLesCoord(xc, yc,allSounds)) {
		Objets obj;
		(*window).clear();
		choixObjets(1, obj, false, indice, Liste, window,allSounds);
	}
	else if (AjouterObjet3.comprendLesCoord(xc, yc,allSounds) && Z.niveauMax() >= 25) {
		Objets obj;
		(*window).clear();
		choixObjets(1, obj, true, indice, Liste, window,allSounds, 2);
	}
	else if (AjouterObjet4.comprendLesCoord(xc, yc,allSounds) && Z.niveauMax() >= 25) {
		Objets obj;
		(*window).clear();
		choixObjets(1, obj, false, indice, Liste, window,allSounds, 2);
	}
	(*window).display();
	(*window).clear();
}

void Affichage::afficherCompetences(int indice, Equipes& Liste, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds) const
{
	float x = 50;
	float y = 20;
	std::string str;
	sf::Color couleurFond = sf::Color::Black;
	sf::Color couleurTexte = sf::Color::White;
	sf::Color couleurTexteG = sf::Color::Green;

	int DEGATS;
	int SOINS;
	str = "Pseudo : " + Liste[indice]->nom();
	afficherTexte(x+100.f, y, str, couleurTexte, window);

	str = "Passif ";
	afficherTexte(x, y + 10.f, str, couleurTexteG, window);
	switch (indice) {
		case 0:
			str = "Gagne force/(7/5/3/2) + niveau de dégats supplémentaires. Niveau (1/10/100/1000) Valeur actuelle : " + std::to_string(Liste[indice]->status().adducteur());
			str = str + "\n" + "Recois niveaux dégats en moins, Valeur actuel : "+ std::to_string(Liste[indice]->niveau());
			break;
		case 1:
			str = "Emmagasine 10% des dégats reçu, insensible au brulures, possède un compteur de tour qui est augmenté de 1 à chaque tour joué (CT) ";
			break;
		case 2:
			str = "Aucun";
			break;
		case 3:
			str = "Aucun";
			break;
		case 4:
			str = "Reduction de dégats du personnage = 100 x ( 1 - vie actuel/ vie maximum) %";
			str = str + "\n" + "Ratio attaque (RA) = vie maximum / vie actuel, maximum 30";
			break;
		case 5:
			str = "Commence avec 5% de chance de coup critique bonus et 25% de dégats critique bonus, à chaque tour attaque l'ennemi le plus faible pour 5-25% de votre force x dégats critiques";
			str = str + "\n" + "Insensible au poison";
			break;
		case 6:
			str = "Ratio attaque RA = vitesse/force ";
			break;
		case 7:
			str = "Lors de son tour augmente sa vie maximum à hauteur de son niveau";
			break;
		case 8:
			str = "Aucun";
			break;
		case 9:
			str = "Aucun";
			break;
		case 10:
			str = "Aucun";
			break;
		case 11:
			str = "Aucun";
			break;
		case 12:
			str = "Possede 10 fois plus de points de vies";
			break;
		case 13:
			str = "Ne joue son tour que si un tirage habile est concluant";
			break;
		case 14:
			str = "Les statistiques sont améliorés au niveau 9/99/999, réduit les dégats à hauteur de 2 x sont niveau, emmagasine les dégats";
			break;
		case 15:
			str = "Aucun";
			break;
		case 16:
			str = "Les statistiques sont améliorés selon le temps joué Taille = T (1 à 4) sur le personnage,les améliorations redescendent à zéro si le personnage tombe KO";
			str = str + "\^n" + "+ niveau dégats et -niveau de reduction de dégats fixe";
			break;

	}
	afficherTexte(x, y + 30.f, str, couleurTexte, window);

	str = "Passif par tour";
	afficherTexte(x, y + 90.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Tout les 17 tours vous gagnez 7% de réduction de dégats";
		str = str + "\n" + "Tout les 70 tours vous gagnez 17% de force ";
		break;
	case 1:
		str = "Tout les 5 tours emmagasine 2% de ses points de vie maximum, val potentiel :" + std::to_string((int)Liste[indice]->vieMax()/50);
		str = str + "\n" + "Se bouclier également pour 10% de sa vie max, Valeur actuel : " + std::to_string((int)Liste[indice]->vieMax()/5);
		break;
	case 2:
		str = "Tout les 5 tours se soigne pour 30-60% de votre force, soins potentiel :" + std::to_string(Liste[indice]->soins(0.2, 0.4));
		break;
	case 3:
		str = "A 25 tour ajoute un lapin dans l'équipe avec un animal qui soigne et bouclier de zone, a 50 tour un sanglier,ils bénéficient de stats supplémentaire équivalent à 10% des stats de Fiona";
		str = str + "\n" + "Tout les 17 tours ajoute 7% chance de coup critique, si habile ajoute également 7% de dégats critique";
		str = str + "\n" + "Tout les 70 tours ajoute 17% de dégats critique et attaque l'ennemi le plus fort 17 fois pour 17%-(18%+1,7% x numéro coup)force, somme dégats potentiel => ";
		DEGATS = 0;
		for (size_t i = 0; i < 17; i++)
		{
			DEGATS += Liste[indice]->degats(0.17, 0.18 + 0.017 * i);
		}
		str = str + std::to_string(DEGATS);
		break;
	case 4:
		str = "Aucun";
		break;
	case 5:
		str = "Tout les 10 tours ajoute 1% chance de coup critique et 2% de dégats critiques";
		break;
	case 6:
		str = "Se soigne à hauteur de 5,9% de sa vie maximum, ou bouclier si sa vie est au maximum";
		break;
	case 7:
		str = "Tout les 5 tours ajoute force equivalent à niveau/10 et vie maxmimum à hauteur de niveau (x10 si habile et double attaque)";
		str = str + "\n" + "Tout les 30 tours se soigne et bouclier intégralement";
		break;
	case 8:
		str = "Si le personnage n'a pas été attaqué pendant 4 tours, recharge son bouclier à son maximum";
		break;
	case 9:
		str = "Tout les 5 tours reduit sa vie actuel de 10% et ajoute 1% de reduction aux dégats";
		break;
	case 10:
		str = "Tout les 8 tours attaque brut l'ennemi le plus proche avec ratio = reduction de dégats de l'ennemi/50, dégats = (ratio)-(ratio*3+1)% de votre force";
		break;
	case 11:
		str = "Tout les 10 tours augmente les chance d'habilete,double attaque et de coup critique de 2% ainsi que 6% de dégats critique en plus à tout les alliers, x 2 si habile";
		break;
	case 12:
		str = "Tout les 10 tours permet de faire gagner de l'xp selon son niveau : 1/7/70/700/7000 au niveau 1/70/700/7000, les alliers ko bénéficient aussi de l'xp";
		str = str + "\n" + "Au tour 10/20/30/60/80/100/130/160/200 partage 2/2/2/4/4/4/10/10/10% de sa vie max à un allier aléatoire et perd 10/10/10/5/5/5/3/3/3% de sa vie max";
		break;
	case 13:
		str = "Tout les 10 tours se soigne à hauteur de 20% de ses points de vie actuel";
		break;
	case 14:
		str = "Tout les tours soigne 10% de ses pv manquent et bouclier 10% du bouclier manquent";
		break;
	case 15:
		str = "Tout les tours augmente la vie max à hauteur de 10% de sa force, puis 10% si habile puis une seconde fois 10% si habile";
		str = str + "\n" + "Tout les 100 tours attaque l'ennemi à hauteur de 111-211% de votre force, si tirage habile l'attaque est brut";
		break;
	case 16:
		str = "Tout les tours soigne 10% de ses pv manquent et bouclier 10% du bouclier manquent";
		break;
	}
	afficherTexte(x, y + 110.f, str, couleurTexte, window);

	str = "Passif defensif";
	afficherTexte(x, y + 160.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Vous augmenter votre reduction de dégats de 1";
		break;
	case 1:
		str = "Attaque l'attaquant pour (1% 0,1% x CT)+ des pv max, valeur sans compteur : " + std::to_string((int)Liste[indice]->vieMax() / 100);
		break;
	case 2:
		str = "Lance un jet d'habilete, si concluant ajoute 1% de reduction de dégats au coéquipier le plus faible et un compteur de protection";
		str = str + "\n" +"puis vous ajouter un bouclier à vous même équivalent à 4 % de votre vie actuel, bouclier potentiel : " + std::to_string((double)Liste[indice]->vie() * 0.04);
		break;
	case 3:
		str = "Aucun";
		break;
	case 4:
		str = "Emmagasine 10% des dégats reçu";
		break;
	case 5:
		str = "Peut se bouclier selon son pourcentage d'esquive à hauteur de 25% de sa vitesse";
		break;
	case 6:
		str = "Aucun";
		break;
	case 7:
		str = "Aucun";
		break;
	case 8:
		str = "Ajoute 1% chance de double attaque";
		break;
	case 9:
		str = "Aucun";
		break;
	case 10:
		str = "Augmente votre bouclier à hauteur de votre niveau";
		break;
	case 11:
		str = "Vous vous soiigner à hauteur de 20-80% de votre force";
		break;
	case 12:
		str = "Aucun";
		break;
	case 13:
		str = "Se bouclier à hauteur de 1% de vos points de vie maximum + niveau";
		break;
	case 14:
		str = "Si tirage habile, attaque l'ennemi le plus proche à hauteur de 1% de ses pv max";
		str = str + "\n" + "et ajoute 1% de reduction de dégats à l'allier le moins résistant ainsi qu'un compteur de protection";
		break;
	case 15:
		str = "augmente la vie max à hauteur de 10% de sa force, puis 10% si habile puis une seconde fois 10% si habile";
		break;
	case 16:
		str = "Taille = T (1 à 4) selon le temps joué, attaque brut l'ennemi le plus proche pour (1 x T)-(2 + 2 x T)% de votre force";
		break;
	}
	afficherTexte(x, y + 180.f, str, couleurTexte, window);

	str = "Compétence 1 ";
	afficherTexte(x, y + 230.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Attaque l'ennemi le plus proche avec un ratio de 20-40% de votre attaque + 10-30% de votre vitesse , +1 mana";
		DEGATS = Liste[indice]->degats(0.2, 0.4);
		DEGATS += Liste[indice]->degats(0.1, 0.3, CHOIXVITESSE);
		str = str + "\n" + "Dégats potentiels : " + std::to_string(DEGATS);
		break;
	case 1:
		DEGATS = Liste[indice]->degats(0.2, 0.6);
		str = "Attaque l'ennemi le plus proche avec un ratio de 20-60% de votre attaque, dégats x 2 si l'ennemi à moins de force que vous, + 1 mana, dégats possibles : " + std::to_string(DEGATS) + " ou " + std::to_string(DEGATS*2);
		break;
	case 2:
		DEGATS = Liste[indice]->degats(0.1, 0.30);
		DEGATS += (int)(0.03 * (double)Liste[indice]->vie() + 0.01 * (double)Liste[indice]->vieMax());
		str = "Attaque l'ennemi le plus proche pour 10-30% de votre force +3% de vos point de vie actuel + 1% de vos point de vie maximum, + 1 mana, dégats potentiel : " + std::to_string(DEGATS);
		DEGATS = (int)(Aleatoire(0.01, 0.05).decimal() * ((double)Liste[indice]->vie() + (double)Liste[indice]->bouclier()));
		str = str + "\n" + "Lance un jet d'habileté, si concluant attaque l'équipe ennemi pour 1-5% de votr vie actuel + bouclier actuel,+1 mana, dégats potentiel :" + std::to_string(DEGATS);
		break;
	case 3:
		str = "Attaque l'ennemi le plus proche pour 40-80% de votre force, double attaque re attaque l'ennemi le plus proche pour 25-95% de votre force, + 1 mana, degats potentiels :  " + std::to_string(Liste[indice]->degats(0.4, 0.80)) + " et " + std::to_string(Liste[indice]->degats(0.25, 0.95));
		break;
	case 4:
		str = "Attaque l'ennemi le plus proche (1 + RA/2) fois pour (RA/30)-(RA/15)% de votre force pour chaque attaque, +(1+RA/10) mana";
		break;
	case 5:
		str = "Attaque l'ennemi le plus proche pour 45-75% de votre force, si attaque double : attaque brut l'ennemi le plus faible pour 12-24% de votre force, +2 mana";
		break;
	case 6:
		str = "Ataque jusqu'a 7 fois l'ennemi le plus faible pour 15-35% de sa vitesse si tirage habile, + 1 mana";
		break;
	case 7:
		str = "Attaque un ennemi aléatoire à hauteur de 0,1-1% de sa force puis 100-150% si tirage habile, si tirage habile + 2 mana sinon + 1";
		break;
	case 8:
		str = "CA = compteur attaque, Attaque (vitesse x 5)/force fois l'ennemi le plus proche pour (1+CA/100)-(2+CA/50)% de votre force, compteur attaque augmente de 1 ";
		str = str + "\n" + "Chaque attaque peut attaquer une seconde fois si attaque double et la rafalle d'attaque aussi peut être affecté, + 1 mana";
		break;
	case 9:
		str = "Bouclier chaque allier à hauteur de 10-30% de votre force, bouclier une seconde fois si double attaque, + 1 mana";
		break;
	case 10:
		str = "Attaque l'ennemi le plus proche à hauteur de 80-120% de votre force, +1 mana";
		break;
	case 11:
		str = "Se bouclier à hauteur de 25-75% de votre bouclier puis si double attaquue ou vie au maximum vous attaquer l'ennemi le plus proche à hauteur de 37-97% de votre force, + 1 mana";
		break;
	case 12:
		str = "Attaque l'ennemi le plus proche à hauteur de 20-40% de votre force, + 1 mana";
		break;
	case 13:
		str = "Enchaine jusqu'à 6 attaques(ennemi plus proche), chaque attaque se délanche si habile et incrémente un compteur K qui commence à 1 et multiplié par deux par attaque lancé";
		str = str + "\n" + " si double attaque compteur/2 et re-enchaine jusqu'a 6 attaques, Dégats pour chaque coups : (5 + 0,25 x K) - (5 + 2,5 x K)% de votre force dégats, + 1 mana";
		break;
	case 14:
		str = "Attaque l'ennemi le plus proche à hauteur de 21-52% de sa force + 10% de son emmagasination, retire l'emmagasination, + 1 mana";
		break;
	case 15:
		str = "Attaque l'ennemi le plus proche à hauteur de 1-2% de votre vie max + 10-20% de votre force, + 1 mana";
		str = str + "\n" + "Si tirage habile attaque brut l'ennemi le plus proche à hauteur de 0,5-1% de votre vie max + 5-10% de votre force, + 1 mana";
		break;
	case 16:
		str = "Attaque taille fois l'ennemi le plus proche pour 45-85% de votre force, + 1 mana, ré-attaque si attaque double";
		break;
	}
	afficherTexte(x, y + 250.f, str, couleurTexte, window);

	str = "Compétence 2 ";
	afficherTexte(x, y + 320.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Attaque plusieurs fois l'ennemi le plus fort, le nombre de coup = 3 + vitesse/niveau, compteur d'attaque = 0 et augmente de 1 à chaque attaque (CA), -1 mana ";
		str = str + "\n" + " ratio = (1,7% + 1,7% x CA) - (17% + 3,4% x CA) : " ;
		DEGATS = 0;
		for (int i = 0; i <= (3 + Liste[indice]->vitesse() / Liste[indice]->niveau()); i++) {
			DEGATS += Liste[indice]->degats(0.017 + i * 0.017, 0.17 + i * 0.034);
		}
		str = str + "Dégats potentiels : " + std::to_string(DEGATS);
		str = str + "\n" + " Double attaque ratio = (17% + 1,7% x CA) - (17% + 7,0% x CA) : ";
		DEGATS = 0;
		for (int i = 0; i <= (3 + Liste[indice]->vitesse() / Liste[indice]->niveau()); i++) {
			if (Liste[indice]->attaqueDouble()) {
				DEGATS += Liste[indice]->degats(0.17 + i * 0.017, 0.17 + i * 0.07);
			}
		}
		str = str + "Dégats potentiels : " + std::to_string(DEGATS);
		str = str + "\n" + " Si habile attaque brut sur l'ennemi le plus proche egalement = (1,7% + 1,7% x CA) - (7% + 7,0% x CA) : ";
		DEGATS = 0;
		for (int i = 0; i <= (3 + Liste[indice]->vitesse() / Liste[indice]->niveau()); i++) {
			if (Liste[indice]->habile()) {
				DEGATS += Liste[indice]->degats(0.017 + i * 0.017, 0.07 + i * 0.07);
			}
		}
		str = str + "Dégats potentiels brut : " + std::to_string(DEGATS);
		break;
	case 1:
		str = "Ajoute + 1 reduction de dégats à chaque membre de l'équipe, + 1 si double attaque, + 1 si habile, - 1 mana";
		break;
	case 2:
		str = "Attaque l'equipe ennemi pour 10-20% de votre attaque à 60%-120% par ennemis selon sa position plus au centre et selon le nombre d'ennemis, ennemi au centre prend deux coups,-1 mana";
		break;
	case 3:
		str = "Soigne 7 fois un allier aléatoire pour 10-25% de votre force si tirage habile, si double attaque 5-50% soins potentiels, + 1 mana";
		break;
	case 4:
		str = "Attaque l'ennemi le plus proche pour (RA/8)-(RA/4)% de votre force + l'emmegasination + 20% du bouclier actel si bouclier > 50% bouclier max et retire 50% du bouclier max, - 1 mana";
		break;
	case 5:
		str = "Attaque l'ennemi le plus faible à hauteur de 15-45% de votre force x le ratio (vie/vie max) de l'adversaire (max 20), -1 mana";
		break;
	case 6:
		str = "Attaque l'equipe ennemi pour (RA/14)-(RA/10)% de votre force - 1 mana ";
		str = str + "\n" + "Si habile à la place : Soigne l'équipe pour (RA/16)-(RA/12)% de votre force et bouclier pour (RA/32)-(RA/24)% de votre force, +1 mana";
		break;
	case 7:
		str = "Se soigne 1 à 100 fois (si habile pour chaque coups) avec compteur numero du soins NS, soins = (NS/1 000)-(NS/1 000 + 1)% de votre force";
		str = str + "\n" + "et ajoute vie maximal à hauteur de vie max / 1 000 pour chaque soins, +1 mana";
		break;
	case 8:
		str = "Attaque l'ennemi le plus faible pour 25-50% de votre force, si attaque double reattaque pour 50-100%, si double attaque reattaque pour 75-150% de votre force, -1 mana";
		break;
	case 9:
		str = "Ajoute 3 compteur de protection, 3% de reduction de dégats et niveau/20 de Force à un allier, bonus x 2 si habile, + 1 mana";
		break;
	case 10:
		str = "Se soigne à hauteur de 20-60% de votre force et bouclier à hauteur de 10-30% de votre force, si vie et bouclier au maximum utilie une autre attaque à la place, + 1 mana";
		break;
	case 11:
		str = " Se soigne à hauteur de 45-85% de sa force puis si habile et vie au maximum attaque l'équipe adverse à hauteur de 15-25% de votre force + 1-3% vie max + 3-9% vie actuel, - 1 mana ";
		break;
	case 12:
		str = "Se soigne à hauteur de 0,5% de sa vie max + 3% de sa vie actuel puis augmente ses points de vie maximum à hauteur de niveau * 10, + 1 mana";
		break;
	case 13:
		str = "Lance un compteur K de 1 à 25 et qui s'incrémente de 1, pour chaque itération elle s'attaque pour (K/100)-(K/50)% de votre force";
		str = str + "\n" + "puis se soigne pour (K/200)-(K100)% de sa force et augmente sa vie max à hauteur de son niveau/100, -1 mana";
		break;
	case 14:
		str = "Remplie 20% du bouclier maximum, + 0 mana";
		str = str + "\n" + " Si le bouclier était au maximum : Emmagasine le bouclier et le réduit à zero, - 1 mana";
		break;
	case 15:
		str = "Nombre d'alliés en vie = NA, soigne toute l'équipe à hauteur de (1/NA)-(4/NA)% de votre force et bouclier pour (0,5/NA)-(2/NA)% de votre force, -1 mana ";
		break;
	case 16:
		str = "Compétence disponible si taile = 2 ou plus : Soigne les brulures et poisons de tout les alliers puis ";
		str = str + "\n" + "Soigne l'équipe pour (20 x (T-1))-(40 x (T-1))% de votre force, -1 mana";
		break;
	}
	afficherTexte(x, y + 340.f, str, couleurTexte, window);

	str = "Compétence 3 ";
	afficherTexte(x, y + 410.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Augmente les chances de coup critique de 2% et les dégats critiques de 7%, -1 mana";
		break;
	case 1:
		str = "Attaque l'ennemi le plus fort pour 20-40% de la force +200% de l'emmagasination, -2 mana -100% emmagasination";
		str = str + "\n" + "Si double attaque : Attaque l'ennemi le plus fort pour 40-80% de la force +100% de l'emmagasination ";
		break;
	case 2:
		str = "Soigne l'équipe pour 8%-32% de votre force, + 1 mana, soins potentiel : " + std::to_string(Liste[indice]->soins(0.08, 0.32));
		break;
	case 3:
		str = " - 1% de reduction de dégats à l'énnemi le plus proche, attaque 3 fois successivement l'ennemi le plus fort pour (20/40/60)-(30/60/90)% de votre force, -2 mana";
		str = str + "\n" + "Double attaque : - 1% de reduction de dégats à l'énnemi le plus proche, attaque 3 fois successivement l'ennemi le plus fort pour (30/60/90)-(40/80/120)% de votre force";
		break;
	case 4:
		str = "Attaque l'ennemi le plus proche RA fois pour (RA/10)-(RA/5)% de votre force pour chaque attaque, - 2 mana";
		break;
	case 5:
		str = "Attaque l'ennemi le plus éloigné pour 75-175% de votre force, attaque double : attaque l'ennemi le plus faible pour 50-150% de votre vitesse, -2 mana";
		break;
	case 6:
		str = "Déclenche le passif par tour et ajoute 1 mana";
		break;
	case 7:
		str = "Réduit la reduction de dégats de toute l'équipe adverse de 2%";
		break;
	case 8:
		str = "Attaque l'ennemi le plus proche pour 150-250% de votre force, -2 mana";
		break;
	case 9:
		str = "Soigne le premier coéquipier à hauteur de 10-20% de votre et chaque nouvelle allier avec un soins deux fois plus fort jusqu'a l'allier au fond, - 2 mana";
	case 10:
		str = "Ajoute 1% chance de coup critique et 5% de dégats critique, +1 mana";
		break;
	case 11:
		str = "Soigne l'équipe à hauteur de 25-50% de votre force puis si habile, double attaque et vie au maximum attaque l'équipe adverse à hauteur de 20-60% de votre force + 60-180% de votre vitesse, -2 mana";
		break;
	case 12:
		str = "Soigne l'équipe à hauteur de 22-72% de votre force, + 1 mana";
		break;
	case 13:
		str = "S'ajoute 3% de chance de coup critique et 6% de dégats critique, x 2 si habile, -2 mana";
		break;
	case 14:
		str = "Soigne ses brulures, et empoisonnement ainsi que 10% de sa vie maximum, -2 mana";
		break;
	case 15:
		str = "Se bouclier à hauteur de 25-75% de votre force puis soigne à hauteur de 50-150% de votre force, puis ajoute 5% reduction de dégats,-2 mana";
		break;
	case 16:
		str = "Compétence disponible si taile = 3 ou plus : Ajoute T chance de double attaque, chance habileter et chance coup critique";
		str = str + "\n" + "T/2 reduction de dégats et chance de ricochets, T x 2 compteurs de protections et T x 2 +2 dégats critiques, -2 mana";
		break;
	}
	afficherTexte(x, y + 430.f, str, couleurTexte, window);

	str = "Compétence 4 ";
	afficherTexte(x, y + 500.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Si vous avez pas toute votre vie et tout votre bouclier, vous soigne et bouclier intégralement - 3 Mana";
		str = str + "\n" + "Sinon attaque la cible la plus faible pour 50-150% de votre force + 75-125% de votre vitesse, -2 mana";
		DEGATS = Liste[indice]->degats(0.5, 1.5);
		DEGATS += Liste[indice]->degats(0.75, 1.25, CHOIXVITESSE);
		str = str + " Dégats potentiels : " + std::to_string(DEGATS);
		break;
	case 1:
		str = "Augmente la force de tout les alliers de 5%";
		break;
	case 2:
		str = "Attaque l'ennemi le plus fort pour 8% de votre vie actuel + 2% de vos pv max + 8% de votre bouclier + 40% de votre force, - 3 mana, dégats potentiel : " + std::to_string((int)(0.08 * (double)Liste[indice]->vie() + 0.02 * (double)Liste[indice]->vieMax() + 0.08 * (double)Liste[indice]->bouclier() + 0.40 * (double)Liste[indice]->force()));
		break;
	case 3:
		str = "Ajoute 3% de chance de coup habileter, reduit la résistance de l'ennemi le plus proche de 7%, puis attaque pour 70-170% de votre force, -3 mana, double attaque 117/177%";
	case 4:
		str = " Augmente l'emmagasination à hauteur de 10% de votre vie, ajout 10 compteur de protection et reduisier vos points de vies actuels de moitié,-3 mana";
		break;
	case 5:
		str = "Ajoute 1% chance coup critique et 5% de dégats critiques, si habile bonus x 2,et se soigne à hauteur de 50-250% de votre force, ou bouclier à hauteur de 25-125% si vie au maximum, -3 mana ";
		break;
	case 6:
		str = "Attaque chaque ennemis de l'équipe adverse en commencent par le personnage du début, compteur j= 1 et multiplié par deux pour chaque nouvelle ennemi attaqué";
		str = str + "\n" + "Degats = (j+20)% de votre vitesse, -3 mana";
		break;
	case 7:
		str = "Attaque un ennemi aléatoire à hauteur de 100-200% de votre force + 50-100% de votre vitesse";
		break;
	case 8:
		str = "Attaque l'equipe ennemi pour 10-40% de votre attaque à 50%-200% par ennemis selon sa position plus au centre et selon le nombre d'ennemis, ennemi au centre prend deux coups,-3 mana, dégats potentiel :";
		break;
	case 9:
		str = "Attaque l'equipe adverse à hauteur de 100-200% de votre force, -3 mana";
		break;
	case 10:
		str = "Point de mana du personnage = PM, attaque l'ennemi le plus proche à hauteur de (PM/3)-(PM/2)% de votre force + 50-100% de votre bouclier,reduit le bouclier à 0 et le mana à 0";
		break;
	case 11:
		str = "Attaque un ennemi aléatoire à hauteur de 5-350% de votre force,-3 mana";
		break;
	case 12:
		str = "Ajoute 15% de reduction de dégats au coéquipier le moins résistant et un compteur de protection, -3 mana";
		break;
	case 13:
		str = "Double sa force et sa vitesse,mutliplie sa vie par 10,augmente ses chances de coup habile de 20%,- 3 mana";
		str = str + "\n" + "Si déja transformé ajoute 3 points de mana";
		break;
	case 14:
		str = "Attaque l'équipe adverse à hauteur de 1,5% de sa vie actuel + 0,5% de ses points de vie max + 50% de sa force + 100% de sa force, -3 mana";
		break;
	case 15:
		str = "Première transformation : Reduit de 90% sa vie maximum et double sa force, +10% reduction de dégats, - 3 mana";
		str = str + "\n" + "Deuxième transformation (si première transformation et mana superieur à 9) : Reduit de 90% la vie maximum, double la force et +20% reduction de dégats";
		str = str + "\n" + "Si les deux transformations on étés faites : Augmente vie max à hauteur de niveau/10 et soigne pour 20-120% de votre force et bouclier pour 10-60% de votre force";
		break;
	case 16:
		str = "Compétence disponible si taile = 4 (max) : Attaque l'équipe ennemi pour 100-400% de votre force";
		break;
	}
	afficherTexte(x, y + 520.f, str, couleurTexte, window);

	Bouton Retour(300.f, 700.f, "RETOUR");
	Retour.afficher(window);
	Bouton Precedent(450.f, 700.f, "Precedent");
	Precedent.afficher(window);
	Bouton Suivant(600.f, 700.f, "Suivant");
	Suivant.afficher(window);

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

	} while (!Retour.comprendLesCoord(xc, yc, allSounds) && !Suivant.comprendLesCoord(xc, yc, allSounds) && !Precedent.comprendLesCoord(xc, yc, allSounds));

	if (Suivant.comprendLesCoord(xc, yc, allSounds)) {
		indice = (indice + 1) % Liste.taille();
		(*window).clear();
		afficherCompetences(indice, Liste, window, allSounds);
	}
	else if (Precedent.comprendLesCoord(xc, yc, allSounds)) {
		indice--;
		if (indice < 0) {
			indice = Liste.taille() - 1;
		}
		(*window).clear();
		afficherCompetences(indice, Liste, window, allSounds);
	}
	(*window).display();
	(*window).clear();
}

void Affichage::afficherMecaniques(sf::RenderWindow* window, std::vector<sf::Sound>& allSounds) const
{
	float x = 50;
	float y = 20;
	std::string str;
	sf::Color couleurFond = sf::Color::Black;
	sf::Color couleurTexte = sf::Color::White;

	str = "Statistiques :";
	str = str + "\n" + "Attaque : Statistique principale pour les dégats et soins";
	str = str + "\n" + "Vie : Statistique pour avoir plus de vie (Point de vie = 10x la statistique vie)";
	str = str + "\n" + "Vitesse : Permet d'attaquer plus souvent, pris en compte avant le combat pour initialiser les priorités";
	afficherTexte(x, y, str, couleurTexte, window);

	str = "Double attaque : Permet d'attaquer deux fois sur certaines attaques, certains effets sur certains personnages.";
	afficherTexte(x, y+60.f, str, sf::Color::Green, window);

	str = "Coup habile : Permet d'avoir les dégats et soins multiplié par deux";
	afficherTexte(x, y + 80.f, str, sf::Color::Yellow, window);
	
	str = "Coup critique : Un coup critique permet de faire des dégats/soins critiques, de base 5% de chances de faire 50% de dégats/soins supplémentaires";
	afficherTexte(x, y + 100.f, str, sf::Color::Red, window);

	str = "Pourcentage de reduction de dégats : Reduit les dégats reçu en pourcentage, ne fonctionne pas avec les dégats brut";
	afficherTexte(x, y + 120.f, str, sf::Color::Green, window);

	str = "Pourcentage de déviation : Renvoie une attaque après le calcul des dégats, ne fonctionne pas avec les attaques brut,le passif défensif ne s'applique pas";
	afficherTexte(x, y + 140.f, str, sf::Color::Magenta, window);

	str = "Pourcentage de blocage : Une attaque bloqué bloque 50% des dégats, ne fonctionne pas avec les attaques brut";
	afficherTexte(x, y + 160.f, str, sf::Color::Cyan, window);
	
	str = "Pourcentage d'esquive : Une attaque esquivé ne fait aucun dégats, le passif défensif n'est pas appliqué";
	afficherTexte(x, y + 180.f, str, sf::Color::Yellow, window);

	str = "Pourcentage de ricochet : Permet de relancer une attaque sur une cible aléatoire après calcul des dégats";
	afficherTexte(x, y + 200.f, str, sf::Color::Magenta, window);

	str = "Le bouclier : Le bouclier est la barre en dessous des points de vie, le bouclier est réduit avant les points de vies.";
	str = str + "\n" + "Montant de bouclier maximum : (Force * 10 + vie_max)/4";
	afficherTexte(x, y + 220.f, str, sf::Color::Magenta, window);

	str = "Compteur de protection : Prochaine attaque à des dégats diviser par 2, le compteur décrémente.";
	str = str + "\n" + "Compteur de fragilisation : Prochaine attaque à des dégats multiplié par 2, le compteur décrémente.";
	afficherTexte(x, y + 250.f, str, sf::Color::Green, window);

	str = "Attaque brut : Une attaque brut n'active pas les passif et animaux, les dégats ne sont pas réduits";
	afficherTexte(x, y + 280.f, str, sf::Color::Red, window);

	str = "Status brulé : Reduit de 1 à 10% des pv max par tour du personnage brulé, augmente de 1% chaque tour";
	afficherTexte(x, y + 300.f, str, sf::Color::Red, window);

	str = "Status empoisonné : Incurable, dégats très très faible au départ mais finit mais les dégats augmente de manière exponentiel";
	afficherTexte(x, y + 320.f, str, sf::Color::Magenta, window);


	Bouton Retour(300.f, 700.f, "RETOUR");
	Retour.afficher(window);



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

	} while (!Retour.comprendLesCoord(xc, yc, allSounds));

	(*window).display();
	(*window).clear();
}

void Affichage::choixObjets(int page, Objets  obj, bool premierObjet, int indicePersonnage, Equipes& Liste, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds, int set)const {
	int maxPage = (int)(obj.nombreObjets() / 15) + 1;
	std::cout << obj.nombreObjets() << " " << maxPage << " ";
	float y = 20.f;
std::string txt = "";
sf::Color couleurTexte = sf::Color::White;

for (int i = (page - 1) * 15 + 1; i <= std::min(obj.nombreObjets(), page * 15); i++) {
	if (obj.estDebloquer(obj.objetNumero(i))) {
		txt = obj.objetNumero(i).nom() + "     " + obj.objetNumero(i).rareterTexte();
		afficherTexte(50.f, y + 20.f, txt, colorRareter(obj.objetNumero(i).rareter()), window);
		txt = obj.objetNumero(i).effet();
		afficherTexte(50.f, y + 40.f, txt, colorRareter(obj.objetNumero(i).rareter()), window);
		Bouton(1000.f, y + 25.f, "Equiper").afficher(window);
	}
	else {
		txt = "???     " + obj.objetNumero(i).rareterTexte();
		afficherTexte(50.f, y + 20.f, txt, couleurTexte, window);
		txt = "???";
		afficherTexte(50.f, y + 40.f, txt, couleurTexte, window);
		//Bouton(1000, y + 25, "Equiper").afficher();
	}
	y += 50.f;
}

y = 20.f;
bool choix = false;

Bouton Precedent(10.f, -5.f, "Page precedente");
Precedent.afficher(window);

Bouton Retour(525.f, -5.f, "Retour");
Retour.afficher(window);

Bouton Suivant(1065.f, -5.f, "Page suivante");
Suivant.afficher(window);

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

			for (int i = (page - 1) * 15 + 1; i <= std::min(obj.nombreObjets(), page * 15); i++) {
				if (obj.estDebloquer(obj.objetNumero(i)) && Bouton(1000.f, y + 25.f, "Equiper").comprendLesCoord(xc, yc,allSounds)) {
					if (set == 2) {
						Liste[indicePersonnage]->equiperObjet2(obj.objetNumero(i), premierObjet);
						obj.equiperObjetDuPersonnage2(indicePersonnage, obj.objetNumero(i), premierObjet);
					}
					else {
						Liste[indicePersonnage]->equiperObjet(obj.objetNumero(i), premierObjet);
						obj.equiperObjetDuPersonnage(indicePersonnage, obj.objetNumero(i), premierObjet);
					}

					choix = true;
				}
				y += 50.f;
			}
			if (choix != true) {
				if (Precedent.comprendLesCoord(xc, yc, allSounds)) {
					page--;
					if (page <= 0) {
						page = maxPage;
					}
					choix = true;
					(*window).clear();
					choixObjets(page, obj, premierObjet, indicePersonnage, Liste, window, allSounds, set);
				}
				else if (Suivant.comprendLesCoord(xc, yc, allSounds)) {
					page++;
					if (page > maxPage) {
						page = 1;
					}
					choix = true;
					(*window).clear();
					choixObjets(page, obj, premierObjet, indicePersonnage, Liste, window, allSounds, set);
				}
				else if (Retour.comprendLesCoord(xc, yc, allSounds)) {
					choix = true;
				}
			}
		}
	}
} while (!choix);
(*window).display();
(*window).clear();
afficherJoueurs(indicePersonnage, Liste, window, allSounds);
}


void Affichage::afficherSucces(int page, Succes succes, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds)const {
	int maxPage = (int)(succes.nombres() / 15) + 1;
	float y = 20.f;
	std::string txt = "";
	sf::Color couleurTexte = sf::Color::White;

	for (int i = (page - 1) * 15; i < std::min(succes.nombres(), page * 15); i++) {

		if (succes.estDebloque(i) || !succes.estCache(i)) {
			if ( !succes.estCache(i) && !succes.estDebloque(i)){
				couleurTexte = sf::Color::Red;
			}
			else {
				couleurTexte = sf::Color::Green;
			}
			txt = succes.nom(i);
			afficherTexte(50.f, y + 20.f, txt, couleurTexte, window);
			txt = succes.description(i);
			afficherTexte(50.f, y + 40.f, txt, couleurTexte, window);
		}
		else {
			couleurTexte = sf::Color::Red;
			txt = "???";
			afficherTexte(50.f, y + 20.f, txt, couleurTexte, window);
			txt = "???";
			afficherTexte(50.f, y + 40.f, txt, couleurTexte, window);
		}
		y += 50.f;
	}
	couleurTexte = sf::Color::White;

	y = 20.f;
	bool choix = false;

	Bouton Precedent(10.f, -5.f, "Page precedente");
	Precedent.afficher(window);

	Bouton Retour(525.f, -5.f, "Retour");
	Retour.afficher(window);

	Bouton Suivant(1065.f, -5.f, "Page suivante");
	Suivant.afficher(window);

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

				if (choix != true) {
					if (Precedent.comprendLesCoord(xc, yc, allSounds)) {
						page--;
						if (page <= 0) {
							page = maxPage;
						}
						choix = true;
						(*window).clear();
						afficherSucces(page, succes, window, allSounds);
					}
					else if (Suivant.comprendLesCoord(xc, yc, allSounds)) {
						page++;
						if (page > maxPage) {
							page = 1;
						}
						choix = true;
						(*window).clear();
						afficherSucces(page, succes, window, allSounds);
					}
					else if (Retour.comprendLesCoord(xc, yc, allSounds)) {
						choix = true;
					}
				}
			}
		}
	} while (!choix);
	(*window).display();
	(*window).clear();
}
void Affichage::afficherAnimaux(Animaux A, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) const
{
	sf::Color couleurTexte = sf::Color::Red;
	sf::Color couleurFond = sf::Color::Black;

	float x, y;
	int j = 0;
	std::string ratio;
	afficherTexte(300, 50, "Liste des animaux", couleurTexte, window);
	for (float i = 0; i < 5; i += 1.0, j++) {
		x = 150.f + 200.f * i;
		y = 100.f;

		sf::RectangleShape rectangle1(sf::Vector2f(180.f, 30.f));
		rectangle1.setOutlineColor(couleurTexte);
		rectangle1.setOutlineThickness(2.f);
		rectangle1.setFillColor(couleurFond);
		rectangle1.setPosition(sf::Vector2f(x, y));
		(*window).draw(rectangle1);

		//rectangle(x, y, x + 180, y + 30);
		afficherTexte(x + 5.f, y + 10.f, A.animalNumero(j).type(), couleurTexte, window);

		sf::RectangleShape rectangle2(sf::Vector2f(90.f, 30.f));
		rectangle2.setOutlineColor(couleurTexte);
		rectangle2.setOutlineThickness(2.f);
		rectangle2.setFillColor(couleurFond);
		rectangle2.setPosition(sf::Vector2f(x, y + 30.f));
		(*window).draw(rectangle2);
		//rectangle(x, y + 30, x + 90, y + 60);	
		afficherTexte(x + 15.f, y + 40.f, "%PROC", couleurTexte, window);

		sf::RectangleShape rectangle3(sf::Vector2f(90.f, 30.f));
		rectangle3.setOutlineColor(couleurTexte);
		rectangle3.setOutlineThickness(2.f);
		rectangle3.setFillColor(couleurFond);
		rectangle3.setPosition(sf::Vector2f(x + 90.f, y + 30.f));
		(*window).draw(rectangle3);

		//rectangle(x + 90, y + 30, x + 180, y + 60);
		afficherTexte(x + 105.f, y + 40.f, "%RATIO", couleurTexte, window);
		y = y + 60.f;
		for (int i = 0; i < 5; i += 1) {
			sf::RectangleShape rectangle4(sf::Vector2f(90.f, 30.f));
			rectangle4.setOutlineColor(couleurTexte);
			rectangle4.setOutlineThickness(2.f);
			rectangle4.setFillColor(couleurFond);
			rectangle4.setPosition(sf::Vector2f(x, y + 30.f * i));
			(*window).draw(rectangle4);
			//rectangle(x, y + 30 * i, x + 90, y + 30 * (i + 1));
			afficherTexte(x + 15.f, y + 10.f + 30.f * (float)i, std::to_string(A.animalNumero(j).pourcentageActivation(i + 1)) + " %", couleurTexte, window);

			ratio = std::to_string((int)(A.animalNumero(j).ratioMin(i + 1) * 100)) + " % - " + std::to_string((int)(A.animalNumero(j).ratioMax(i + 1) * 100)) + " %";

			sf::RectangleShape rectangle5(sf::Vector2f(90.f, 30.f));
			rectangle5.setOutlineColor(couleurTexte);
			rectangle5.setOutlineThickness(2.f);
			rectangle5.setFillColor(couleurFond);
			rectangle5.setPosition(sf::Vector2f(x + 90.f, y + 30.f * (float)i));
			(*window).draw(rectangle5);

			//rectangle(x + 90, y + 30 * i, x + 180, y + 30 * (i + 1));
			afficherTexte(x + 105.f, y + 10.f + 30.f * (float)i, ratio, couleurTexte, window);
		}
	}
	for (float i = 0.0; i < 5.0; i += 1.0, j++) {
		x = 150.f + 200.f * i;
		y = 400.f;

		sf::RectangleShape rectangle6(sf::Vector2f(180.f, 30.f));
		rectangle6.setOutlineColor(couleurTexte);
		rectangle6.setOutlineThickness(2.f);
		rectangle6.setFillColor(couleurFond);
		rectangle6.setPosition(sf::Vector2f(x, y));
		(*window).draw(rectangle6);

		//rectangle(x, y, x + 180, y + 30);
		afficherTexte(x + 5.f, y + 10.f, A.animalNumero(j).type(), couleurTexte, window);

		sf::RectangleShape rectangle7(sf::Vector2f(90.f, 30.f));
		rectangle7.setOutlineColor(couleurTexte);
		rectangle7.setOutlineThickness(2.f);
		rectangle7.setFillColor(couleurFond);
		rectangle7.setPosition(sf::Vector2f(x, y + 30.f));
		(*window).draw(rectangle7);

		//rectangle(x, y + 30, x + 90, y + 60);
		afficherTexte(x + 15.f, y + 40.f, "%PROC", couleurTexte, window);

		sf::RectangleShape rectangle8(sf::Vector2f(90.f, 30.f));
		rectangle8.setOutlineColor(couleurTexte);
		rectangle8.setOutlineThickness(2.f);
		rectangle8.setFillColor(couleurFond);
		rectangle8.setPosition(sf::Vector2f(x + 90.f, y + 30.f));
		(*window).draw(rectangle8);
		//rectangle(x + 90, y + 30, x + 180, y + 60);
		afficherTexte(x + 105.f, y + 40.f, "%RATIO", couleurTexte, window);
		y = y + 60.f;
		for (int i = 0; i < 5; i += 1) {

			sf::RectangleShape rectangle9(sf::Vector2f(90.f, 30.f));
			rectangle9.setOutlineColor(couleurTexte);
			rectangle9.setOutlineThickness(2.f);
			rectangle9.setFillColor(couleurFond);
			rectangle9.setPosition(sf::Vector2f(x, y + 30.0 * (float)i));
			(*window).draw(rectangle9);
			//rectangle(x, y + 30 * i, x + 90, y + 30 * (i + 1), couleurTexte, window);
			afficherTexte(x + 15.f, y + 10.f + 30.f * (float)i, std::to_string(A.animalNumero(j).pourcentageActivation(i + 1)) + " %", couleurTexte, window);

			ratio = std::to_string((int)(A.animalNumero(j).ratioMin(i + 1) * 100)) + " % - " + std::to_string((int)(A.animalNumero(j).ratioMax(i + 1) * 100)) + " %";
			sf::RectangleShape rectangle10(sf::Vector2f(90.f, 30.f));
			rectangle10.setOutlineColor(couleurTexte);
			rectangle10.setOutlineThickness(2.f);
			rectangle10.setFillColor(couleurFond);
			rectangle10.setPosition(sf::Vector2f(x + 90.f, y + 30.f * (float)i));
			(*window).draw(rectangle10);
			//rectangle(x + 90, y + 30 * i, x + 180, y + 30 * (i + 1), couleurTexte, window);
			afficherTexte(x + 105, y + 10 + 30 * (float)i, ratio, couleurTexte, window);
		}
	}
	afficherTexte(150, 670, "Le proc est le pourcentage de chance que l'animal s'active quand votre personnage attaque ou ce fait attaquer pour chaque rareter.", couleurTexte, window);
	afficherTexte(150, 700, "Le Ratio montre le ratio minimum et maximum de l'attaque concernant cet effet pour chaque rareter.", couleurTexte, window);
	Bouton retour(50, 675, " Retour ");
	retour.afficher(window);

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
	} while (!retour.comprendLesCoord(xc, yc,allSounds));
	(*window).display();
	(*window).clear();
}



void Affichage::dessinerTexte(std::string texte, sf::RenderWindow* window)const {
	afficherTexte(390.f, 5.f, texte, sf::Color::White, window);
	sf::Time  DELAY = sf::milliseconds(Delais().getDelais() * 10);
}

void Affichage::choixNiveau(Zones Z, Objets obj, int& niveau, int& repetition, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) const
{

	int niveauMax = Z.niveauMax();
	if (niveau < 1) {
		niveau = 1;
	}
	else if (niveau > niveauMax) {
		niveau = niveauMax;
	}
	if (repetition < 1) {
		repetition = 100;
	}
	else if (repetition > 100) {
		repetition = 100;
	}
	afficherObjetsDeblocableNiveau(obj, niveau, window);


	afficherTexte(100.f, 100.f, "Choix du niveau, niveau max = " + std::to_string(niveauMax), sf::Color::White, window);
	Bouton plus1(100.f, 200.f, " + 1 ");
	Bouton moins1(100.f, 300.f, " - 1 ");
	Bouton plus10(200.f, 200.f, " + 10 ");
	Bouton moins10(200.f, 300.f, " - 10 ");
	Bouton niveauActuel(330.f, 90.f, std::to_string(niveau));

	afficherTexte(400.f, 100.f, "Choix du nombre de repetition, max = 100 ", sf::Color::White, window);
	Bouton plus1r(400.f, 200.f, " + 1 ");
	Bouton moins1r(400.f, 300.f, " - 1 ");
	Bouton plus10r(500.f, 200.f, " + 10 ");
	Bouton moins10r(500.f, 300.f, " - 10 ");
	Bouton repetitionActuel(680.f, 90.f, std::to_string(repetition));

	Bouton confirmer(150.f, 400.f, "Confirmer");

	plus1.afficher(window);
	moins1.afficher(window);
	plus10.afficher(window);
	moins10.afficher(window);
	niveauActuel.afficher(window);

	confirmer.afficher(window);

	plus1r.afficher(window);
	moins1r.afficher(window);
	plus10r.afficher(window);
	moins10r.afficher(window);
	repetitionActuel.afficher(window);

	bool bouttonHit = false;
	(*window).display();

	float  xc = 0.f, yc = 0.f;
	sf::Event event;
	do {
		while ((*window).pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition((*window));
				xc = (float)position.x;
				yc = (float)position.y;

				if (plus1.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					choixNiveau(Z, obj, ++niveau, repetition, window,allSounds);
				}
				else if (plus10.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					niveau = niveau + 10;
					choixNiveau(Z, obj, niveau, repetition, window,allSounds);
				}
				else if (moins1.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					choixNiveau(Z, obj, --niveau, repetition, window,allSounds);
				}
				else if (moins10.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					niveau = niveau - 10;
					choixNiveau(Z, obj, niveau, repetition, window,allSounds);
				}
				else if (plus1r.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					choixNiveau(Z, obj, niveau, ++repetition, window,allSounds);
				}
				else if (plus10r.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					repetition += 10;
					choixNiveau(Z, obj, niveau, repetition, window,allSounds);
				}
				else if (moins1r.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					choixNiveau(Z, obj, niveau, --repetition, window,allSounds);
				}
				else if (moins10r.comprendLesCoord(xc, yc,allSounds)) {
					(*window).clear();
					bouttonHit = true;
					repetition -= 10;
					choixNiveau(Z, obj, niveau, repetition, window,allSounds);
				}
			}
		}
	} while (!confirmer.comprendLesCoord(xc, yc,allSounds) && !bouttonHit);
	(*window).display();
	(*window).clear();
}

void Affichage::afficherObjetsDeblocableNiveau(Objets obj, int niveau, sf::RenderWindow* window)const {
	sf::RectangleShape rectangleN(sf::Vector2f(1200.f, 350.f));
	rectangleN.setOutlineColor(sf::Color::Black);
	rectangleN.setFillColor(sf::Color::Black);
	rectangleN.setPosition(sf::Vector2f(0.f, 450.f));
	(*window).draw(rectangleN);
	//setfillstyle(1, BLACK);
	//setcolor(BLACK);
	//int Tab[8] = { 0,450,0,800,1200,800,1200,450 };
	//fillpoly(4, Tab);
	//setcolor(RED);
	std::vector<Objet> objets = obj.objetsDuNiveau(niveau);
	std::string txt = "";
	for (int i = 0; i < (int)objets.size(); i++) {
		if (!obj.estDebloquer(objets[i])) {
			txt += " ???   ";
		}
		else {
			txt += objets[i].nom() + "   ";
		}
	}
	afficherTexte(300.f, 460.f, "LOOT", sf::Color::White, window);
	afficherTexte(50.f, 490.f, txt, sf::Color::White, window);
}
void Affichage::menuModifierEquipe(Equipes & Gentil, Equipes choix,Zones & Z, int max, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) const
{
	//(*window).clear();
	Objets O = Objets();
	Succes S;
	afficherTexte(100, 20, "Equipe actuel", sf::Color::White, window);
	for (int i = 0; i < Gentil.taille(); i++) {
		Bouton(100.f, (float)(i + 1) * 50.f, std::to_string(i) + Gentil[i]->nom()).afficher(window);
	}
	std::vector<Bouton>* les_boutons = new std::vector<Bouton>;
	les_boutons->reserve(15);
	std::vector<int> ids;
	ids.reserve(15);
	int i = 0;
	if (!Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Fabian = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Fabian);
		ids.push_back(i);
	}
	
	i++;
	if (!Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Nicolas = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Nicolas);
		ids.push_back(i);
	}

	i++;
	if (Z.niveauMax() >= 6 && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Thomas = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Thomas);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_ANIMAL_LEGENDAIRE) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Fiona = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Fiona);
		ids.push_back(i);
	}

	i++;
	if (Z.niveauMax() >= 11 && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Moustick = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Moustick);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_OBJET_LEGENDAIRE) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Bryan = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Bryan);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV25_FIONA) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_David = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_David);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV25_NICOLAS) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Isidore = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Isidore);
		ids.push_back(i);
	}
	i++;
	if (S.estDebloque(SUCCES_NIV10_2PERSOS) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Sebastien = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Sebastien);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV10_FABIAN_FIONA) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Cloe = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Cloe);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV25_3PERSOS) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Amine = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Amine);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV10_NICOLAS_SEBASTIEN) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Florian = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Florian);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV15) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_JB = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_JB);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV25_FABIAN_FIONA_CLOE) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Maelle = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Maelle);
		ids.push_back(i);
	}
	
	i++;
	if (O.estDebloquer(O.objetNumero(OBJET_OEUF_TORTUE)) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Tortue = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Tortue);
		ids.push_back(i);
	}

	i++;
	if (S.estDebloque(SUCCES_NIV20) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Salim = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Salim);
		ids.push_back(i);
	}

	i++;
	if (O.estDebloquer(O.objetNumero(OBJET_CENDRE_PHENIX)) && !Gentil.comprendPersonnage(choix[i]->id())) {
		Bouton Bouton_Phenix = Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau()));
		les_boutons->push_back(Bouton_Phenix);
		ids.push_back(i);
	}

	if (max > 0) {
		afficherTexte(400.f, 10.f, "Personnages selectionnable", sf::Color::White, window);
		for (Bouton& bouton : *les_boutons) {
			bouton.afficher(window);
		}
		/*
		for (int i = 14; i < choix.taille(); i++) {
			if (i == 14 && !O.estDebloquer(O.objetNumero(OBJET_OEUF_TORTUE))) {

			}
			else {
				if (i == 16 && !O.estDebloquer(O.objetNumero(OBJET_CENDRE_PHENIX))) {

				}
				else {
					Bouton(600.f, (float)(i - 13) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau())).afficher(window);
				}

			}

		}*/
	}
	else {
		afficherTexte(400.f, 20.f, "Maximum de personnages selectionnable atteintes", sf::Color::White, window);
	}
	Bouton retirer(100.f, 700.f, "Retirer le dernier personnage");
	if (Gentil.taille() > 0) {
		retirer.afficher(window);
	}

	Bouton Sauvegarder(600.f, 700.f, "Sauvegarder");
	Sauvegarder.afficher(window);
	Bouton Retour(800.f, 700.f, "Retour");
	Retour.afficher(window);
	bool boutonSelectionnerPerso = false;
	bool boutonSelectionnerAutre = false;
	(*window).display();
	sf::Time  DELAY = sf::milliseconds(50); // Milliseconds of delay between checks
	float  xc, yc;
	do {
		sf::Event event;

		while ((*window).pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position = sf::Mouse::getPosition((*window));
				xc = (float)position.x;
				yc = (float)position.y;

				if (max > 0) {
					for (int i = 0;i < ids.size(); i++) {
						if (les_boutons->at(i).comprendLesCoord(xc, yc, allSounds)) {
							
							Gentil.ajouterPerso(choix[ids[i]]);
							--max;
							boutonSelectionnerPerso = true;
							(*window).clear();
							menuModifierEquipe(Gentil, choix,Z, max, window,allSounds);
						}
					}
				}
				if ( Gentil.taille() > 0) {
					if (retirer.comprendLesCoord(xc, yc,allSounds)) {
						boutonSelectionnerAutre = true;
						Gentil.retirerDernierPerso();
						(*window).clear();
						menuModifierEquipe(Gentil, choix,Z, ++max, window,allSounds);
					}
				}
				if (Sauvegarder.comprendLesCoord(xc, yc,allSounds)) {
					Gentil.sauvegarderEquipe();
					boutonSelectionnerAutre = true;
					(*window).clear();
					menuModifierEquipe(Gentil, choix,Z, max, window,allSounds);
				}
				else if (Retour.comprendLesCoord(xc, yc,allSounds)) {

					boutonSelectionnerAutre = true;
				}
			}

		}
		(*window).clear();
	} while (!boutonSelectionnerPerso && !boutonSelectionnerAutre);
	les_boutons->~vector();
	(*window).display();
	(*window).clear();
}



Affichage::~Affichage()
{
}
