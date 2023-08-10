#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <SFML/Audio.hpp>
class Personnage;
class Equipes;
class Zones;
class Animaux;
class Objets;
class Succes;

class Affichage
{
public:
	Affichage();

	void afficherTexte(float x, float y, std::string texte,sf::Color couleurTexte, sf::RenderWindow * window)const;

	void affichageTexte(float x, float y, std::string texte, sf::Color couleurTexte, sf::RenderWindow * window);
	
	void afficherJoueurs(int indice, Equipes& Liste, sf::RenderWindow * window, std::vector< sf::Sound >& allSounds) const;
	void afficherCompetences(int indice, Equipes& Liste, sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) const;
	void afficherMecaniques( sf::RenderWindow* window, std::vector< sf::Sound >& allSounds) const;
	void choixObjets(int page, Objets  obj, bool premierObjet, int indicePersonnage, Equipes & Liste, sf::RenderWindow * window, std::vector< sf::Sound >& allSounds,int set =1)const;
	void afficherSucces(int page, Succes succes, sf::RenderWindow* window, std::vector<sf::Sound>& allSounds) const;
	void afficherAnimaux(Animaux A, sf::RenderWindow * window, std::vector< sf::Sound >& allSounds)const;
	
	void dessinerTexte(std::string texte, sf::RenderWindow * window)const;

	void choixNiveau(Zones Z, Objets obj,int & niveau,int & repetition, sf::RenderWindow * window, std::vector< sf::Sound >& allSounds)const;
	void afficherObjetsDeblocableNiveau(Objets obj, int niveau, sf::RenderWindow * window)const;
	void menuModifierEquipe(Equipes& Gentil, Equipes choix, Zones& Z,int max, sf::RenderWindow * window, std::vector< sf::Sound >& allSounds)const;

	~Affichage();
private:
	
};

