#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Personnage;
class Experiences;
class Combat;
class Equipes
{
public:
	Equipes();
	~Equipes();
	Equipes(bool equipeIA);
	int taille()const;
	Personnage* operator[](int i)const;
	Personnage* perso(int i);
	int nbEnVie() const;
	void setIndiceANul(int indice);
	Personnage* plusProcheVivant();
	Personnage* plusLoinVivant();
	Personnage* plusFaible();
	Personnage* plusFort();
	Personnage* moinsResistant();
	Personnage* aleatoireEnVie();
	Personnage* meilleurDegats();
	Personnage* meilleurTank();
	Personnage* meilleurSoigneur();
	Personnage* meilleurBouclier();
	Personnage* meilleurAugmentationForce();
	Personnage* meilleurAugmentationVieMax();
	Personnage* meilleurAugmentationReduction();
	Personnage* meilleurAugmentationDegatsCritiques();
	Personnage* meilleurAugmentationChanceCritiques();
	Personnage* meilleurAugmentationHabileter();
	Personnage* meilleurAugmentationChanceDoubleAttaque();
	Personnage* meilleurNombreAttaquesEnvoyes();
	Personnage* meilleurNombresAttaquesRecues();
	Personnage* plusGrosseAttaqueRecue();
	Personnage* plusGrosseAttaqueEnvoyer();
	void attaqueZone(int Degats,Personnage*Attaquant, Combat & C, sf::RenderWindow* window, std::vector< sf::Sound>& allSounds);
	void soignerZone(int soins, Personnage* Soigneur, Combat & C, sf::RenderWindow* window);
	void bouclierZone(int bouclier, Personnage* bouclierMan, Combat & C, sf::RenderWindow* window);
	void vider();
	void liberer();
	void chargerEquipe(Equipes & Liste);
	void sauvegarderEquipe();
	int xpDonner() const;
	void ajouterPerso(Personnage * P);
	void retirerDernierPerso();
	void ajouterExperience(int xp, Experiences E);
	void setAllierEtEnnemis(Equipes & E);
	bool estEnVie() const;
	bool ia() const;
	bool comprendPersonnage(int id) const;
	int place(Personnage* P) const;
	//void modifierStats(std::vector<double> listeRatioModification);
private:
	std::vector<Personnage*> _equipe;
	bool _equipeIA;
};

