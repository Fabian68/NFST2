#pragma once

#include <string>
#include "Status.h"
#include "Equipes.h"
#include "Experiences.h"
#include "Orbes.h"
#include "Animaux.h"
#include "Statistiques.h"
#include "Objets.h"
#include <SFML/Audio.hpp>
const int CHOIXFORCE = 0;
const int CHOIXVIEMAX = 1;
const int CHOIXVITESSE = 2;
const int CHOIXVIE = 3;
const int CHOIXBOUCLIER = 4;

const int actionSOINS=0;
const int actionDEGATS=1;
const int actionBOUCLIER=2;
const int actionNULL=3;
class Personnage
{
public:
	Personnage(int id, Experiences E,Orbes O,Animaux A,Objets Obj, std::string nom, int vieLVL, int attaqueLVL, int vitesseLVL, int chanceDoubleAttaque, int chanceHabilete, int pourcentageReduction, int pourcentageDeviation, int pourcentageBlocage, int pourcentageEsquive, int pourcentageRicochet);
	Personnage(int LVL, std::string nom, int vieLVL, int attaqueLVL, int vitesseLVL, int chanceDoubleAttaque, int chanceHabilete, int pourcentageReduction, int pourcentageDeviation, int pourcentageBlocage, int pourcentageEsquive, int pourcentageRicochet,int indiceAnimal,int rareteAnimal);
	virtual ~Personnage();
	int id() const;
	int mana()const;
	std::string nom()const;
	long long int vie()const;
	long long int vieMax()const;
	void ajouterVieMax(long long int montant);
	void reduireVieMax(long long int montant);
	void reduireVie(long long int nb);
	int reduireBouclier(int nb);
	int pourcentageVie()const;
	int pourcentageBouclier() const;
	virtual void attaqueEnnemis(sf::RenderWindow* window, std::vector< sf::Sound > &allSounds)=0;
	virtual void passif(int tour, sf::RenderWindow* window, std::vector< sf::Sound > &allSounds) = 0 ;
	virtual void passifDefensif(sf::RenderWindow* window, std::vector< sf::Sound > &allSounds,int degats,Personnage * P) = 0;
	bool estEnVie() const;
	int force() const;
	int vitesse()const;
	int niveau() const;
	void ajouterForce(int montant);
	void ajouterVitesse(int montant);
	void ajouterVie(long long int montant);
	int xpDonner()const;
	int soins(double RatioMin, double RatioMax,int choix=0) const;
	Statistiques& stats();
	int degats(double RatioMin, double RatioMax,int choix=0) const;
	void soigner(int soins,Personnage * P, sf::RenderWindow* window);
	void AjouterVie(long long int montant, sf::RenderWindow* window);
	void bouclier(int soins, Personnage* P, sf::RenderWindow* window);
	void AjouterBouclier(int montant, sf::RenderWindow* window);
	void ajouterBouclier(int montant);
	int bouclierMax()const;
	bool estAttaquable() const;
	void setEnnemis(Equipes & E);
	void setAllier(Equipes & A);
	Equipes& equipeAllier();
	Equipes& equipeEnnemi();
	bool habile() const;
	void traitementAnimaux(sf::RenderWindow* window, std::vector< sf::Sound > &allSounds);
    void   Attaque(int Degat, Personnage * Defenseur, sf::RenderWindow* window, std::vector< sf::Sound > &allSounds) ;
	void AttaqueBrut(int Degat, Personnage* Defenseur, sf::RenderWindow* window);
	int degatsCritiques() const;
	void setReduction(int montant);
	void ajouterChanceDoubleAttaque(int montant);
	void ajouterChanceHabileter(int montant);
	void ajouterReduction(int montant);
	void ajouterDeviation(int montant);
	void ajouterChanceRicochet(int montant);
	void ajouterEsquive(int montant);
	bool possedeObjetNumero(int i)const;
	int bouclier() const;
	bool bloque() const;
	bool attaqueDouble() const;
	void ajouterMana(int n);
	int reductionDesDegats(int entier) const;
	bool devie() const;
	bool ricoche() const;
	void modifierIndiceEquipe(int i);
	int choixAttaque();
	int indiceEquipe() const;
	int chanceDoubleAttaque()const;
	int chanceHabileter()const;
	int pourcentageDeviation()const;
	int pourcentageReduction()const;
	int pourcentageRicochet()const;
	int pourcentageEsquive()const;
	int pourcentageBlocage()const;
	void setId(int val);
	void setAnimal(Animal A);
	Animal animal()const;
	int rareterAnimal()const;
	void ajouterCoupCritique(int pourcentage);
	void ajouterDegatsCritique(int pourcentage);
	void setNom(std::string nom);
	//void modifierStats(double ratio);
	Status & status();
	std::pair <Objet, Objet> objets();
	std::pair <Objet, Objet> objets2();
	void appliquerEffets();
	void setObjets(Objet un, Objet deux);
	void setObjets2(Objet un, Objet deux);
	bool possedeBouclier() const;
	void equiperObjet(Objet, bool premier);
	void equiperObjet2(Objet, bool premier);
	int getDerniereActionMontant()const;
	int getDerniereActionType()const;
	void setDerniereActionMontant(int montant);
	void setDerniereActionType(int TYPE);

private:
	int _id;
	int _niveau;
	long long int _vieMax;
	long long int _vie;
	int _force;
	int _vitesse;
	int _bouclier;
	int _mana;
	int _pourcentageCritique;
	int _degatCritique;
	int _chanceDoubleAttaque;
	int _chanceHabilete;
	int _pourcentageDeviation;
	int _pourcentageReduction;
	int _pourcentageRicochet;
	int _pourcentageEsquive;
	int _pourcentageBlocage;
	int _indiceEquipe;
	Equipes _A;
	Equipes _E;
	int _indiceAnimal;
	int _rareteAnimal;
	Animal _animal;
	std::string _nom;
	Statistiques _S;
	Status _statusPerso;
	std::pair<Objet, Objet> _objets;
	std::pair<Objet, Objet> _objets2;
	int _derniereActionMontant;
	int _derniereActionType;
	
};

