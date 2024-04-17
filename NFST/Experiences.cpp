#include "Experiences.h"
#include <string>


Experiences::Experiences()
{
	//0char* T1 = ;
	FILE *file = fopen("T1.txt", "r");
	if (file == NULL) {
		
		std::ofstream os("T1.txt", std::ios::binary);
		long long int v = 1;
		for (int i = 0;i < 50;i++) {
			os.write((char*)&v, sizeof(v));
			//os << std::endl;
		}
		os.close();
	}
	else {
		fclose(file);
	}
	std::ifstream is("T1.txt", std::ios::binary);

	int i = 0;
	long long int val;
	// lecture tantque possible
	while (!is.eof())
	{
		_ExperiencesPersonnages.resize(51);
		is.read((char*)&val, sizeof(val));
		_ExperiencesPersonnages[i] = val;
		i++;
	}
	is.close();

	std::ofstream os("Exp.txt", std::ios::binary);
	long long int UnEntierTresTresLong;
	_tabXp.resize(10000);
	for (int i = 0;i < 10000;i++) {


		UnEntierTresTresLong = static_cast<long long int>(100 * pow(1.0024, i)  + 2 * i*i)*10-1000;
		
		os.write((char*)&UnEntierTresTresLong, sizeof(UnEntierTresTresLong));
		_tabXp[i] = UnEntierTresTresLong;
	}

	os.close();
}

bool Experiences::ecrireEXP(const std::string& fichier)
{
	std::ofstream os(fichier,  std::ios::binary);

	int i = 0;
	// lecture tantque possible
	while (i != 50)
	{
		os.write((char*)&_ExperiencesPersonnages[i], sizeof(_ExperiencesPersonnages[i])); 
		//os << std::endl;
		i++;
	}
	os.close();
	return true;
}

Experiences::~Experiences()
{
}

int Experiences::calculNiveau(int indiceTabxp) const
{
	int niv = 1;
	long long int xp = _ExperiencesPersonnages[indiceTabxp];
	int i = 0;
	while (xp > _tabXp[i]) {
		i++;
	}
	return i;
}

void Experiences::ajouterXP(int indiceTabxp,int montant) {
	_ExperiencesPersonnages[indiceTabxp] += montant;
}
