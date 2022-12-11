#include "Delais.h"
#include <iostream>


Delais::Delais()
{
	_delais = delaisBase;
	int ci = delaisBase;
	FILE* file = fopen("DL.txt", "r");
	if (file == NULL) {
		std::ofstream os("DL.txt", std::ios::binary);
		os.write((char*)&ci, sizeof(ci));
		//os << 1 << std::endl;
		os.close();
	}
	else {
		fclose(file);
	}
	/*std::ifstream is("DL.txt", std::ios::binary);
	is.read((char*)&_niveauMax, sizeof(_niveauMax));
	//is >> _niveauMax;
	is.close();
	*/
}

int Delais::getDelais() const
{
	
	std::ifstream is("DL.txt", std::ios::binary);
	is.read((char*)&_delais, sizeof(_delais));
	//is >> _niveauMax;
	is.close();
	return _delais;
}

void Delais::setDelais(int delais)
{
	std::ofstream os("DL.txt", std::ios::binary);
	os.write((char*)&delais, sizeof(delais));
	//os << 1 << std::endl;
	os.close();
}
