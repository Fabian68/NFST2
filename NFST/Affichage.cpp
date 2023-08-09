#include "Affichage.h"
#include "Equipes.h"
#include "Personnage.h"
#include "Bouton.h"
#include "Zones.h"
#include  <iostream>
#include "Delais.h"
#include "Objets.h"

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
	afficherTexte(x, y + 40.f, str, couleurTexte, window);

	str = "Vie : " + std::to_string(Liste[indice]->vieMax());
	afficherTexte(x, y + 60.f, str, couleurTexte, window);

	str = "Vitesse : " + std::to_string(Liste[indice]->vitesse());
	afficherTexte(x, y + 80.f, str, couleurTexte, window);

	str = "Chance de double attaque : " + std::to_string(Liste[indice]->chanceDoubleAttaque());
	afficherTexte(x, y + 100.f, str, couleurTexte, window);

	str = "Chance de coup habile : " + std::to_string(Liste[indice]->chanceHabileter());
	afficherTexte(x, y + 120.f, str, couleurTexte, window);

	str = "Chance de deviation : " + std::to_string(Liste[indice]->pourcentageDeviation());
	afficherTexte(x, y + 140.f, str, couleurTexte, window);

	str = "Pourcentage de reduction de degats : " + std::to_string(Liste[indice]->pourcentageReduction());
	afficherTexte(x, y + 160.f, str, couleurTexte, window);

	str = "Chance de ricochet : " + std::to_string(Liste[indice]->pourcentageRicochet());
	afficherTexte(x, y + 180.f, str, couleurTexte, window);

	str = "Chance esquive : " + std::to_string(Liste[indice]->pourcentageEsquive());
	afficherTexte(x, y + 200.f, str, couleurTexte, window);

	str = "Chance de blocage : " + std::to_string(Liste[indice]->pourcentageBlocage());
	afficherTexte(x, y + 220.f, str, couleurTexte, window);

	float x2 = x - 20.f;

	x = x + 250.f;

	afficherTexte(x - 250.f, y + 350.f, Liste[indice]->objets().first.nom(), couleurTexte, window);
	afficherTexte(x - 250.f, y + 390.f, Liste[indice]->objets().second.nom(), couleurTexte, window);
	afficherTexte(x - 250.f, y + 430.f, Liste[indice]->objets2().first.nom(), couleurTexte, window);
	afficherTexte(x - 250.f, y + 470.f, Liste[indice]->objets2().second.nom(), couleurTexte, window);

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
		afficherTexte(x + 180.f, y + 40.f, std::to_string((int)(A.ratioMin(rareter) * 100)) + " %", couleurTexte, window);
		afficherTexte(x + 230.f, y + 40.f, " Ratio Max : ", couleurTexte, window);
		afficherTexte(x + 310.f, y + 40.f, std::to_string((int)(A.ratioMax(rareter) * 100)) + " %", couleurTexte, window);

		sf::RectangleShape rectangle3(sf::Vector2f(425.f, 30.f));
		rectangle3.setOutlineColor(couleurTexte);
		rectangle3.setOutlineThickness(2.f);
		rectangle3.setFillColor(couleurFond);
		rectangle3.setPosition(sf::Vector2f(x + 90.f, y + 110.f));
		(*window).draw(rectangle3);

		//rectangle(x + 90, y + 80, x + 515, y + 110);
		afficherTexte(x + 100.f, y + 90.f, " Pourcentage d'activation quand attaque ou est attaquer : ", couleurTexte, window);
		afficherTexte(x + 475.f, y + 90.f, std::to_string(A.pourcentageActivation(rareter)) + " %", couleurTexte, window);
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
			afficherTexte(x, y, texteAnimaux, couleurTexte, window);
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
			afficherTexte(x, (float)k, texteOrbe, couleurTexte, window);
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

	str = "Pseudo : " + Liste[indice]->nom();
	afficherTexte(x+100.f, y, str, couleurTexte, window);

	str = "Passif ";
	afficherTexte(x, y + 10.f, str, couleurTexteG, window);
	switch (indice) {
		case 0:
			str = "Gagne force/(7/5/3/2) + niveau de dégats supplémentaires. Niveau (1/10/100/1000) Valeur actuelle : " + std::to_string(Liste[indice]->status().adducteur());
			str = str + "\n" + "Recois niveaux dégats en moins, Valeur actuel : "+ std::to_string(Liste[indice]->niveau());
			
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
	}
	afficherTexte(x, y + 110.f, str, couleurTexte, window);

	str = "Passif defensif";
	afficherTexte(x, y + 160.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Vous augmenter votre reduction de dégats de 1";
		break;
	}
	afficherTexte(x, y + 180.f, str, couleurTexte, window);

	str = "Compétence 1 ";
	afficherTexte(x, y + 230.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Attaque l'ennemi le plus proche avec un ratio de 20-40% de votre attaque + 10-30% de votre vitesse , +1 mana";
		int DEGATS = Liste[indice]->degats(0.2, 0.4);
		DEGATS += Liste[indice]->degats(0.1, 0.3, CHOIXVITESSE);
		str = str + "\n" + "Dégats potentiels : " + std::to_string(DEGATS);
		break;
	}
	afficherTexte(x, y + 250.f, str, couleurTexte, window);

	str = "Compétence 2 ";
	afficherTexte(x, y + 320.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Attaque plusieurs fois l'ennemi le plus fort, le nombre de coup = 3 + vitesse/niveau, compteur d'attaque = 0 et augmente de 1 à chaque attaque (CA), -1 mana ";
		str = str + "\n" + " ratio = (1,7% + 1,7% x CA) - (17% + 3,4% x CA) : " ;
		int DEGATS = 0;
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
	}
	afficherTexte(x, y + 340.f, str, couleurTexte, window);

	str = "Compétence 3 ";
	afficherTexte(x, y + 410.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Augmente les chances de coup critique de 2% et les dégats critiques de 7%, -1 mana";
		break;
	}
	afficherTexte(x, y + 430.f, str, couleurTexte, window);

	str = "Compétence 4 ";
	afficherTexte(x, y + 500.f, str, couleurTexteG, window);
	switch (indice) {
	case 0:
		str = "Si vous avez pas toute votre vie et tout votre bouclier, vous soigne et bouclier intégralement - 3 Mana";
		str = str + "\n" + "Sinon attaque la cible la plus faible pour 50-150% de votre force + 75-125% de votre vitesse, -2 mana";
		int DEGATS = Liste[indice]->degats(0.5, 1.5);
		DEGATS += Liste[indice]->degats(0.75, 1.25, CHOIXVITESSE);
		str = str + " Dégats potentiels : " + std::to_string(DEGATS);
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
			afficherTexte(50.f, y + 20.f, txt, couleurTexte, window);
			txt = obj.objetNumero(i).effet();
			afficherTexte(50.f, y + 40.f, txt, couleurTexte, window);
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
					if (Precedent.comprendLesCoord(xc, yc,allSounds)) {
						page--;
						if (page <= 0) {
							page = maxPage;
						}
						choix = true;
						(*window).clear();
						choixObjets(page, obj, premierObjet, indicePersonnage, Liste, window,allSounds, set);
					}
					else if (Suivant.comprendLesCoord(xc, yc,allSounds)) {
						page++;
						if (page > maxPage) {
							page = 1;
						}
						choix = true;
						(*window).clear();
						choixObjets(page, obj, premierObjet, indicePersonnage, Liste, window,allSounds, set);
					}
					else if (Retour.comprendLesCoord(xc, yc,allSounds)) {
						choix = true;
					}
				}
			}
		}
	} while (!choix);
	(*window).display();
	(*window).clear();
	afficherJoueurs(indicePersonnage, Liste, window,allSounds);
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
void Affichage::menuModifierEquipe(Equipes& Gentil, Equipes choix,Zones & Z, int max, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) const
{
	//(*window).clear();
	Objets O = Objets();

	afficherTexte(100, 20, "Equipe actuel", sf::Color::White, window);
	for (int i = 0; i < Gentil.taille(); i++) {
		Bouton(100.f, (float)(i + 1) * 50.f, std::to_string(i) + Gentil[i]->nom()).afficher(window);
	}

	if (max > 0) {
		afficherTexte(400.f, 10.f, "Personnages selectionnable", sf::Color::White, window);
		for (int i = 0; i < 14; i++) {
			Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + " " + choix[i]->nom() + " LVL : " + std::to_string(choix[i]->niveau())).afficher(window);
		}
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

		}
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
					for (int i = 0; i < 14; i++) {
						if (Bouton(400.f, (float)(i + 1) * 45.f, std::to_string(i) + choix[i]->nom()).comprendLesCoord(xc, yc,allSounds)) {
							if (Gentil.comprendPersonnage(choix[i]->id())) {
								afficherTexte(400.f, 20.f, "Personnage déja selectionner", sf::Color::White, window);
							}
							else {

								Gentil.ajouterPerso(choix[i]);
								--max;
							}

							boutonSelectionnerPerso = true;
							(*window).clear();
							menuModifierEquipe(Gentil, choix, max, window,allSounds);
						}
					}
					for (int i = 14; i < choix.taille(); i++) {
						if (i == 14 && !O.estDebloquer(O.objetNumero(44))) {

						}
						else {
							if (i == 16 && !O.estDebloquer(O.objetNumero(45))) {

							}
							else {
								if (Bouton(600.f, (float)(i - 13) * 45.f, std::to_string(i) + choix[i]->nom()).comprendLesCoord(xc, yc,allSounds)) {
									if (Gentil.comprendPersonnage(choix[i]->id())) {
										afficherTexte(400, 20, "Personnage déja selectionner", sf::Color::White, window);
									}
									else {

										Gentil.ajouterPerso(choix[i]);
										--max;
									}

									boutonSelectionnerPerso = true;
									(*window).clear();
									menuModifierEquipe(Gentil, choix, max, window,allSounds);
								}
							}
						}

					}
				}
				if (Gentil.taille() > 0) {
					if (retirer.comprendLesCoord(xc, yc,allSounds)) {
						boutonSelectionnerAutre = true;
						Gentil.retirerDernierPerso();
						(*window).clear();
						menuModifierEquipe(Gentil, choix, ++max, window,allSounds);
					}
				}
				if (Sauvegarder.comprendLesCoord(xc, yc,allSounds)) {
					Gentil.sauvegarderEquipe();
					boutonSelectionnerAutre = true;
					(*window).clear();
					menuModifierEquipe(Gentil, choix, max, window,allSounds);
				}
				else if (Retour.comprendLesCoord(xc, yc,allSounds)) {

					boutonSelectionnerAutre = true;
				}
			}

		}
		(*window).clear();
	} while (!boutonSelectionnerPerso && !boutonSelectionnerAutre);
	(*window).display();
	(*window).clear();
}



Affichage::~Affichage()
{
}
