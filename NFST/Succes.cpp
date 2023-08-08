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
	allSounds[1].play();
	sf::Color couleurTexte = sf::Color::White;
	sf::Color couleurFond = sf::Color::Black;

	std::string str = _listeSucces[succes].first;
	afficherTexte(20, 50, str, couleurTexte, window);

	str = _listeSucces[succes].second;
	afficherTexte(20, 100, str, couleurTexte, window);
	(*window).display();
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
