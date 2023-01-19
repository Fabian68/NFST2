#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Bouton
{
public:
	Bouton(float xDepart, float yDepart, std::string texte,sf::Color couleurRectangle = sf::Color::Black, sf::Color couleurBordure = sf::Color::White, sf::Color couleurTexte = sf::Color::White);
	void afficher(sf::RenderWindow * window )const;
	bool comprendLesCoord(float x, float y,  std::pair < sf::SoundBuffer,std::vector< sf::Sound >> & allSounds);
	~Bouton();
private:
	float _x1, _x2, _y1, _y2;
	sf::Color _couleurRectangle, _couleurTexte, _couleurBordure;
	float _xPos, _yPos;
	float _xSize, _ySize;
	std::string _texte;
};

