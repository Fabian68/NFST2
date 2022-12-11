#pragma once
#include <vector>
#include <string>
class Animal
{
public:
	Animal();
	Animal(int numero);
	int pourcentageActivation(int rareter)const;
	double ratioMin(int rareter)const;
	double ratioMax(int rareter)const;
	std::string type()const;
	bool activer(int rareter)const;
	int indice()const;
private:
	std::vector<int> _pourcentagesActivations;
	std::vector<double> _ratioMin;
	std::vector<double> _ratioMax;
	std::string _type;
	int _indice;

};

