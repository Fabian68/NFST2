#include "Animal.h"
#include "Aleatoire.h"
Animal::Animal()
{
	Animal(0);
}

Animal::Animal(int numero)
{
	_indice = numero;
	_pourcentagesActivations.resize(5);
	_ratioMin.resize(5);
	_ratioMax.resize(5);
	switch (numero) {
	case -1:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 0;
			_ratioMin[i] =0;
			_ratioMax[i] =0;
			_type = " aucun animal ";
		}
	
		break;
	case 0:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 6 + 3 * i;
			_ratioMin[i] = 0.02 * i;
			_ratioMax[i] = 0.04 +0.04*i;
			_type = " soins de zone ";
		}
		_pourcentagesActivations[4] += 2;
		_ratioMin[4] += 0.02 ;
		_ratioMax[4] += 0.1;
		break;
	case 1:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 10 + 5 * i;
			_ratioMin[i] = 0.05 * pow(2,i)+0.01;
			_ratioMax[i] = 0.10 * pow(2,i);
			_type = " soigne le plus faible ";
		}
		break;
	case 2:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 3 + 8 * i;
			_ratioMin[i] = 0.10 +0.10*i;
			_ratioMax[i] = 0.15+0.20 * i;
			_type = " soigne un allier aleatoire ";
		}
		break;
	case 3:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 15 + 3 * i;
			_ratioMin[i] = 0.03 * i+0.2;
			_ratioMax[i] = 0.09 * i+0.3;
			_type = " attaque le plus faible ";
		}
		_pourcentagesActivations[4] += 6;
		_ratioMin[4] += 0.02;
		_ratioMax[4] += 0.2;
		break;
	case 4:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 2 + 5 * i;
			_ratioMin[i] = 0.01 * pow(2, i)+0.02;
			_ratioMax[i] = 0.01 * pow(2, i*1.0+1.0)+0.04;
			_type = " attaque de zone ";
		}
		break;
	case 5:
		_ratioMin[0] = 0.03;
		_ratioMax[0] = 0.045;
		_pourcentagesActivations[0] = 5;
		for (int i = 1; i < 5; i++) {
			_pourcentagesActivations[i] = _pourcentagesActivations[i-1]+5;
			_ratioMin[i] = _ratioMin[i-1]*3;
			_ratioMax[i] = _ratioMax[i-1]*3;
			_type = " attaque l'ennemi le plus fort ";
		}
		break;
	case 6:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 3 + 4 * i;
			_ratioMin[i] = 0.02 * i;
			_ratioMax[i] = 0.03 * (i*1.0+1.0);
			_type = " bouclier de zone ";
		}
		break;
	case 7:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 3 + 8 * i;
			_ratioMin[i] = 0.03 * pow(2, i);
			_ratioMax[i] = 0.06 * pow(2, i);
			_type = " bouclier le plus faible ";
		}
		break;
	case 8:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 1 + 10 * i;
			_ratioMin[i] = 0.05 * (i*1.0+1.0);
			_ratioMax[i] = 0.10+0.10 * (i*1.0+1.0);
			_type = " bouclier un allier aleatoire ";
		}
		break;
	case 9:
		for (int i = 0; i < 5; i++) {
			_pourcentagesActivations[i] = 1 + 11 * i;
			_ratioMin[i] = 0.03 * (i*1.0+1.0)+0.2;
			_ratioMax[i] = 0.06 * (i*1.0+1.0)+0.4;
			_type = " bouclier et soigne le plus faible ";
		}
		break;
	}
}

int Animal::pourcentageActivation(int rareter) const
{
	return _pourcentagesActivations[rareter - 1];
}

double Animal::ratioMin(int rareter) const
{
	return _ratioMin[rareter - 1];
}

double Animal::ratioMax(int rareter) const
{
	return _ratioMax[rareter - 1];
}
std::string Animal::type()const {
	return _type;
}

bool Animal::activer(int rareter) const
{
	return Aleatoire(0,101).entier()<_pourcentagesActivations[rareter-1];
}

int Animal::indice() const
{
	return _indice;
}
