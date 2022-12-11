#pragma once
#include <string>
class Personnage;
class Objet
{
public:
	Objet();
	Objet(std::string nom, int numero, int rareter, std::string effet);
	std::string nom()const;
	std::string effet()const;
	int rareter()const;
	std::string rareterTexte();
	void appliquerEffet(Personnage* P);
	int numero()const;
private:
	std::string _nom;
	std::string _effet;
	int _rareter;
	int _numero;
};

