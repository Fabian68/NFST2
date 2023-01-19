#include "Animaux.h"
#include <iostream>
#include "Bouton.h"

Animaux::Animaux()
{
	int zero = 0;
	int moins1 = -1;

	FILE* file = fopen("Animaux.txt", "r");
	if (file == NULL) {
		std::ofstream os("Animaux.txt",std::ios::binary);
		
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 9; j++) {
				//os << 0 << " ";
				os.write((char*)&zero, sizeof(zero));
			}
			//os << -1 << " ";
			//os << std::endl;
			os.write((char*)&moins1, sizeof(moins1));
		}
		os.close();
	}
	else {
		fclose(file);
	}

	_animauxPosseder.resize(30);
	_animauxUtiliser.resize(30);

	for (int i = 0; i < 30; i++) {
		_animauxPosseder[i].resize(9);
	}

	std::ifstream is("Animaux.txt",std::ios::binary);
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 9; j++) {
			//is >> _animauxPosseder[i][j];
			is.read((char*)&_animauxPosseder[i][j], sizeof(_animauxPosseder[i][j]));
		}
		//is >> _animauxUtiliser[i];
		is.read((char*)&_animauxUtiliser[i], sizeof(_animauxUtiliser[i]));
	}
	is.close();
	_listeAnimaux.resize(16);
	for (int i = 0; i < 16; i++) {
		_listeAnimaux[i] = Animal(i);
	}
}

void Animaux::animalDuPersonnage(int indicePersonnage, int& indiceAnimal, int& rareteAnimal) const
{
	indiceAnimal = _animauxUtiliser[indicePersonnage];
	rareteAnimal = _animauxPosseder[indicePersonnage][indiceAnimal];
}

int Animaux::indiceAnimal(int indicePersonnage)const {
	return _animauxUtiliser[indicePersonnage];
}
int Animaux::rareteAnimal(int indicePersonnage, int indiceAnimal)const {
	if (indiceAnimal == -1) {
		return -1;
	}
	else {
		return _animauxPosseder[indicePersonnage][indiceAnimal];
	}
}

bool Animaux::animalDebloquer(int indicePersonnage, int indiceAnimal, int rareteAnimal) const
{
	return _animauxPosseder[indicePersonnage][indiceAnimal]>=rareteAnimal;
}

void Animaux::deblocageAnimal(int indicePersonnage, int indiceAnimal, int rareteAnimal,std::string perso, sf::RenderWindow* window, std::pair < sf::SoundBuffer, std::vector< sf::Sound>>& allSounds)
{
	std::string txt= "";
	txt+= perso + " a débloquer un animal ";
	switch (indiceAnimal) {
	case 0:
		txt += " de soins de zone ";
		break;
	case 1:
		txt += " qui soigne le plus faible ";
		break;
	case 2:
		txt += " qui soigne un allier aleatoire ";
		break;
	case 3:
		txt += " qui attaque l'ennemi le plus faible ";
		break;
	case 4:
		txt += " qui attaque l'équipe ennemi ";
		break;
	case 5:
		txt += " qui attaque l'ennemi le plus fort ";
		break;
	case 6:
		txt += " qui bouclier de zone ";
		break;
	case 7:
		txt += " qui bouclier le plus faible ";
		break;
	case 8:
		txt += " qui bouclier une cible aleatoire ";
		break;
	case 9:
		txt += " qui soigne et bouclier de zone ";
		break;
	}
	txt += " de rarete ";
	switch (rareteAnimal) {
	case 1:
		txt += " commune ";
		break;
	case 2:
		txt += " rare ";
		break;
	case 3:
		txt += " epique ";
		break;
	case 4:
		txt += " LEGENDAIRE ";
		break;
	case 5:
		txt += " CHEATER ";
		break;
	}
	/*std::cout << ", voulez voul l'equiper ? Entrer le chiffre 0 si oui ";
	int entrer;
	std::cin >> entrer;
	if (entrer == 0) {
		_animauxUtiliser[indicePersonnage] = indiceAnimal;
	}*/
	Bouton(300.f, 400.f, txt, sf::Color::Black, sf::Color::Green, sf::Color::Green).afficher(window);
	
	Bouton Equiper(340.f, 450.f, " Equiper ", sf::Color::Black, sf::Color::Green, sf::Color::Green);
	Equiper.afficher(window);
	Bouton NePasEquiper(440.f, 450.f, " NePasEquiper ", sf::Color::Black, sf::Color::Green, sf::Color::Green);
	NePasEquiper.afficher(window);

	
	bool selectionner = false;
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

				if (Equiper.comprendLesCoord(xc, yc,allSounds)) {
					selectionner = true;
					_animauxUtiliser[indicePersonnage] = indiceAnimal;
				}
				else if (NePasEquiper.comprendLesCoord(xc, yc,allSounds)) {
					selectionner = true;
				}
			}
		}
	} while (!selectionner);
	(*window).display();
	(* window).clear();
	_animauxPosseder[indicePersonnage][indiceAnimal] = rareteAnimal;
	sauvegarder();
}

void Animaux::sauvegarder()
{
	std::ofstream os("Animaux.txt",std::ios::binary);

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 9; j++) {
			//os << _animauxPosseder[i][j]<<" ";
			os.write((char*)&_animauxPosseder[i][j], sizeof(_animauxPosseder[i][j]));
		}
		//os << _animauxUtiliser[i] << " ";
		//os << std::endl;
		os.write((char*)&_animauxUtiliser[i], sizeof(_animauxUtiliser[i]));
	}
	os.close();
}

Animal Animaux::animalNumero(int indice) const
{
	return _listeAnimaux[indice];
}

void Animaux::setAnimalPersonnage(int indicePersonnage, int indiceAnimal)
{
	_animauxUtiliser[indicePersonnage] = indiceAnimal;
	sauvegarder();
}
