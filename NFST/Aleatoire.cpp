#include "Aleatoire.h"



Aleatoire::Aleatoire() : _entier{rand() % (101 ) }
{
}

Aleatoire::Aleatoire(int a, int b) : _entier{ rand() % (b - a) + a }
{
}

Aleatoire::Aleatoire(double a, double b) : _decimal{ (rand() / (double)RAND_MAX)*(b - a) + a }
{
}

int Aleatoire::entier() const
{
	return _entier;
}

double Aleatoire::decimal() const
{
	return _decimal;
}

Aleatoire::~Aleatoire()
{
}

/*
int rand_a_b(int a,int b ){
	return rand()%(b-a)+a;
}

double frand_a_b(double a,double b){
	return (rand()/(double)RAND_MAX)*(b-a)+a;
}
bool tiragePersoCarac(int joueur,int carac) {
	int T= rand_a_b(0,101);
	return(T<=PersoCarac[joueur][carac]);
}
bool tiragePersoCaracBonus(int joueur,int carac,int bonus) {
	int T= rand_a_b(0,101);
	return(T<=PersoCarac[joueur][carac]+bonus);
}
*/
