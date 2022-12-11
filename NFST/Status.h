#pragma once
class Personnage;
#include <vector>

const int BRULURE = 0;
const int EMPOISONNER = 1;
const int COMPTEURFRAGILISER = 2;
const int COMPTEURPROTEGER = 3;
const int EMAGASINEUR = 4;
const int EMAGASINATION = 5;
const int REDUCTEUR = 6;
const int ADDUCTEUR = 7;
const int ADDUCTEURBRUT = 8;
const int COMPTEURRESURECTIONS = 9;
const int STADEZOMBIE = 10;

class Status
{
	public:
		Status();
		Status(Personnage* P);
		bool estBruler()const;
		bool estEmpoisoner()const;
		bool estFragiliser()const;
		bool estProteger()const;

		bool estEnMagasineur()const;
		void ajoutEnmagasination(int montant);
		void retirerEmagasination(int montant);
		int enmagasination()const;
		void devientEnmagasineur();

		void appliquerBrulure();
		void appliquerPoison();
		void ajouterCompteurFragile(int nb);
		void ajouterCompteurProteger(int nb);

		void decrementerCompteur();

		void effetBrulure();
		void soignerBrulure();
		void soignerPoison();
		void effetPoison();

		void setAdducteur(int montant);
		void setReducteur(int montant);
		void setAdducteurBrut(int montant);

		int adducteur()const;
		int reducteur()const;
		int adducteurbrut()const;

		void revivre();
		bool peutRevivre();
		void ajouterCompteurRessurections();

		void contamination();
		void decontamination();
		bool estContaminer()const;
	private:
		Personnage* _perso;
		std::vector<int> _status;
};

