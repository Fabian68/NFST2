#pragma once
#include <vector>
#include <string>

class Conseils
{
public:
	Conseils();
	std::string conseilAleatoire()const;
private:
	std::vector<std::string> _listeConseils;
};

