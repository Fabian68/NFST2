#include "AffichageCombat.h"
#include "Combat.h"
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>
#include <tuple>
#include <string>

void AffichageCombat::afficherTexte(float x, float y, std::string texte, sf::Color couleurTexte, sf::RenderWindow* window)const {
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

std::string conversion(long long int nombre) {
	std::string nombrestr;
	if (nombre >= 1000000) {
		nombrestr = std::to_string(nombre / 1000000) + "M";
	}
	else if (nombre >= 1000) {
		nombrestr = std::to_string(nombre / 1000) + "K";
	}
	else {
		nombrestr = std::to_string(nombre);
	}
	return nombrestr;
}

AffichageCombat::AffichageCombat() = default;

void AffichageCombat::dessinerTexteModificationVie(Personnage* P, sf::RenderWindow* window) const {

	int montant = P->getDerniereActionMontant();
	int ACTION = P->getDerniereActionType();
	float x;
	if (P->equipeAllier().ia()) {
		x = 1200.f - 195.f;
	}
	else {
		x = 430.f;
	}

	float y = -35.f + 100.f * (float)(P->indiceEquipe() + 1);

	std::string texte = conversion(montant);
	switch (ACTION) {
	case actionDEGATS:
		afficherTexte(x, y, texte, sf::Color::Red, window);
		break;
	case actionSOINS:
		afficherTexte(x, y, texte, sf::Color::Green, window);
		break;
	case actionBOUCLIER:
		afficherTexte(x, y, texte, sf::Color::Magenta, window);
		break;
	}
}

void afficherEtats(float x, float y, Personnage* P, sf::RenderWindow* window) {
	auto drawCercleEtat = [&](float offsetY, sf::Color couleur) {
		sf::CircleShape circle(5.f);
		circle.setPosition(x - 15.f, y + offsetY);
		circle.setFillColor(couleur);
		circle.setOutlineColor(sf::Color::White);
		circle.setOutlineThickness(1.f);
		window->draw(circle);
	};

	auto drawRectangleEtat = [&](float offsetY, sf::Color couleur) {
		sf::RectangleShape rect(sf::Vector2f(10.f, 10.f));
		rect.setPosition(x - 15.f, y + offsetY);
		rect.setFillColor(couleur);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(1.f);
		window->draw(rect);
	};

	drawCercleEtat(1.f, P->status().estEmpoisoner() ? sf::Color::Magenta : sf::Color::Black);
	drawCercleEtat(13.f, P->status().estBruler() ? sf::Color::Red : sf::Color::Black);
	drawRectangleEtat(30.f, P->status().estFragiliser() ? sf::Color::Red : sf::Color::Black);
	drawRectangleEtat(45.f, P->status().estProteger() ? sf::Color::Green : sf::Color::Black);
}

void AffichageCombat::afficherVieEtBouclier(float x, float y, Personnage* P, sf::RenderWindow* window) const {
	auto drawBarre = [&](float offsetY, int pourcentage, sf::Color couleur) {
		sf::RectangleShape barreRemplie(sf::Vector2f(pourcentage * 2.f, 15.f));
		barreRemplie.setPosition(x + 2.f, y + offsetY);
		barreRemplie.setFillColor(couleur);
		barreRemplie.setOutlineColor(sf::Color::White);
		barreRemplie.setOutlineThickness(1.f);
		window->draw(barreRemplie);

		sf::RectangleShape barreVide(sf::Vector2f((100 - pourcentage) * 2.f, 15.f));
		barreVide.setPosition(x + 2.f + pourcentage * 2.f, y + offsetY);
		barreVide.setFillColor(sf::Color::Black);
		barreVide.setOutlineColor(sf::Color::White);
		barreVide.setOutlineThickness(1.f);
		window->draw(barreVide);
	};

	drawBarre(25.f, P->pourcentageVie(), sf::Color::Green);
	drawBarre(45.f, P->pourcentageBouclier(), sf::Color::Magenta);

	afficherTexte(x + 210.f, y + 23.f, conversion(P->vie()) + " / " + conversion(P->vieMax()), sf::Color::White, window);
	afficherTexte(x + 210.f, y + 43.f, conversion(P->bouclier()) + " / " + conversion(P->bouclierMax()), sf::Color::White, window);
}

void afficherMana(float x, float y, Personnage* P, sf::RenderWindow* window) {
	for (int i = 0; i < P->mana(); ++i) {
		sf::RectangleShape mana(sf::Vector2f(2.f, 2.f));
		mana.setPosition(x + 3.f * i + 1.f, y + 62.f);
		mana.setFillColor(sf::Color::Cyan);
		mana.setOutlineColor(sf::Color::Blue);
		mana.setOutlineThickness(1.f);
		window->draw(mana);
	}
}
bool sourisSurJoueur(const sf::Vector2f& souris, const sf::FloatRect& rectStats, const sf::FloatRect& rectSprite) {
	return rectStats.contains(souris) || rectSprite.contains(souris);
}

struct StatCombat {
	long long int valeur;
	long long int max;
	sf::Color couleurEquipe;
	sf::Color couleurAdverse;
	std::string label;
};

static StatCombat creerStatCombat(const long long int & valeur,const long long & max, sf::Color couleurEquipe, sf::Color couleurAdverse, const std::string& label) {
	StatCombat s;
	s.valeur = valeur;
	s.max = max > 0 ? max : 1; // éviter division par zéro
	s.couleurEquipe = couleurEquipe;
	s.couleurAdverse = couleurAdverse;
	s.label = label;
	return s;
}
void AffichageCombat::dessinerStatistiquesCombat(Personnage* P, sf::RenderWindow* window, float posX, float posY, bool equipeIA)const {
	float xCombat = equipeIA ? 1088.f : 5.f;
	float yCombat = posY; // sous la fiche du joueur

	std::vector<StatCombat> stats2;
	stats2.push_back(creerStatCombat(P->stats().degatsProvoquer(),
		std::max(P->equipeAllier().meilleurDegats()->stats().degatsProvoquer(),
			P->equipeEnnemi().meilleurDegats()->stats().degatsProvoquer()),
		sf::Color::Red, sf::Color::Black, "degats"));

	stats2.push_back(creerStatCombat(
		P->stats().degatsRecu(),
		std::max(P->equipeAllier().meilleurTank()->stats().degatsRecu(),
			P->equipeEnnemi().meilleurTank()->stats().degatsRecu()),
		sf::Color(51, 102, 0), sf::Color::Black, "tanking"));

	stats2.push_back(creerStatCombat(
		P->stats().soinsDonner(),
		std::max(P->equipeAllier().meilleurSoigneur()->stats().soinsDonner(),
			P->equipeEnnemi().meilleurSoigneur()->stats().soinsDonner()),
		sf::Color::Green, sf::Color::Black, "soins"));

	stats2.push_back(creerStatCombat(
		P->stats().bouclierDonner(),
		std::max(P->equipeAllier().meilleurBouclier()->stats().bouclierDonner(),
			P->equipeEnnemi().meilleurBouclier()->stats().bouclierDonner()),
		sf::Color::Magenta, sf::Color::Black, "bouclier"));


	for (const auto& stat : stats2) {
		float max = static_cast<float>(std::max(stat.max, (long long int)1));
		int pourcentage = static_cast<int>(100.f * (float)stat.valeur / max);
		pourcentage = std::max(0, std::min(pourcentage, 100));

		float val1 = (float)(equipeIA ? 100 - pourcentage : pourcentage);
		float val2 = 100.f - val1;

		sf::Color couleur1 = equipeIA ? stat.couleurAdverse : stat.couleurEquipe;
		sf::Color couleur2 = equipeIA ? stat.couleurEquipe : stat.couleurAdverse;

		sf::RectangleShape rect1(sf::Vector2f(val1, 15.f));
		rect1.setOutlineColor(sf::Color::White);
		rect1.setOutlineThickness(1.f);
		rect1.setFillColor(couleur1);
		rect1.setPosition(sf::Vector2f(xCombat, yCombat));
		window->draw(rect1);

		sf::RectangleShape rect2(sf::Vector2f(val2, 15.f));
		rect2.setOutlineColor(sf::Color::White);
		rect2.setOutlineThickness(1.f);
		rect2.setFillColor(couleur2);
		rect2.setPosition(sf::Vector2f(xCombat + val1, yCombat));
		window->draw(rect2);

		afficherTexte(xCombat + 52.f, yCombat, conversion(stat.valeur), sf::Color::White, window);

		yCombat += 16.f;
	}

}

void AffichageCombat::afficherFenetreStatistiques(Personnage* P, const sf::Vector2f& souris, sf::RenderWindow* window) const {
	std::vector<std::pair<std::string, int>> stats;
	stats.push_back(std::make_pair("Force", P->force()));
	stats.push_back(std::make_pair("Vitesse", P->vitesse()));
	stats.push_back(std::make_pair("Double Attaque", P->chanceDoubleAttaque()));
	stats.push_back(std::make_pair("Chance Habilité", P->chanceHabileter()));
	stats.push_back(std::make_pair("Déviation", P->pourcentageDeviation()));
	stats.push_back(std::make_pair("Réduction", P->pourcentageReduction()));
	stats.push_back(std::make_pair("Ricochet", P->pourcentageRicochet()));
	stats.push_back(std::make_pair("Esquive", P->pourcentageEsquive()));
	stats.push_back(std::make_pair("Blocage", P->pourcentageBlocage()));
	stats.push_back(std::make_pair("Chance de critique", P->chancesCritiques()));
	stats.push_back(std::make_pair("Dégats critiques", P->degatsCritiques()));

	const float ligneHauteur = 20.f;
	const float marge = 10.f;
	const float colonneLargeur = 140.f;
	const unsigned int nbLignes = (stats.size() + 1) / 2;

	sf::Vector2f positionFenetre(souris.x + 10.f, souris.y + 10.f);
	sf::Vector2f tailleFenetre(colonneLargeur * 2 + marge * 3, nbLignes * ligneHauteur + marge * 2);

	// Fond
	sf::RectangleShape fond(tailleFenetre);
	fond.setFillColor(sf::Color(50, 50, 50, 220));
	fond.setOutlineColor(sf::Color::White);
	fond.setOutlineThickness(1.f);
	fond.setPosition(positionFenetre);
	window->draw(fond);

	// Texte
	for (std::size_t i = 0; i < stats.size(); ++i) {
		const std::string texte = stats[i].first + ": " + std::to_string(stats[i].second);

		float x = positionFenetre.x + marge + (i % 2) * (colonneLargeur + marge);
		float y = positionFenetre.y + marge + (i / 2) * ligneHauteur;

		afficherTexte(x, y, texte, sf::Color::White, window);
	}
}

bool AffichageCombat::dessinerJoueur(int indice, bool equipeIA, Personnage* P, sf::RenderWindow* window) const {
	bool sourisSurPerso = false;
	float x = equipeIA ? 1180.f - 460.f : 130.f;
	float y = -65.f + 100.f * (float)indice;
	float posStatX = x;
	float posStatY = y;
	sf::Color couleurTexte = equipeIA ? sf::Color::Red : sf::Color::Green;
	sf::Color couleurFond = sf::Color::Black;

	// Rectangle de fond
	sf::RectangleShape rectangleJoueur(sf::Vector2f(360.f, 65.f));
	rectangleJoueur.setOutlineColor(couleurTexte);
	rectangleJoueur.setOutlineThickness(1.f);
	rectangleJoueur.setFillColor(P->estSonTour() ? sf::Color(0, 0, 102) : couleurFond);
	rectangleJoueur.setPosition(sf::Vector2f(x, y));
	window->draw(rectangleJoueur);

	// Sprite
	P->sprite().setPosition(equipeIA ? sf::Vector2f(x - 136.f, y - 30.f) : sf::Vector2f(x + 361.f, y - 30.f));
	window->draw(P->sprite());

	// Texte nom + niveau
	std::string nomNiveau = P->nom() + " " + std::to_string(P->niveau());
	afficherTexte(x + 2.f, y + 5.f, nomNiveau, couleurTexte, window);

	afficherEtats(x, y, P, window);
	afficherVieEtBouclier(x, y, P, window);
	afficherMana(x, y, P, window);
	dessinerStatistiquesCombat(P, window, x, y, equipeIA);

	dessinerTexteModificationVie(P, window);
	sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
	sf::Vector2f positionSouris = window->mapPixelToCoords(mousePixel);

	// Zones du joueur
	sf::FloatRect zoneStat = rectangleJoueur.getGlobalBounds();
	sf::FloatRect zoneSprite = P->sprite().getGlobalBounds();
	
	if (sourisSurJoueur(positionSouris, zoneStat, zoneSprite)) {
		sourisSurPerso = true;
	}
	return sourisSurPerso;
}


void AffichageCombat::dessinerEquipeJoueur(Equipes J, sf::RenderWindow* window) const
{
	Personnage* personnageSurvole = nullptr;
	for (int i = 0; i < J.taille(); i++) {
		if (dessinerJoueur(i + 1, false, J.perso(i), window) == true) {
			personnageSurvole = J.perso(i);
		}
	}

	if (personnageSurvole != nullptr) {
		sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
		sf::Vector2f positionSouris = window->mapPixelToCoords(mousePixel);
		afficherFenetreStatistiques(personnageSurvole, positionSouris, window);
	}
}

void AffichageCombat::dessinerEquipeIA(Equipes I, sf::RenderWindow* window) const
{
	Personnage* personnageSurvole = nullptr;
	for (int i = 0; i < I.taille(); i++) {
		if (dessinerJoueur(i + 1, true, I.perso(i), window) == true) {
			personnageSurvole = I.perso(i);
		}
	}
	if (personnageSurvole != nullptr) {
		sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
		sf::Vector2f positionSouris = window->mapPixelToCoords(mousePixel);
		afficherFenetreStatistiques(personnageSurvole, positionSouris, window);
	}
}

void AffichageCombat::dessinerStatsJoueur(int indice,Equipes E, bool equipeIA, Personnage* P, sf::RenderWindow* window) const
{
	float x=0.f;
	sf::Color couleurTexte = sf::Color::White;
	sf::Color couleurRectangle = sf::Color::Red;

	std::string categorie = "";
	int pourcentage = 0;

	std::string str = P->nom() + " " + std::to_string(P->niveau());

	float y = 0.0;

	if (equipeIA) {
		y = 400.f;
		couleurTexte = sf::Color::Red;
	}
	else {
		y = 20.f;
		couleurTexte = sf::Color::Green;
	}

	categorie = "Dégats infligés";
	pourcentage = (int)(100.f * ((float)P->stats().degatsProvoquer() / (float)E.meilleurDegats()->stats().degatsProvoquer()));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}
	afficherTexte(x + 150.f, 5.f, categorie, sf::Color::Red, window);

	y = y + 30.f * (float)indice -20.f;

	afficherTexte(x + 2.f, y, str, couleurTexte, window);

	sf::RectangleShape rectangleP1(sf::Vector2f((float)pourcentage * 2.f, 15.f));
	rectangleP1.setOutlineColor(sf::Color::White);
	rectangleP1.setOutlineThickness(1.f);
	rectangleP1.setFillColor(couleurRectangle);
	rectangleP1.setPosition(sf::Vector2f(x + 102.f, y));
	(*window).draw(rectangleP1);

	sf::RectangleShape rectangleP2(sf::Vector2f(-(float)pourcentage * 2.f + 200.f, 15.f));
	rectangleP2.setOutlineColor(sf::Color::White);
	rectangleP2.setOutlineThickness(1.f);
	rectangleP2.setFillColor(sf::Color::Black);
	rectangleP2.setPosition(sf::Vector2f(x + 102.f + (float)pourcentage * 2.f, y));
	(*window).draw(rectangleP2);

	afficherTexte(x + 152.f, y, conversion(P->stats().degatsProvoquer()), sf::Color::White, window);

	x += 225.f;
	couleurRectangle = sf::Color::Green;
	categorie = "Dégats subis";
	pourcentage = (int)(100.f * ((float)P->stats().degatsRecu() / (float)E.meilleurTank()->stats().degatsRecu()));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}
	afficherTexte(x + 150.f, 5.f, categorie, sf::Color::Green, window);

	sf::RectangleShape rectangleS1(sf::Vector2f((float)pourcentage * 2.f, 15.f));
	rectangleS1.setOutlineColor(sf::Color::White);
	rectangleS1.setOutlineThickness(1.f);
	rectangleS1.setFillColor(couleurRectangle);
	rectangleS1.setPosition(sf::Vector2f(x + 102.f, y));
	(*window).draw(rectangleS1);

	sf::RectangleShape rectangleS2(sf::Vector2f(-(float)pourcentage * 2.f + 200.f, 15.f));
	rectangleS2.setOutlineColor(sf::Color::White);
	rectangleS2.setOutlineThickness(1.f);
	rectangleS2.setFillColor(sf::Color::Black);
	rectangleS2.setPosition(sf::Vector2f(x + 102.f + (float)pourcentage * 2.f, y));
	(*window).draw(rectangleS2);

	afficherTexte(x + 152.f, y, conversion(P->stats().degatsRecu()), sf::Color::White, window);

	x += 225.f;
	couleurRectangle = sf::Color::Green;
	categorie = "Soins provoqués";
	pourcentage = (int)(100.f * ((float)P->stats().soinsDonner() / (float)E.meilleurSoigneur()->stats().soinsDonner()));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}
	afficherTexte(x + 150.f, 5.f, categorie, sf::Color::Green, window);

	sf::RectangleShape rectangleSo1(sf::Vector2f((float)pourcentage * 2.f, 15.f));
	rectangleSo1.setOutlineColor(sf::Color::White);
	rectangleSo1.setOutlineThickness(1.f);
	rectangleSo1.setFillColor(couleurRectangle);
	rectangleSo1.setPosition(sf::Vector2f(x + 102.f, y));
	(*window).draw(rectangleSo1);

	sf::RectangleShape rectangleSo2(sf::Vector2f(-(float)pourcentage * 2.f + 200.f, 15.f));
	rectangleSo2.setOutlineColor(sf::Color::White);
	rectangleSo2.setOutlineThickness(1.f);
	rectangleSo2.setFillColor(sf::Color::Black);
	rectangleSo2.setPosition(sf::Vector2f(x + 102.f + (float)pourcentage * 2.f, y));
	(*window).draw(rectangleSo2);

	afficherTexte(x + 152.f, y, conversion(P->stats().soinsDonner()), sf::Color::White, window);

	x += 225.f;
	couleurRectangle = sf::Color::Magenta;
	categorie = "Bouclié provoqués";
	pourcentage = (int)(100.f * ((float)P->stats().bouclierDonner() / (float)E.meilleurBouclier()->stats().bouclierDonner()));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}
	afficherTexte(x + 150.f, 5.f, categorie, sf::Color::Magenta, window);

	sf::RectangleShape rectangleBo1(sf::Vector2f((float)pourcentage * 2.f, 15.f));
	rectangleBo1.setOutlineColor(sf::Color::White);
	rectangleBo1.setOutlineThickness(1.f);
	rectangleBo1.setFillColor(couleurRectangle);
	rectangleBo1.setPosition(sf::Vector2f(x + 102.f, y));
	(*window).draw(rectangleBo1);

	sf::RectangleShape rectangleBo2(sf::Vector2f(-(float)pourcentage * 2.f + 200.f, 15.f));
	rectangleBo2.setOutlineColor(sf::Color::White);
	rectangleBo2.setOutlineThickness(1.f);
	rectangleBo2.setFillColor(sf::Color::Black);
	rectangleBo2.setPosition(sf::Vector2f(x + 102.f + (float)pourcentage * 2.f, y));
	(*window).draw(rectangleBo2);

	afficherTexte(x + 152.f, y, conversion(P->stats().bouclierDonner()), sf::Color::White, window);
}

void AffichageCombat::dessinerStatsEquipeJoueur(Equipes J, sf::RenderWindow* window) const
{
	for (int i = 0; i < J.taille(); i++) {
		dessinerStatsJoueur(i + 1,J, false, J.perso(i), window);
	}
}

void AffichageCombat::dessinerStatsEquipeIA(Equipes I, sf::RenderWindow* window) const
{
	for (int i = 0; i < I.taille(); i++) {
		dessinerStatsJoueur(i + 1, I, true, I.perso(i), window);
	}
}
void AffichageCombat::dessinerDeuxEquipes(Equipes Joueur, Equipes IA, Combat & C, sf::RenderWindow* window) const
{
	window->draw(C.fond());
	dessinerEquipeJoueur(Joueur, window);
	dessinerEquipeIA(IA, window);
	afficherTexte(5, 3, "Tour : " + std::to_string(C.tour() + 1), sf::Color::Magenta, window);
	AffichageCombat().dessinerTour(C.quiJoue(), C.quiJoueIndex(), window);
	sf::Event event;
	while (window->pollEvent(event))
	{

	}
	(*window).display();
	sf::Time  DELAY = sf::milliseconds(Delais().getDelais() * 20);
	sf::sleep(DELAY);
	(*window).clear();
}

void AffichageCombat::dessinerStatistiques(Equipes Joueur, Equipes IA, Combat& C, sf::RenderWindow* window) const
{
	(*window).clear();
	dessinerStatsEquipeJoueur(Joueur, window);
	dessinerStatsEquipeIA(IA, window);
	sf::Event event;
	while (window->pollEvent(event))
	{

	}
	(*window).display();
}
void AffichageCombat::dessinerAttaque(Personnage* Attaquant, Personnage* Defenseur, sf::RenderWindow* window) {

	int i;
	int j;
	if (!Attaquant->equipeAllier().ia()) {
		i = Attaquant->indiceEquipe() + 1;
		j = Defenseur->indiceEquipe() + 1;
	}
	else {
		j = Attaquant->indiceEquipe() + 1;
		i = Defenseur->indiceEquipe() + 1;
	}

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(385.f, -25.f + 70 * (float)i)),
		sf::Vertex(sf::Vector2f(800.f,  -25.f + 70 * (float)j))
	};
	(*window).draw(line, 2, sf::Lines);

	if (!Attaquant->equipeAllier().ia()) {
		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(780.f, -5.f + 70 * (float)j)),
			sf::Vertex(sf::Vector2f(800.f,  -25.f + 70 * (float)j))
		};
		(*window).draw(line2, 2, sf::Lines);

		sf::Vertex line3[] =
		{
			sf::Vertex(sf::Vector2f(780.f, -45.f + 70 * (float)j)),
			sf::Vertex(sf::Vector2f(800.f,  -25.f + 70 * (float)j))
		};
		(*window).draw(line3, 2, sf::Lines);
	}
	else {

		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(405.f, -5.f + 70 * (float)i)),
			sf::Vertex(sf::Vector2f(385.f,  -25.f + 70 * (float)i))
		};
		(*window).draw(line2, 2, sf::Lines);

		sf::Vertex line3[] =
		{
			sf::Vertex(sf::Vector2f(405.f, -45.f + 70 * (float)i)),
			sf::Vertex(sf::Vector2f(385.f,  -25.f + 70 * (float)i))
		};

		(*window).draw(line3, 2, sf::Lines);
	}	
}

void AffichageCombat::afficherStats(Equipes joueur, sf::RenderWindow* window) const {
	afficherTexte(400.f, 20.f, "Statistiques du dernier combat : ", sf::Color::White, window);
	afficherTexte(30.f, 60.f, "Meilleur DPS : " + joueur.meilleurDegats()->nom() + " " + std::to_string(joueur.meilleurDegats()->stats().degatsProvoquer()) + " degats.", sf::Color::White, window);
	afficherTexte(30.f, 100.f, "Meilleur TANK : " + joueur.meilleurTank()->nom() + " " + std::to_string(joueur.meilleurTank()->stats().degatsRecu()) + " degats.", sf::Color::White, window);
	afficherTexte(30.f, 140.f, "Meilleur Soigneur : " + joueur.meilleurSoigneur()->nom() + " " + std::to_string(joueur.meilleurSoigneur()->stats().soinsDonner()) + " points de vie.", sf::Color::White, window);
	afficherTexte(30.f, 180.f, "Meilleur Bouclier : " + joueur.meilleurBouclier()->nom() + " " + std::to_string(joueur.meilleurBouclier()->stats().bouclierDonner()) + " bouclier.", sf::Color::White, window);
	afficherTexte(30.f, 220.f, "Meilleur augmentation de force : " + joueur.meilleurAugmentationForce()->nom() + " " + std::to_string(joueur.meilleurAugmentationForce()->stats().augmentationForce()) + " points.", sf::Color::White, window);
	afficherTexte(30.f, 260.f, "Meilleur augmentation de vie maximum : " + joueur.meilleurAugmentationVieMax()->nom() + " " + std::to_string(joueur.meilleurAugmentationVieMax()->stats().augmentationVieMax()) + " PV.", sf::Color::White, window);
	afficherTexte(30.f, 300.f, "Meilleur augmentation de reduction de degats : " + joueur.meilleurAugmentationReduction()->nom() + " " + std::to_string(joueur.meilleurAugmentationReduction()->stats().augmentationReduction()) + " %.", sf::Color::White, window);
	afficherTexte(30.f, 340.f, "Meilleur augmentation de chance de coup habile : " + joueur.meilleurAugmentationHabileter()->nom() + " " + std::to_string(joueur.meilleurAugmentationHabileter()->stats().augmentationChanceHabileter()) + " %.", sf::Color::White, window);
	afficherTexte(30.f, 380.f, "Meilleur augmentation de degats critique : " + joueur.meilleurAugmentationDegatsCritiques()->nom() + " " + std::to_string(joueur.meilleurAugmentationDegatsCritiques()->stats().augmentationDegatsCritique()) + " %.", sf::Color::White, window);
	afficherTexte(30.f, 420.f, "Meilleur augmentation de chance de coup critique : " + joueur.meilleurAugmentationChanceCritiques()->nom() + " " + std::to_string(joueur.meilleurAugmentationChanceCritiques()->stats().augmentationCoupCritiques()) + " %.", sf::Color::White, window);
	afficherTexte(30.f, 460.f, "Meilleur augmentation de chance de double attaques : " + joueur.meilleurAugmentationChanceDoubleAttaque()->nom() + " " + std::to_string(joueur.meilleurAugmentationChanceDoubleAttaque()->stats().augmentationChanceDoubleAttaque()) + " %.", sf::Color::White, window);
	afficherTexte(30.f, 500.f, "Plus grand nombre d'attaques reçues : " + joueur.meilleurNombresAttaquesRecues()->nom() + " " + std::to_string(joueur.meilleurNombresAttaquesRecues()->stats().nbAttaquesRecues()) + " attaques subis.", sf::Color::White, window);
	afficherTexte(30.f, 540.f, "Plus grand nombre d'attaques envoyer : " + joueur.meilleurNombreAttaquesEnvoyes()->nom() + " " + std::to_string(joueur.meilleurNombreAttaquesEnvoyes()->stats().nbAttaques()) + " attaques envoyés.", sf::Color::White, window);
	afficherTexte(30.f, 580.f, "Plus grosse attaque envoyer : " + joueur.plusGrosseAttaqueEnvoyer()->nom() + " " + std::to_string(joueur.plusGrosseAttaqueEnvoyer()->stats().plusGrosseAttaqueEnvoyer()) + " dégats.", sf::Color::White, window);
	afficherTexte(30.f, 620.f, "Plus grosse attaque recue : " + joueur.plusGrosseAttaqueRecue()->nom() + " " + std::to_string(joueur.plusGrosseAttaqueRecue()->stats().plusGrosseAttaqueRecue()) + " dégats.", sf::Color::White, window);

	std::cout << "Combat finis" << std::endl;
}

void AffichageCombat::dessinerTour(std::vector<Personnage*> quiJoue,int index, sf::RenderWindow* window) const
{
	float hauteur1 = 1026.f;
	float hauteur2 = 1045.f;
	float rectangleHauteur = hauteur2 - hauteur1;

	int nbQuiJoue = quiJoue.size();

	sf::Color couleurRectangle = sf::Color::Magenta;
	sf::Color couleurTexte = sf::Color::White;

	float rectangleLargeur = 1200.f / (float)nbQuiJoue;

	sf::RectangleShape rectangBlack(sf::Vector2f(1200.f, rectangleHauteur));
	rectangBlack.setOutlineColor(sf::Color::Black);
	rectangBlack.setOutlineThickness(1.f);
	rectangBlack.setFillColor(couleurRectangle);
	float positionX = 0.f;
	rectangBlack.setPosition(sf::Vector2f(0.f, hauteur1));

	for (int i = 0;i < nbQuiJoue;i++) {
		sf::RectangleShape rectangTour(sf::Vector2f(rectangleLargeur -4.f, rectangleHauteur));
		rectangTour.setOutlineColor(sf::Color::White);
		rectangTour.setOutlineThickness(1.f);
		if (index == i) {
			couleurRectangle = sf::Color::Blue;
		}
		else if (index < i) {
			couleurRectangle = sf::Color::Black;
		}
		else {
			couleurRectangle = sf::Color::Magenta;
		}
		rectangTour.setFillColor(couleurRectangle);
		positionX = rectangleLargeur * (float)i + 2.f;
		rectangTour.setPosition(sf::Vector2f(positionX , hauteur1));
		(*window).draw(rectangTour);
		afficherTexte(positionX +2.f, (hauteur1 + hauteur2) / 2.0 -4.f, quiJoue.at(i)->nom().substr(0,3), couleurTexte, window);
	}
	
}

void AffichageCombat::cleanMainZone(sf::RenderWindow* window)const
{
	float hauteur1 = 20.f;
	float hauteur2 = 800.f;
	float rectangleHauteur = hauteur2 - hauteur1;

	sf::Color couleurRectangle = sf::Color::Black;

	float rectangleLargeur = 1200.f;

	sf::RectangleShape rectangBlack(sf::Vector2f(rectangleLargeur, rectangleHauteur));
	rectangBlack.setOutlineColor(sf::Color::Black);
	rectangBlack.setOutlineThickness(1.f);
	rectangBlack.setFillColor(couleurRectangle);
	float positionX = 0.f;
	rectangBlack.setPosition(sf::Vector2f(positionX, hauteur1));
	(*window).draw(rectangBlack);

	sf::RectangleShape rectangBlack2(sf::Vector2f(rectangleLargeur -100., 100.f));
	rectangBlack2.setOutlineColor(sf::Color::Black);
	rectangBlack2.setOutlineThickness(1.f);
	rectangBlack2.setFillColor(couleurRectangle);
	positionX = 0.f;
	rectangBlack2.setPosition(sf::Vector2f(100.f, 0.f));
	(*window).draw(rectangBlack2);	
}
