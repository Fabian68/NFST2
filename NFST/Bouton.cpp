#include "Bouton.h"
#include <iostream>


Bouton::Bouton(float xDepart, float yDepart, std::string texte, sf::Color couleurRectangle, sf::Color couleurBordure, sf::Color couleurTexte) : _xPos{xDepart}, _yPos{yDepart},_couleurRectangle{couleurRectangle},_couleurBordure{couleurBordure},_couleurTexte{couleurTexte}, _texte{texte}
{
	_xSize = 8.f * (float)texte.size()+20.f;
	_ySize =  40.f;

	_x1 = _xPos;
	_y1 = _yPos;

	_x2 = _x1 + _xSize;
	_y2 = _y1 + _ySize;
	if (!buffer.loadFromFile("vine-boom.ogg")) {

	}
	else {
		sound.setBuffer(buffer);
		//sound.play();
	}
}

void Bouton::afficher(sf::RenderWindow * window) const
{
	sf::Font _font;
	if (!_font.loadFromFile("arial.ttf"))
	{
		std::cout << "Erreur chargement font" << std::endl;
	}
	sf::RectangleShape rectangle(sf::Vector2f(_xSize, _ySize));
	rectangle.setOutlineColor(_couleurBordure);
	rectangle.setOutlineThickness(2.f);
	rectangle.setFillColor(_couleurRectangle);
	rectangle.setPosition(sf::Vector2f(_xPos, _yPos));

	sf::Text text;
	text.setFont(_font);
	text.setString(_texte);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(16);
	text.setPosition(sf::Vector2f(_xPos+5.f, _yPos+10.f));

	(* window).draw(rectangle);
	(* window).draw(text);
}

bool Bouton::comprendLesCoord(float x, float y) 
{
	if ((x >= _x1 && x <= _x2) && (y >= _y1 && y <= _y2)) {
	
		sound.play();
		
		//sf::sleep(sf::milliseconds(500));
		
		return true;
	}
	else {
		
		return false;
	}
}

Bouton::~Bouton()
{
	
}
