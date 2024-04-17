#include "Succes.h"
#include <fstream>

Succes::Succes()
{
	int zero = 0;
	FILE* file = fopen("succes.txt", "r");
	if (file == NULL) {
		std::ofstream os("succes.txt", std::ios::binary);

		for (int i = 0; i < 100; i++) {
			os.write((char*)&zero, sizeof(zero));
			//os << 0;
			//os << std::endl;
		}
		os.close();
	}
	else {
		fclose(file);
	}
	_succesDebloquer.resize(100);
	std::ifstream is("succes.txt", std::ios::binary);
	for (int i = 0; i < 100; i++) {
		is.read((char*)&_succesDebloquer[i], sizeof(_succesDebloquer[i]));
		//is >> _objetsDebloquer[i];
	}
	is.close();

	_listeSucces.reserve(100);
	_succesCache.reserve(100);

	_listeSucces.push_back(std::make_pair("Trouver le texte BOING caché", "+ 1 à chaque stats pour chaque personnage" ));
	_succesCache.push_back(true);
	_listeSucces.push_back(std::make_pair("Finir le niveau 1", "Une médaille en chocolat"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Finir le niveau 5", "Nouveau personnage : Thomas"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Finir le niveau 10", "Nouveau personnage : Moustick"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Finir le niveau 15", "Nouveau personnage : Jean Baptiste"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Finir le niveau 20", "Nouveau personnage : Salim"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Finir le niveau 25", "Nouveau personnage : A VENIR"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Finir le niveau 50", "???"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Obtenir un objet légendaire", "Nouveau personnage : Bryan"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Obtenir un animal légendaire", "Nouveau personnage : Fiona"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Obtenir une orbe légendaire", "Nouveau personnage : Salim"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Obtenir l'oeuf de tortue", "Nouveau personnage : Tortue"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Obtenir la cendre de Phénix", "Nouveau personnage : Phénix"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Monter Nicolas au niveau 25", "Nouveau personnage : Isidore"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Monter Fiona au niveau 25", "Nouveau personnage : David"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Monter deux perso niveau 10", "Nouveau personnage : Sebastien"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Monter Fabian et Fiona niveau 10", "Nouveau personnage : Cloe"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Monter 3 personnages niveau 25", "Nouveau personnage : Amine"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Monter Nicolas et Sebastien au niv 10", "Nouveau personnage : Florian"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Monter Fabian, Fiona et Cloe au niv 25", "Nouveau personnage : Maelle"));
	_succesCache.push_back(false);
	_listeSucces.push_back(std::make_pair("Débloquer 10 succès", "Les combats seront 25% plus rapide"));
	_succesCache.push_back(true);
}

void Succes::sauvegarder()
{
	std::ofstream os("succes.txt", std::ios::binary);

	for (int i = 0; i < 100; i++) {
		os.write((char*)&_succesDebloquer[i], sizeof(_succesDebloquer[i]));
		
	}
	os.close();
}

bool Succes::estDebloque(int succes) const
{
	return _succesDebloquer[succes] == 1;
}

void Succes::affichageDeblocageSucces(int succes, std::vector< sf::Sound> allSounds) const
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(400, 200), "Succes débloqué");
	allSounds[3].play();
	sf::Color couleurTexte = sf::Color::White;
	sf::Color couleurFond = sf::Color::Black;

	std::string str = _listeSucces[succes].first;
	afficherTexte(20, 50, str, couleurTexte, window);

	str = _listeSucces[succes].second;
	afficherTexte(20, 100, str, couleurTexte, window);
	(*window).display();
	sf::Event event;
	while (window->pollEvent(event))
	{
		// on regarde le type de l'évènement...
		switch (event.type)
		{
			// fenêtre fermée
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

void Succes::debloquerSucces(int succes)
{
	_succesDebloquer[succes] = 1;
	sauvegarder();
}

void Succes::appliquerBonus(Personnage* P)
{
	if (estDebloque(0)) {
		P->ajouterVie(10);
		P->ajouterForce(1);
		P->ajouterVitesse(1);
	}
}

void Succes::afficherTexte(float x, float y, std::string texte, sf::Color couleurTexte, sf::RenderWindow* window)const {
	sf::Font _font;
	if (!_font.loadFromFile("arial.ttf"))
	{
	}
	sf::Text text;
	text.setFont(_font);
	text.setString(texte);

	text.setFillColor(couleurTexte);
	text.setCharacterSize(12);
	text.setPosition(sf::Vector2f(x, y));
	(*window).draw(text);
}

int Succes::nombres()const {
	return _listeSucces.size() ;
}

bool Succes::estCache(int i) const
{
	return _succesCache[i];
}

std::string Succes::nom(int i) const
{
	return _listeSucces[i].first;
}

std::string Succes::description(int i) const
{
	return _listeSucces[i].second;
}

int Succes::nbSuccesDebloque() const {
	int nb_succes_debloquer = 0;
	for (int i = 0;i < _succesDebloquer.size();i++) {
		if (_succesDebloquer[i] == 1) {
			nb_succes_debloquer += 1;
		}
	}
	return nb_succes_debloquer;
}