#pragma once
#include <fstream>
#include<iomanip>
#include <vector>
class Experiences
{
public:
	Experiences();
	bool ecrireEXP(const std::string & fichier);
	~Experiences();
	int calculNiveau(int indiceTabxp)const;

	void ajouterXP(int indiceTabxp, int montant);

private:
	std::vector<long long int> _tabXp;
	std::vector<long long int> _ExperiencesPersonnages;
};

