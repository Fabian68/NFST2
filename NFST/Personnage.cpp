#include "Personnage.h"
#include "Aleatoire.h"
#include "Affichage.h"
#include "AffichageCombat.h"
#include <iostream>
#include <limits> 

Personnage::Personnage(int LVL, std::string nom, int vieLVL, int forceLVL, int vitesseLVL, int chanceDoubleAttaque, int chanceHabilete, int pourcentageReduction, int pourcentageDeviation, int pourcentageBlocage, int pourcentageEsquive, int pourcentageRicochet, int indiceAnimal, int rareteAnimal) :
	_vieMax{ (long long int)vieLVL * LVL * 10 }, _vie{ (long long int)vieLVL * LVL * 10 }, _nom{ nom }, _id{ -1 }, _niveau{ LVL }, _force{ forceLVL * LVL }, _vitesse{ vitesseLVL * LVL }, _chanceDoubleAttaque{ chanceDoubleAttaque },
	_chanceHabilete{ chanceHabilete }, _pourcentageReduction{ pourcentageReduction }, _pourcentageDeviation{ pourcentageDeviation }, _pourcentageBlocage{ pourcentageBlocage }, _pourcentageEsquive{ pourcentageEsquive }, _pourcentageRicochet{ pourcentageRicochet },
	_mana{ 0 }, _pourcentageCritique{ 5 }, _degatCritique{ 50 }, _bouclier{ 0 }, _indiceAnimal{ indiceAnimal }, _rareteAnimal{ rareteAnimal }
{
	_statusPerso = Status(this);
	_animal = Animal(_indiceAnimal);
	_objets.first = Objet();
	_objets.second = Objet();
	_objets2.first = Objet();
	_objets2.second = Objet();
	_derniereActionType = actionNULL;
	_derniereActionMontant = 0;
}

Personnage::Personnage(int id,Experiences E,Orbes O,Animaux A, Objets Obj, std::string nom, int vieLVL, int forceLVL, int vitesseLVL, int chanceDoubleAttaque, int chanceHabilete, int pourcentageReduction, int pourcentageDeviation, int pourcentageBlocage, int pourcentageEsquive, int pourcentageRicochet) :
	_nom{ nom }, _id{ id }, _chanceDoubleAttaque{ chanceDoubleAttaque },
	_chanceHabilete{ chanceHabilete }, _pourcentageReduction{ pourcentageReduction }, _pourcentageDeviation{ pourcentageDeviation }, _pourcentageBlocage{ pourcentageBlocage }, _pourcentageEsquive{ pourcentageEsquive }, _pourcentageRicochet{ pourcentageRicochet },
	_mana{ 0 }, _pourcentageCritique{ 5 }, _degatCritique{ 50 }, _bouclier{ 0 }
{
	int bonusLVLattaque;
	int bonusLVLvie;
	int bonusLVLvitesse;
	O.buffOrbes(_id, bonusLVLattaque, bonusLVLvie, bonusLVLvitesse);
	_niveau = E.calculNiveau(id);
	_vie = ((long long int)vieLVL + bonusLVLvie) * _niveau * 10;
	_vieMax = _vie;
	_force = (forceLVL + bonusLVLattaque) * _niveau;
	_vitesse = (vitesseLVL + bonusLVLvitesse) * _niveau;
	_indiceAnimal = A.indiceAnimal(_id);
	_rareteAnimal = A.rareteAnimal(_id, _indiceAnimal);
	//A.animalDuPersonnage(_id, _indiceAnimal, _rareteAnimal);
	//std::cout << _indiceAnimal << " " << _rareteAnimal;
	_animal = Animal(_indiceAnimal);
	_statusPerso = Status(this);
	Obj.objetsDuPersonnage(_id, _objets.first, _objets.second);
	Obj.objetsDuPersonnage2(_id, _objets2.first, _objets2.second);
	appliquerEffets();
	_derniereActionType = actionNULL;
	_derniereActionMontant = 0;
}

Personnage::~Personnage()
{
	

}

int Personnage::id()const 
{
	return _id;
}
int Personnage::mana() const
{
	return _mana;
}
std::string Personnage::nom()const
{
	return _nom;
}

long long int Personnage::vie() const
{
	return _vie;
}

long long int Personnage::vieMax() const
{
	return _vieMax;
}
void Personnage::ajouterVieMax(long long int montant) {
	_vieMax += montant;
	if (_vieMax > 999999999999) {
		_vieMax = 999999999999;
	}
	setDerniereActionMontant(montant);
	setDerniereActionType(actionSOINS);
	_S.ajouterAugmentationVieMax(montant);
}

void Personnage::reduireVieMax(long long int montant) {
	ajouterVieMax(-montant);
	if (_vie > _vieMax) {
		_vie = _vieMax;
	}
}
void Personnage::reduireVie(long long int nb)
{
	if (_vie < nb) {
		_S.ajouterDegatsRecu(_vie);
		setDerniereActionMontant(_vie);
		setDerniereActionType(actionDEGATS);
		_vie = 0;
	}
	else {
		_vie -= nb;
		_S.ajouterDegatsRecu(nb);
		setDerniereActionMontant(nb);
		setDerniereActionType(actionDEGATS);
	}
}

int Personnage::reduireBouclier(int nb)
{
	int ecart;
	if (nb > _bouclier) {
		ecart = nb - _bouclier;
		_bouclier = 0;
		_S.ajouterDegatsRecu(ecart);
		setDerniereActionMontant(ecart);
		setDerniereActionType(actionDEGATS);
	}
	else {
		ecart = 0;
		_bouclier = _bouclier - nb;
		_S.ajouterDegatsRecu(nb);
		setDerniereActionMontant(nb);
		setDerniereActionType(actionDEGATS);
	}
	return ecart;
}

int Personnage::pourcentageVie() const
{
	return ceil((static_cast<double>(_vie)/ static_cast<double>(_vieMax))*100);
}

int Personnage::pourcentageBouclier() const
{
	return ceil((static_cast<double>(_bouclier) / static_cast<double>(bouclierMax()) * 100));
}

bool Personnage::estEnVie()const {
	return _vie > 0;
}

int Personnage::force()const {
	return _force;
}

int Personnage::vitesse() const
{
	return _vitesse;
}

int Personnage::niveau()const {
	return _niveau;
}
void Personnage::ajouterForce(int montant)
{
	_force += montant;
	_S.ajouterAugmentationForce(montant);
}
void Personnage::ajouterVitesse(int montant)
{
	_vitesse += montant;
}
void Personnage::ajouterVie(long long int montant)
{
	_vie += montant;
	if (_vie > 999999999999) {
		_vie = 999999999999;
	}
	_vieMax = _vie;
}

int Personnage::xpDonner() const
{
	double xp;
	double multiplicateur = 1.0;
	xp = _force / 10.0 + _vitesse / 10.0 + _vieMax / 100.0;
	multiplicateur += _chanceDoubleAttaque / 100.0 + _chanceHabilete / 100.0 + _pourcentageRicochet / 100.0 + _pourcentageReduction / 90.0 + _pourcentageEsquive / 90.0 + _pourcentageDeviation / 80.0 + _pourcentageBlocage / 100.0;
	return round(xp * multiplicateur);
}
int Personnage::soins(double RatioMin,double RatioMax, int choixStats) const {
	int montant=0;
	switch (choixStats) {
	case CHOIXFORCE:
		montant = _force;
		break;
	case CHOIXVIEMAX:
		montant = _vieMax;
		break;
	case CHOIXVITESSE:
		montant = _vitesse;
		break;
	case CHOIXVIE:
		montant = _vie;
		break;
	case CHOIXBOUCLIER:
		montant = _bouclier;
		break;
	}
	double SOINS = Aleatoire(RatioMin,RatioMax).decimal()*montant;
	return (int)(SOINS);

}

Statistiques& Personnage::stats() {
	return _S;
}
int Personnage::degats(double RatioMin, double RatioMax,int choixStats) const
{
	int montant=0;
	switch (choixStats) {
	case CHOIXFORCE:
		montant = _force;
		break;
	case CHOIXVIEMAX:
		montant = _vieMax;
		break;
	case CHOIXVITESSE:
		montant = _vitesse;
		break;
	case CHOIXVIE:
		montant = _vie;
		break;
	case CHOIXBOUCLIER:
		montant = _bouclier;
		break;
	}
	double degat = Aleatoire(RatioMin, RatioMax).decimal()*(montant*1.0);
	
	return (int)(degat);
}

void Personnage::soigner(int soins,Personnage * P, sf::RenderWindow* window)
{	if (P->estEnVie()) {
		if (soins < 0) {
			soins = 0;
		}
		if (Aleatoire().entier() <= _pourcentageCritique) {
			soins *= (_degatCritique / 100.0 + 1);
		}
		if (Aleatoire().entier() <= _chanceHabilete) {
			if (possedeObjetNumero(6)) {
				if (Aleatoire(0, 101).entier() < 5) {
					soins *= 4;
				}
				else if (Aleatoire(0, 101).entier() < 10) {
					soins *= 3;
				}
				else {
					soins *= 2;
				}
				//std::cout << " OBJ6 ";
			}
			else {
				soins *= 2;
			}

		}
		if ((soins + P->vie()) > P->vieMax()) {
			soins =(int)( P->vieMax() - P->vie());
			
		}
		P->stats().ajouterSoinsDonner(soins);
		P->AjouterVie(soins,window);
		if (possedeObjetNumero(4)) {
			if (Aleatoire(0, 101).entier() < 20) {
				P->bouclier(soins, P,window);
			}
			//std::cout << " OBJ4 ";
		}
	}
}

void Personnage::AjouterVie(long long int montant, sf::RenderWindow* window) {
	if (montant <= 0) {
		montant = 0;
	}
	else {
		_vie += montant;
		AffichageCombat H;
		setDerniereActionMontant(montant);
		setDerniereActionType(actionSOINS);
		//H.dessinerSoins(this, montant,window);
	
		if (_vie > _vieMax) {
			_vie = _vieMax;	
		}
	
		if (this->equipeAllier().ia() == false) {
			H.dessinerDeuxEquipes(this->equipeAllier(), this->equipeEnnemi(), window);
		}
		else {
			H.dessinerDeuxEquipes(this->equipeEnnemi(), this->equipeAllier(), window);
		}
		
		//H.dessinerJoueur(this->indiceEquipe() + 1, this->equipeAllier().ia(), this,window);
	}
}

void Personnage::bouclier(int soins, Personnage* P, sf::RenderWindow* window)
{
	if (P->estEnVie()) {
		if (Aleatoire().entier() <= _pourcentageCritique) {
			soins *= (_degatCritique / 100.0 + 1);
		}
		if (Aleatoire().entier() <= _chanceHabilete) {
			if (possedeObjetNumero(6)) {
				if (Aleatoire(0, 101).entier() < 5) {
					soins *= 4;
				}
				else if (Aleatoire(0, 101).entier() < 10) {
					soins *= 3;
				}
				else {
					soins *= 2;
				}
				//std::cout << " OBJ6 ";
			}
			else {
				soins *= 2;
			}

		}
		if ((soins + P->bouclier()) >P->bouclierMax()) {
			soins = P->bouclierMax() - P->bouclier();

		}
		P->stats().ajouterBouclierDonner(soins);
		P->AjouterBouclier(soins,window);
		if (possedeObjetNumero(4)) {
			if (Aleatoire(0, 101).entier() < 10) {
				P->status().ajouterCompteurProteger(1);
			}
			//std::cout << " OBJ4 ";
		}
	}
}

void Personnage::AjouterBouclier(int montant, sf::RenderWindow* window) {
	if (montant <= 0) {
		montant = 0;
	}
	else {
		_bouclier += montant;
		AffichageCombat H;
		setDerniereActionMontant(montant);
		setDerniereActionType(actionBOUCLIER);
		//H.dessinerBouclier(this,montant,window);
		if (_bouclier > bouclierMax()) {
			_bouclier = bouclierMax();
		
		}
		
		if (this->equipeAllier().ia() == false) {
			H.dessinerDeuxEquipes(this->equipeAllier(), this->equipeEnnemi(), window);
		}
		else {
			H.dessinerDeuxEquipes(this->equipeEnnemi(), this->equipeAllier(), window);
		}
		//H.dessinerJoueur(this->indiceEquipe() + 1, this->equipeAllier().ia(), this,window);
	}
	
}

void Personnage::ajouterBouclier(int montant) {
	_bouclier += montant;
}
int Personnage::bouclierMax()const {
	int max = (_force * 10 + (int)_vieMax)/4;
	if (max > 2000000000) {
		max = 2000000000;
	}
	else if (max < 0) {
		max = 2000000000;
	}
	return max;
}
bool Personnage::estAttaquable()const {
	return (estEnVie() && _pourcentageEsquive < Aleatoire().entier());
}

void Personnage::setEnnemis(Equipes & E)
{
	_E = E;
}

void Personnage::setAllier(Equipes & A)
{
	_A = A;
}

Equipes & Personnage::equipeAllier() 
{
	return _A;
}

Equipes & Personnage::equipeEnnemi() 
{
	return _E;
}

bool Personnage::habile()const {
	return Aleatoire(0, 101).entier() <= _chanceHabilete;
}
void Personnage::traitementAnimaux(sf::RenderWindow* window) {
	if (_animal.indice() < 0) {

	}
	else if (_animal.activer(_rareteAnimal)) {
		int Soins = soins(_animal.ratioMin(_rareteAnimal), _animal.ratioMax(_rareteAnimal));
		int Degats = degats(_animal.ratioMin(_rareteAnimal), _animal.ratioMax(_rareteAnimal));
		//std::cout << _nom+_animal.type()+"animal" << std::endl;
		switch (_indiceAnimal) {
		case 0:
				_A.soignerZone(Soins, this,window);
			break;
		case 1:
				soigner(Soins, _A.plusFaible(),window);	
			break;
		case 2:
				soigner(Soins, _A.aleatoireEnVie(),window);
			break;
		case 3:
				Attaque(Degats, _E.plusFaible(),window);
			break;
		case 4:
				_E.attaqueZone(Degats, this,window);
			break;
		case 5:
				Attaque(Degats, _E.aleatoireEnVie(),window);
			break;
		case 6:
				_A.bouclierZone(Soins, this,window);
			break;
		case 7:
				bouclier(Soins, _A.plusFaible(),window);
			break;
		case 8:
				bouclier(Soins, _A.aleatoireEnVie(),window);
			break;
		case 9:
				_A.soignerZone(Soins, this,window);
				_A.bouclierZone(Soins, this,window);
			break;
		}
	}
}
void  Personnage::Attaque(int Degat, Personnage * Defenseur, sf::RenderWindow* window)
{

	bool redirection = false;
	Degat++;
	std::string FRAGILISER = "";
	std::string PROTEGER = "";
	int degatEffectif;
	if (Defenseur->estAttaquable()) {

		if (Defenseur->possedeObjetNumero(42)) {
			Degat -= Defenseur->vieMax() / 100;
		}
		if (!this->estEnVie() && possedeObjetNumero(46)) {
			Degat *= 3;
		}
		if (possedeObjetNumero(48)) {
			if (bouclier() >= 1) {
				Degat = (int)(Degat * (1.0 + (bouclier() * 1.0) / (bouclierMax() * 1.0)));
			}
		}
		if (Aleatoire().entier() <= _pourcentageCritique) {
			Degat *= (_degatCritique / 100.0 + 1);
		}
		if (Aleatoire().entier() <= _chanceHabilete) {
			if (possedeObjetNumero(6)) {
				if (Aleatoire(0, 101).entier() < 5) {
					Degat *= 4;
				}
				else if (Aleatoire(0, 101).entier() < 10) {
					Degat *= 3;
				}
				else {
					Degat *= 2;
				}
				//std::cout << " OBJ6 ";
			}
			else {
				Degat *= 2;
			}

		}
		if (possedeObjetNumero(29)) {
			Degat += stats().nbAttaques()*(1+_niveau/100);
			//std::cout << " OBJ29 ";
		}
		if (possedeObjetNumero(35)) {
			Degat += Degat/2;
			//std::cout << " OBJ35 ";
		}
		if (Defenseur->possedeObjetNumero(35) ) {
			Degat *= 2;
		}

		if (possedeObjetNumero(37)) {
			if (indiceEquipe() == Defenseur->indiceEquipe()) {
				Degat += Degat / 2;
			}
		}

		if (possedeObjetNumero(38)) {
			if (Defenseur->possedeBouclier()) {
				if (Defenseur->bouclier() == Defenseur->bouclierMax()) {
					Degat *= 2;
				}
				else {
					Degat += Degat / 2;
				}
			}
		}
		if (possedeObjetNumero(39)) {
			double ratio = 1.0-((vie() * 1.0) / (vieMax() * 1.0));
			Degat += (int)((Degat * 1.0) * ratio);
		}
		if (Defenseur->possedeObjetNumero(37)) {
			if (indiceEquipe() == Defenseur->indiceEquipe()) {
				Degat /=2;
			}
		}
		if (Defenseur->possedeObjetNumero(36)) {
			if (Defenseur->vie() > Defenseur->vieMax() / 2) {
				Degat *= 2;
			}
			else {
				Degat /= 2;
			}
		}
		
		if (possedeObjetNumero(5)) {
			Degat = (int)((double)Degat*2.5);
			//std::cout << " OBJ5 ";
		}
		if (possedeObjetNumero(16)) {
			Degat = (int)((double)Degat * 1.2);
			//std::cout << " OBJ16 ";
		}
		if (possedeObjetNumero(12) && _S.nbAttaques()%3==0) {
			Degat = (int)((double)Degat * 1.3);
			//std::cout << " OBJ12 ";
		}
		if (Defenseur->bloque()&&!possedeObjetNumero(43)) {
			Degat /= 2;
		}
		if (Defenseur->status().estProteger()) {
			Degat /= 2;
			PROTEGER = "PROTEGER";
		}
		if (Defenseur->status().estFragiliser()) {
			Degat *= 2;
			FRAGILISER = "FRAGILISER";
		}

		if (possedeObjetNumero(41)) {
			Degat += Defenseur->vie() / 100;
		}
		
		Defenseur->status().decrementerCompteur();

		if (Defenseur->status().estEnMagasineur()) {
			Defenseur->status().ajoutEnmagasination(Degat/10);
		}
		Degat -= Defenseur->status().reducteur();
		Degat += status().adducteur();
		if (!possedeObjetNumero(43)) {
			Degat = Defenseur->reductionDesDegats(Degat);
		}
		
		if (Degat < 0) {
			Degat = 0;
		}
		if (Defenseur->devie()) {
			if (Defenseur->possedeObjetNumero(9)) {
				Degat = (int)((double)Degat * 1.5);
				std::cout << " OBJ9 ";
			}
			Defenseur->Attaque(Degat, this,window);
			
		}
		else if (Defenseur->possedeObjetNumero(10) && Aleatoire(0, 101).entier() < 10) {
			Defenseur->AjouterBouclier(Degat / 10,window);
		}
		else {

			for (int i = 0;i < Defenseur->equipeAllier().taille()&&!redirection;i++) {
				if (Defenseur->equipeAllier()[i]->possedeObjetNumero(11) && Aleatoire(0, 101).entier() < 25) {
					redirection = true;
					Attaque(Degat, Defenseur->equipeAllier()[i],window);
					//std::cout << " OBJ11 ";
				}
			}
			if (!redirection) {
				Defenseur->passifDefensif(window);
				Defenseur->traitementAnimaux(window);
				this->traitementAnimaux(window);
				
				

			//	std::cout << _nom<<indiceEquipe() << " attaque " << Defenseur->indiceEquipe() << Defenseur->nom() << " " << FRAGILISER << " " << PROTEGER;
				//std::cout << " " << Degat << std::endl;
				if (Defenseur->possedeObjetNumero(25)) {
					Degat -= Defenseur->niveau();
					//std::cout << " OBJ25 ";
				}
				if (possedeObjetNumero(28)) {
					Degat -= Defenseur->stats().nbAttaquesRecues() * (1 + Defenseur->niveau() / 100);
					//std::cout << " OBJ28 ";
				}
				if (Degat < 0) {
					Degat = 1;
				}
				if (Defenseur->possedeObjetNumero(14) && _A.estEnVie()) {
					Defenseur->AttaqueBrut(Degat / 10, _A.plusProcheVivant(),window);
					//std::cout << " OBJ14 ";
				}	
				if (possedeObjetNumero(24)) {
					if (Aleatoire(0, 5000).entier() == 1) {
						Defenseur->status().appliquerPoison();
					}
				}
				//fin modif dégats
				degatEffectif = Degat;
				_S.incrementerNbAttaques();
				Defenseur->stats().incrementerNbAttaquesRecues();
				_S.ajouterDegatsProvoquer(Degat);
				if (Degat > _S.plusGrosseAttaqueEnvoyer()) {
					_S.changerPlusGrosseAttaqueEnvoyer(Degat) ;
				}
				if (Degat > Defenseur->stats().plusGrosseAttaqueRecue()) {
					Defenseur->stats().changerPlusGrosseAttaqueRecue(Degat);
				}

				if (Defenseur->bouclier() > 0) {
					Degat = Defenseur->reduireBouclier(Degat);
				}
			
				if (Degat > 0) {
					if (Degat > Defenseur->vie()) {
						Degat = (int)Defenseur->vie();
					}
					
					Defenseur->reduireVie(Degat);		
				}
				if (Defenseur->estEnVie()) {
					if (status().adducteurbrut() > 0) {
						AttaqueBrut(status().adducteurbrut(), Defenseur,window);
					}
				}
				if (!Defenseur->estEnVie()&&Defenseur->possedeObjetNumero(30)) {
					if (Defenseur->status().peutRevivre()) {
						Defenseur->status().revivre();
						Defenseur->AjouterVie(Defenseur->vieMax(),window);
					}
				}
				AffichageCombat H;
				
				H.dessinerAttaque(this, Defenseur,window);
				//H.dessinerJoueur(Defenseur->indiceEquipe() + 1, Defenseur->equipeAllier().ia(), Defenseur,window);
				//H.dessinerDegats(Defenseur, degatEffectif,window);
				Defenseur->setDerniereActionMontant(degatEffectif);
				Defenseur->setDerniereActionType(actionDEGATS);
				if (this->equipeAllier().ia() == false) {
					H.dessinerDeuxEquipes(this->equipeAllier(), this->equipeEnnemi(), window);
				}
				else {
					H.dessinerDeuxEquipes(this->equipeEnnemi(), this->equipeAllier(), window);
				}
			}
		}
		if (ricoche()&&_E.estEnVie()&&!redirection) {
			if (possedeObjetNumero(27)) {
				Degat = (int)((double)Degat*1.3);
			}
			Attaque(Degat, _E.aleatoireEnVie(),window);
			if (possedeObjetNumero(40)) {
				Attaque(Degat, _E.aleatoireEnVie(),window);
			}
		}
	}
	else{
		if (Defenseur->possedeObjetNumero(15)) {
			Defenseur->ajouterDegatsCritique(5);
			//std::cout << " OBJ15 ";
		}
		if (Defenseur->possedeObjetNumero(16)) {
			Defenseur->AttaqueBrut(degats(0.2,0.4),_A.plusFaible(),window);
			//std::cout << " OBJ16 ";
		}
	}
	if (possedeObjetNumero(13) && _E.estEnVie()) {
		Degat = degats(0.05, 0.10);
		AttaqueBrut(Degat, _E.plusFaible(),window);
		//std::cout << " OBJ13 ";
	}
	if (possedeObjetNumero(31) && _A.estEnVie()) {
		Degat = degats(1.0, 10.0);
		if (Aleatoire(0, 1001).entier() == 1) {
			Degat = degats(1.0, 10.0);
			Attaque(Degat, _E.plusProcheVivant(),window);
		}
		if (Aleatoire(0, 101).entier() == 1 &&_E.estEnVie()) {
			Degat = degats(0.1, 1.0);
			Attaque(Degat, _E.plusProcheVivant(),window);
		}
		if (Aleatoire(0, 11).entier() == 1 && _E.estEnVie()) {
			Degat = degats(0.01, 0.10);
			Attaque(Degat, _E.plusProcheVivant(),window);
		}
	//	std::cout << " OBJ31 ";
	}
	
}

void  Personnage::AttaqueBrut(int Degat, Personnage* Defenseur, sf::RenderWindow* window)
{
	if (Defenseur->estAttaquable()) {
		//	std::cout << _nom << " attaqueBrut " << Defenseur->indiceEquipe() << Defenseur->nom();
		//	std::cout << " " << Degat << std::endl;
		
			if (Degat > 0) {
				if (Aleatoire().entier() <= _pourcentageCritique) {
					Degat *= (_degatCritique / 100.0 + 1);
				}
				if (Aleatoire().entier() <= _chanceHabilete) {
					if (possedeObjetNumero(6)) {
						if (Aleatoire(0, 101).entier() < 5) {
							Degat *= 4;
						}
						else if (Aleatoire(0, 101).entier() < 10) {
							Degat *= 3;
						}
						else {
							Degat *= 2;
						}
						//std::cout << " OBJ6 ";
					}
					else {
						Degat *= 2;
					}

				}
				if (Degat > Defenseur->vie()) {
					Degat = (int)Defenseur->vie();
				}
				if (Degat > _S.plusGrosseAttaqueEnvoyer()) {
					_S.changerPlusGrosseAttaqueEnvoyer(Degat);
				}
				if (Degat > Defenseur->stats().plusGrosseAttaqueRecue()) {
					Defenseur->stats().changerPlusGrosseAttaqueRecue(Degat);
				}
				_S.ajouterDegatsProvoquer(Degat);
				_S.incrementerNbAttaques();
				Defenseur->stats().incrementerNbAttaquesRecues();
				Defenseur->reduireVie(Degat);
			}
			if (!Defenseur->estEnVie() && Defenseur->possedeObjetNumero(30)) {
				if (Defenseur->status().peutRevivre()) {
					Defenseur->status().revivre();
					Defenseur->AjouterVie(Defenseur->vieMax(),window);
				}
			}
			AffichageCombat H;
			H.dessinerAttaque(this, Defenseur,window);
			//H.dessinerJoueur(Defenseur->indiceEquipe() + 1, Defenseur->equipeAllier().ia(), Defenseur,window);
			//H.dessinerDegats(Defenseur, Degat,window);

			Defenseur->setDerniereActionMontant(Degat);
			Defenseur->setDerniereActionType(actionDEGATS);
			if (this->equipeAllier().ia() == false) {
				H.dessinerDeuxEquipes(this->equipeAllier(), this->equipeEnnemi(), window);
			}
			else {
				H.dessinerDeuxEquipes(this->equipeEnnemi(), this->equipeAllier(), window);
			}
	}

}

int Personnage::degatsCritiques()const {
	return _degatCritique;
}
void Personnage::setReduction(int montant) {
	_pourcentageReduction = montant;
}
void Personnage::ajouterChanceDoubleAttaque(int montant) {
	_chanceDoubleAttaque += montant;
	_S.ajouterAugmentationChanceDoubleAttaque(montant);
}
void Personnage::ajouterChanceHabileter(int montant) {
	_chanceHabilete += montant;
	_S.ajouterAugmentationChanceHabileter(montant);
}
void Personnage::ajouterReduction(int montant) {
	_pourcentageReduction += montant;
	_S.ajouterAugmentationReduction(montant);
	if (_pourcentageReduction >= 97) {
		_pourcentageReduction = 97;
	}
}

void Personnage::ajouterDeviation(int montant) {
	_pourcentageDeviation += montant;
}

void Personnage::ajouterChanceRicochet(int montant) {
	_pourcentageRicochet += montant;
	if (_pourcentageRicochet >= 90) {
		_pourcentageRicochet = 90;
	}
}

void Personnage::ajouterEsquive(int montant) {
	_pourcentageEsquive += montant;
	if (_pourcentageEsquive >= 95) {
		_pourcentageEsquive = 95;
	}
}
bool Personnage::possedeObjetNumero(int i)const {
	return (_objets.first.numero() == i || _objets.second.numero()==i || _objets2.first.numero() == i || _objets2.second.numero() == i);

}
int Personnage::bouclier()const {
	return _bouclier;
}
bool Personnage::bloque()const {
	return Aleatoire().entier() <= _pourcentageBlocage;
}

bool Personnage::attaqueDouble()const {
	return Aleatoire().entier() <= _chanceDoubleAttaque;
}

void Personnage::ajouterMana(int n) {
	_mana+=n;
}
int Personnage::reductionDesDegats(int entier)const {
	return static_cast<int>(entier*(1 - _pourcentageReduction / 100.0));
}

bool Personnage::devie()const {
	return Aleatoire().entier() <= _pourcentageDeviation;
}

bool Personnage::ricoche()const {
	return Aleatoire().entier() <= _pourcentageRicochet;
}

void Personnage::modifierIndiceEquipe(int i) {
	_indiceEquipe = i;
}

int Personnage::choixAttaque()
{
	return Aleatoire(0, (_mana % 4 + 1)).entier();
}

int Personnage::indiceEquipe()const {
	return _indiceEquipe;
}

int Personnage::chanceDoubleAttaque() const
{
	return _chanceDoubleAttaque;
}

int Personnage::chanceHabileter() const
{
	return _chanceHabilete;
}

int Personnage::pourcentageDeviation() const
{
	return _pourcentageDeviation;
}

int Personnage::pourcentageReduction() const
{
	return _pourcentageReduction;
}

int Personnage::pourcentageRicochet() const
{
	return _pourcentageRicochet;
}

int Personnage::pourcentageEsquive() const
{
	return _pourcentageEsquive;
}

int Personnage::pourcentageBlocage() const
{
	return _pourcentageBlocage;
}

void Personnage::setId(int val)
{
	_id = val;
}

void Personnage::setAnimal(Animal A)
{
	_animal = A;
}

Animal Personnage::animal() const
{
	return _animal;
}

int Personnage::rareterAnimal() const
{
	return _rareteAnimal;
}

void Personnage::ajouterCoupCritique(int pourcentage)
{
	_S.ajouterAugmentationCoupCritiques(pourcentage);
	_pourcentageCritique += pourcentage;
	if (_pourcentageCritique > 100) {
		_pourcentageCritique = 100;
	}
}

void Personnage::ajouterDegatsCritique(int pourcentage)
{
	_S.ajouterAugmentationDegatsCritique(pourcentage);
	_degatCritique += pourcentage;
}

void Personnage::setNom(std::string nom)
{
	_nom = nom;
}
/*
void Personnage::modifierStats(double ratio)
{
	std::cout << "ratio " << ratio <<" "<< std::endl;
	if (ratio > -1.9) {
		_force = round(_force * (1.0 + ratio/2.0));
		_vieMax = round(_vie * (1.0 + ratio/2.0));
		_vie = _vieMax;
		_vitesse = round(_vitesse * (1.0+ratio/2));
	}
	else {
		_force = 1;
		_vie = 1;
		_vieMax = 1;
		_vitesse = 1;
	}
}*/

Status& Personnage::status()
{
	return _statusPerso;
}

std::pair<Objet, Objet> Personnage::objets()
{
	return _objets;
}

std::pair<Objet, Objet> Personnage::objets2()
{
	return _objets2;
}

void Personnage::equiperObjet(Objet obj, bool premier) {
	if (premier == true) {
		_objets.first = obj;
	}
	else {
		_objets.second = obj;
	}
}

void Personnage::equiperObjet2(Objet obj, bool premier) {
	if (premier == true) {
		_objets2.first = obj;
	}
	else {
		_objets2.second = obj;
	}
}

int Personnage::getDerniereActionMontant() const
{
	return _derniereActionMontant;
}

int Personnage::getDerniereActionType() const
{
	return _derniereActionType;
}

void Personnage::setDerniereActionMontant(int montant)
{
	_derniereActionMontant = montant;
}

void Personnage::setDerniereActionType(int TYPE)
{
	_derniereActionType = TYPE;
}

void Personnage::appliquerEffets() {
	_objets.first.appliquerEffet(this);
	_objets.second.appliquerEffet(this);
	_objets2.first.appliquerEffet(this);
	_objets2.second.appliquerEffet(this);
}

void Personnage::setObjets(Objet un,Objet deux) {
	_objets.first = un;
	_objets.second = deux;
}

void Personnage::setObjets2(Objet un, Objet deux) {
	_objets2.first = un;
	_objets2.second = deux;
}

bool Personnage::possedeBouclier() const {
	return _bouclier > 0;
}