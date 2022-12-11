#pragma once
#include <fstream>
const int delaisBase = 50;
class Delais
{
public:
	Delais();
	int getDelais()const;
	void setDelais(int delais);
private:
	int _delais;
};

