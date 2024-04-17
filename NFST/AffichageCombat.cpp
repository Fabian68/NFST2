#include "AffichageCombat.h"
#include "Combat.h"

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

AffichageCombat::AffichageCombat()
{
}

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
void AffichageCombat::dessinerJoueur(int indice, bool equipeIA, Personnage* P, sf::RenderWindow* window) const
{
	float x;
	sf::Color couleurTexte;
	sf::Color couleurFond = sf::Color::Black;
	if (equipeIA) {
		x = 1180.f - 460.f;
		couleurTexte = sf::Color::Red;
	}
	else {
		x = 130.f;
		couleurTexte = sf::Color::Green;
	}
	std::string str = P->nom() + " " + std::to_string(P->niveau());
	
	float y = -65.f + 100.f * (float)indice;

	sf::RectangleShape rectangle1(sf::Vector2f(360.f, 65.f));
	rectangle1.setOutlineColor(couleurTexte);
	rectangle1.setOutlineThickness(1.f);
	if (P->estSonTour()) {
		rectangle1.setFillColor(sf::Color(0,0,102));
	}
	else {
		rectangle1.setFillColor(couleurFond);
	}
	rectangle1.setPosition(sf::Vector2f(x, y));
	(*window).draw(rectangle1);

	if (equipeIA) {
		P->sprite().setPosition(sf::Vector2f(x-136.f , y - 30.f));
	}
	else {
		P->sprite().setPosition(sf::Vector2f(x + 361.f, y - 30.f));
	}
	window->draw(P->sprite());

	afficherTexte(x + 2.f, y + 5.f, str, couleurTexte, window);
	
	int pourcentageVie = P->pourcentageVie();
	int pourcentageBouclier = P->pourcentageBouclier();

	sf::Color couleurStatutEmpoisonner;
	sf::Color couleurStatutBruler;
	if (P->status().estEmpoisoner()) {
		couleurStatutEmpoisonner = sf::Color::Magenta;
	}
	else {
		couleurStatutEmpoisonner = sf::Color::Black;
	}
	sf::CircleShape circle1(5.f);
	circle1.setPosition(x - 15.f, y + 1);
	circle1.setFillColor(couleurStatutEmpoisonner);
	circle1.setOutlineColor(sf::Color::White);
	circle1.setOutlineThickness(1.f);
	(*window).draw(circle1);

	if (P->status().estBruler()) {
		couleurStatutBruler = sf::Color::Red;
	}
	else {
		couleurStatutBruler = sf::Color::Black;
	}

	sf::CircleShape circle2(5.f);
	circle2.setPosition(x - 15.f, y + 13.f);
	circle2.setFillColor(couleurStatutBruler);
	circle2.setOutlineColor(sf::Color::White);
	circle2.setOutlineThickness(1.f);
	(*window).draw(circle2);

	sf::Color couleurStatutFragiliser;
	sf::Color couleurStatutProteger;

	if (P->status().estFragiliser()) {
		couleurStatutFragiliser = sf::Color::Red;
	}
	else {
		couleurStatutFragiliser = sf::Color::Black;
	}

	sf::RectangleShape rectangle2(sf::Vector2f(10.f, 10.f));
	rectangle2.setOutlineColor(sf::Color::White);
	rectangle2.setOutlineThickness(1.f);
	rectangle2.setFillColor(couleurStatutFragiliser);
	rectangle2.setPosition(sf::Vector2f(x - 15.f, y + 30.f));
	(*window).draw(rectangle2);

	if (P->status().estProteger()) {
		couleurStatutProteger = sf::Color::Green;
	}
	else {
		couleurStatutProteger = sf::Color::Black;
	}

	sf::RectangleShape rectangle3(sf::Vector2f(10.f, 10.f));
	rectangle3.setOutlineColor(sf::Color::White);
	rectangle3.setOutlineThickness(1.f);
	rectangle3.setFillColor(couleurStatutProteger);
	rectangle3.setPosition(sf::Vector2f(x - 15.f, y + 45.f));
	(*window).draw(rectangle3);

	sf::RectangleShape rectangleVie1(sf::Vector2f((float)pourcentageVie * 2.f, 15.f));
	rectangleVie1.setOutlineColor(sf::Color::White);
	rectangleVie1.setOutlineThickness(1.f);
	rectangleVie1.setFillColor(sf::Color::Green);
	rectangleVie1.setPosition(sf::Vector2f(x + 2.f, y + 25.f));
	(*window).draw(rectangleVie1);

	sf::RectangleShape rectangleVie2(sf::Vector2f(-(float)pourcentageVie * 2.f + 200.f, 15.f));
	rectangleVie2.setOutlineColor(sf::Color::White);
	rectangleVie2.setOutlineThickness(1.f);
	rectangleVie2.setFillColor(sf::Color::Black);
	rectangleVie2.setPosition(sf::Vector2f(x + 2.f + (float)pourcentageVie * 2.f, y + 25.f));
	(*window).draw(rectangleVie2);

	sf::RectangleShape rectangleBouclier1(sf::Vector2f((float)pourcentageBouclier * 2.f, 15.f));
	rectangleBouclier1.setOutlineColor(sf::Color::White);
	rectangleBouclier1.setOutlineThickness(1.f);
	rectangleBouclier1.setFillColor(sf::Color::Magenta);
	rectangleBouclier1.setPosition(sf::Vector2f(x + 2.f, y + 45.f));
	(*window).draw(rectangleBouclier1);

	sf::RectangleShape rectangleBouclier2(sf::Vector2f(-(float)pourcentageBouclier * 2.f + 200.f, 15.f));
	rectangleBouclier2.setOutlineColor(sf::Color::White);
	rectangleBouclier2.setOutlineThickness(1.f);
	rectangleBouclier2.setFillColor(sf::Color::Black);
	rectangleBouclier2.setPosition(sf::Vector2f(x + 2.f + (float)pourcentageBouclier * 2.f, y + 45.f));
	(*window).draw(rectangleBouclier2);

	for (int i = 0;i < P->mana();i++) {
		sf::RectangleShape rectangMana(sf::Vector2f(2.f, 2.f));
		rectangMana.setOutlineColor(sf::Color::Blue);
		rectangMana.setOutlineThickness(1.f);
		rectangMana.setFillColor(sf::Color::Cyan);
		rectangMana.setPosition(sf::Vector2f(x + 3.f * (float)i + 1.f, y + 62.f));
		(*window).draw(rectangMana);
	}

	couleurTexte = sf::Color::White;

	str = conversion(P->vie()) + " / " + conversion(P->vieMax());
	afficherTexte(x + 210.f, y + 23.f, str, couleurTexte, window);

	str = conversion(P->bouclier()) + " / " + conversion(P->bouclierMax());
	afficherTexte(x + 210.f, y + 43.f, str, couleurTexte, window);
	
	dessinerTexteModificationVie(P, window);

	int pourcentage = 0;
	float max = (float)std::max(P->equipeAllier().meilleurDegats()->stats().degatsProvoquer(), P->equipeEnnemi().meilleurDegats()->stats().degatsProvoquer());
	pourcentage = (int)(100.f * ((float)P->stats().degatsProvoquer() / max));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}

	sf::Color couleur1 = sf::Color::Red;
	sf::Color couleur2 = sf::Color::Black;
	float val1 = (float)pourcentage;
	float val2 = -(float)pourcentage + 100.f;
	x = 5.f;
	if (equipeIA) {
		x = 1088.f;
		val2 = (float)pourcentage;
		val1 = -(float)pourcentage + 100.f;
		couleur1 = sf::Color::Black;
		couleur2 = sf::Color::Red;
	}
	
	sf::RectangleShape rectangleP1(sf::Vector2f(val1 , 15.f));
	rectangleP1.setOutlineColor(sf::Color::White);
	rectangleP1.setOutlineThickness(1.f);
	rectangleP1.setFillColor(couleur1);
	rectangleP1.setPosition(sf::Vector2f(x , y));
	(*window).draw(rectangleP1);

	sf::RectangleShape rectangleP2(sf::Vector2f(val2, 15.f));
	rectangleP2.setOutlineColor(sf::Color::White);
	rectangleP2.setOutlineThickness(1.f);
	rectangleP2.setFillColor(couleur2);
	rectangleP2.setPosition(sf::Vector2f(x  + val1 , y));
	(*window).draw(rectangleP2);

	afficherTexte(x + 52.f, y, conversion(P->stats().degatsProvoquer()), sf::Color::White, window);

	y += 16.f;
	pourcentage = 0;
	max = (float)std::max(P->equipeAllier().meilleurTank()->stats().degatsRecu(), P->equipeEnnemi().meilleurTank()->stats().degatsRecu());
	pourcentage = (int)(100.f * ((float)P->stats().degatsRecu() / max));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}

	couleur1 = sf::Color(51, 102, 0);
	couleur2 = sf::Color::Black;

	val1 = (float)pourcentage;
	val2 = -(float)pourcentage + 100.f;
	if (equipeIA) {
		val2 = (float)pourcentage;
		val1 = -(float)pourcentage + 100.f;
		couleur1 = sf::Color::Black;
		couleur2 = sf::Color(51, 102, 0);
	}
	sf::RectangleShape rectangleD1(sf::Vector2f(val1, 15.f));
	rectangleD1.setOutlineColor(sf::Color::White);
	rectangleD1.setOutlineThickness(1.f);
	rectangleD1.setFillColor(couleur1);
	rectangleD1.setPosition(sf::Vector2f(x, y));
	(*window).draw(rectangleD1);

	sf::RectangleShape rectangleD2(sf::Vector2f(val2, 15.f));
	rectangleD2.setOutlineColor(sf::Color::White);
	rectangleD2.setOutlineThickness(1.f);
	rectangleD2.setFillColor(couleur2);
	rectangleD2.setPosition(sf::Vector2f(x + val1, y));
	(*window).draw(rectangleD2);

	afficherTexte(x + 52.f, y, conversion(P->stats().degatsRecu()), sf::Color::White, window);

	y += 16.f;
	pourcentage = 0;
	max = (float)std::max(P->equipeAllier().meilleurSoigneur()->stats().soinsDonner(), P->equipeEnnemi().meilleurSoigneur()->stats().soinsDonner());
	pourcentage = (int)(100.f * ((float)P->stats().soinsDonner() / max));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}

	couleur1 = sf::Color::Green;
	couleur2 = sf::Color::Black;

	val1 = (float)pourcentage;
	val2 = -(float)pourcentage + 100.f;
	if (equipeIA) {
		val2 = (float)pourcentage;
		val1 = -(float)pourcentage + 100.f;
		couleur1 = sf::Color::Black;
		couleur2 = sf::Color::Green;
	}
	sf::RectangleShape rectangleS1(sf::Vector2f(val1, 15.f));
	rectangleS1.setOutlineColor(sf::Color::White);
	rectangleS1.setOutlineThickness(1.f);
	rectangleS1.setFillColor(couleur1);
	rectangleS1.setPosition(sf::Vector2f(x, y));
	(*window).draw(rectangleS1);

	sf::RectangleShape rectangleS2(sf::Vector2f(val2, 15.f));
	rectangleS2.setOutlineColor(sf::Color::White);
	rectangleS2.setOutlineThickness(1.f);
	rectangleS2.setFillColor(couleur2);
	rectangleS2.setPosition(sf::Vector2f(x + val1, y));
	(*window).draw(rectangleS2);

	afficherTexte(x + 52.f, y, conversion(P->stats().soinsDonner()), sf::Color::White, window);

	y += 16.f;
	pourcentage = 0;
	max = (float)std::max(P->equipeAllier().meilleurBouclier()->stats().bouclierDonner(), P->equipeEnnemi().meilleurBouclier()->stats().bouclierDonner());
	pourcentage = (int)(100.f * ((float)P->stats().bouclierDonner() / max));
	if (pourcentage < 0 || pourcentage >100) {
		pourcentage = 0;
	}

	couleur1 = sf::Color::Magenta;
	couleur2 = sf::Color::Black;

	val1 = (float)pourcentage;
	val2 = -(float)pourcentage + 100.f;
	if (equipeIA) {
		val2 = (float)pourcentage;
		val1 = -(float)pourcentage + 100.f;
		couleur1 = sf::Color::Black;
		couleur2 = sf::Color::Magenta;
	}
	sf::RectangleShape rectangleB1(sf::Vector2f(val1, 15.f));
	rectangleB1.setOutlineColor(sf::Color::White);
	rectangleB1.setOutlineThickness(1.f);
	rectangleB1.setFillColor(couleur1);
	rectangleB1.setPosition(sf::Vector2f(x, y));
	(*window).draw(rectangleB1);

	sf::RectangleShape rectangleB2(sf::Vector2f(val2, 15.f));
	rectangleB2.setOutlineColor(sf::Color::White);
	rectangleB2.setOutlineThickness(1.f);
	rectangleB2.setFillColor(couleur2);
	rectangleB2.setPosition(sf::Vector2f(x + val1, y));
	(*window).draw(rectangleB2);

	afficherTexte(x + 52.f, y, conversion(P->stats().bouclierDonner()), sf::Color::White, window);
}

void AffichageCombat::dessinerEquipeJoueur(Equipes J, sf::RenderWindow* window) const
{
	for (int i = 0; i < J.taille(); i++) {
		dessinerJoueur(i + 1, false, J.perso(i), window);
	}
}

void AffichageCombat::dessinerEquipeIA(Equipes I, sf::RenderWindow* window) const
{
	for (int i = 0; i < I.taille(); i++) {
		dessinerJoueur(i + 1, true, I.perso(i), window);
	}
}

void AffichageCombat::dessinerStatsJoueur(int indice,Equipes E, bool equipeIA, Personnage* P, sf::RenderWindow* window) const
{
	float x=0.f;
	sf::Color couleurTexte = sf::Color::White;
	sf::Color couleurFond = sf::Color::Black;
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
	//cleanMainZone(window);
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

	
	//cleanMainZone(window);
}
void AffichageCombat::dessinerAttaque(Personnage* Attaquant, Personnage* Defenseur, sf::RenderWindow* window) {

	int i, j;
	if (!Attaquant->equipeAllier().ia()) {
		i = Attaquant->indiceEquipe() + 1;
		j = Defenseur->indiceEquipe() + 1;
		//animationCercle(390, -20 + 70 * i, 810, -20 + 70 * j);

	}
	else {
		j = Attaquant->indiceEquipe() + 1;
		i = Defenseur->indiceEquipe() + 1;
		//	animationCercle(810, -20 + 70 * j, 390, -20 + 70 * i);
	}

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(385.f, -25.f + 70 * (float)i)),
		sf::Vertex(sf::Vector2f(800.f,  -25.f + 70 * (float)j))
	};
	(*window).draw(line, 2, sf::Lines);

	//line(385, -25 + 70 * i, 800, -25 + 70 * j);

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

		//line(780, -5 + 70 *j, 800, -25 + 70 * j);
		//line(780, -45 + 70 * j, 800, -25 + 70 * j);
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
		//line(405, -5 + 70 * i, 385, -25 + 70 * i);
		//line(405, -45 + 70 * i, 385, -25 + 70 * i);

	}
	//(*window).display();
	
}

void AffichageCombat::afficherStats(Equipes joueur, sf::RenderWindow* window) {
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

void AffichageCombat::dessinerTour(std::vector<Personnage*> quiJoue,int index, sf::RenderWindow* window)
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
