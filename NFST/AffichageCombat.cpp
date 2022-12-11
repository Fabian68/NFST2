#include "AffichageCombat.h"

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
		x = 1200.f - 95.f;
	}
	else {
		x = 310.f;
	}

	float y = -20.f + 70.f * (float)(P->indiceEquipe() + 1);

	std::string texte = " - " + conversion(montant);
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
		x = 1180.f - 360.f;
		couleurTexte = sf::Color::Red;
	}
	else {
		x = 20.f;
		couleurTexte = sf::Color::Green;
	}
	std::string str = P->nom() + " " + std::to_string(P->niveau());
	
	float y = -50.f + 70.f * (float)indice;

	sf::RectangleShape rectangle1(sf::Vector2f(360.f, 65.f));
	rectangle1.setOutlineColor(couleurTexte);
	rectangle1.setOutlineThickness(1.f);
	rectangle1.setFillColor(couleurFond);
	rectangle1.setPosition(sf::Vector2f(x, y));
	(*window).draw(rectangle1);

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
	circle1.setPosition(x - 20.f, y + 1);
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
	circle2.setPosition(x - 20.f, y + 13.f);
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

	couleurTexte = sf::Color::White;

	str = conversion(P->vie()) + " / " + conversion(P->vieMax());
	afficherTexte(x + 210.f, y + 23.f, str, couleurTexte, window);

	str = conversion(P->bouclier()) + " / " + conversion(P->bouclierMax());
	afficherTexte(x + 210.f, y + 43.f, str, couleurTexte, window);
	
	dessinerTexteModificationVie(P, window);
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

void AffichageCombat::dessinerDeuxEquipes(Equipes Joueur, Equipes IA, sf::RenderWindow* window) const
{
	dessinerEquipeJoueur(Joueur, window);
	dessinerEquipeIA(IA, window);
	
	(*window).display();
	sf::Time  DELAY = sf::milliseconds(Delais().getDelais() * 20);
	sf::sleep(DELAY);
	(*window).clear();
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
