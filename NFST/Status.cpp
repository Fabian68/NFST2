#include "Status.h"
#include "Aleatoire.h"
#include "Personnage.h"
#include <iostream>
Status::Status()
{
	_perso = nullptr;
	_status.resize(11, 0);
}

Status::Status(Personnage* P)
{
	_perso = P;
	_status.resize(11, 0);
}

bool Status::estBruler() const
{
	return _status[BRULURE]>0;
}

bool Status::estEmpoisoner() const
{
	return _status[EMPOISONNER] > 0;
}

bool Status::estFragiliser() const
{
	return _status[COMPTEURFRAGILISER] > 0;;
}

bool Status::estProteger() const
{
	return _status[COMPTEURPROTEGER] > 0;
}

bool Status::estEnMagasineur() const
{
	return _status[EMAGASINEUR]==1;
}

void Status::ajoutEnmagasination(int montant)
{
	_status[EMAGASINATION] += montant;
	if (_status[EMAGASINATION] < 0) {
		_status[EMAGASINATION] = 0;
	}
}

void Status::retirerEmagasination(int montant)
{
	ajoutEnmagasination(-montant);
}

int Status::enmagasination() const
{
	return _status[EMAGASINATION];
}

void Status::devientEnmagasineur()
{
	_status[EMAGASINEUR] = 1;
}

void Status::appliquerBrulure()
{
	if (_status[BRULURE] < 1) {
		_status[BRULURE] = 1;
	}
}

void Status::appliquerPoison()
{
	if (_status[EMPOISONNER] < 1) {
		_status[EMPOISONNER] = 1;
	}
}

void Status::ajouterCompteurFragile(int nb)
{
	_status[COMPTEURFRAGILISER] +=nb ;
}

void Status::ajouterCompteurProteger(int nb)
{
	_status[COMPTEURPROTEGER] += nb;
}

void Status::decrementerCompteur()
{
	if (estFragiliser()) {
		_status[COMPTEURFRAGILISER]--;
	}
	if (estProteger()) {
		_status[COMPTEURPROTEGER]--;
	}


}

void Status::effetBrulure()
{
	if (estBruler()) {
		double i = _status[BRULURE] * 1.0;
		double pourcentage = Aleatoire(i, i * 2).decimal();
		pourcentage /= 100;
		int DEGATS = static_cast<int>(pourcentage * _perso->vieMax());
		std::cout << _perso->nom() << " reçois " << DEGATS << " degats de brulure" << std::endl;
		_perso->reduireVie(DEGATS);

		_status[BRULURE] = (_status[BRULURE] + 1) % 11;
	}
}

void Status::soignerBrulure() {
	_status[BRULURE] = 0;
}

void Status::soignerPoison() {
	_status[EMPOISONNER] = 0;
}

void Status::effetPoison()
{
	if (estEmpoisoner()) {
		double i = _status[EMPOISONNER] * 1.0;
		double pourcentage = Aleatoire(pow(2, i) / 2, pow(2, i)).decimal();
		pourcentage /= 100000;
		int supplement = static_cast<int>(0.10 * (_perso->vieMax()*1.0 - _perso->vie()*1.0));
		int DEGATS = supplement + static_cast<int>(pourcentage * _perso->vieMax());
		std::cout << _perso->nom() << " reçois " << DEGATS << " degats de poison" << std::endl;
		_perso->reduireVie(DEGATS);

		_status[EMPOISONNER] = _status[EMPOISONNER] + 1;
	}
}

void Status::setAdducteur(int montant)
{
	_status[ADDUCTEUR] = montant;
}

void Status::setReducteur(int montant)
{
	_status[REDUCTEUR] = montant;
}

void Status::setAdducteurBrut(int montant)
{
	_status[ADDUCTEURBRUT] = montant;
}

int Status::adducteur() const
{
	return _status[ADDUCTEUR];
}

int Status::reducteur() const
{
	return  _status[REDUCTEUR];
}

int Status::adducteurbrut() const
{
	return  _status[ADDUCTEURBRUT];
}

void Status::revivre()
{
	_status[COMPTEURRESURECTIONS]--;
}

bool Status::peutRevivre()
{
	return _status[COMPTEURRESURECTIONS]>0;
}

void Status::ajouterCompteurRessurections()
{
	_status[COMPTEURRESURECTIONS]++;
}

void Status::contamination()
{
	_status[STADEZOMBIE]=1;
}

void Status::decontamination()
{
	_status[STADEZOMBIE] = 0;
}

bool Status::estContaminer() const
{
	return _status[STADEZOMBIE] == 1;
}
