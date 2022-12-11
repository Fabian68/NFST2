#pragma once

#include <cstdlib>
#include <ctime>
class Aleatoire
{
public:
	Aleatoire();
	Aleatoire(int a, int b);
	Aleatoire(double a, double b);
	int entier()const;
	double decimal()const;
	~Aleatoire();
private:
	int _entier;
	double  _decimal;
};


