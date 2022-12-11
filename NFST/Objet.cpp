#include "Objet.h"
#include "Personnage.h"

Objet::Objet() : _nom{"VIDE"}, _effet{"AUCUN"},_rareter{0},_numero{0}
{
}

Objet::Objet(std::string nom, int numero, int rareter, std::string effet) : _nom{ nom }, _effet{ effet }, _rareter{rareter }, _numero{ numero }
{
}

std::string Objet::nom() const
{
	return _nom;
}

std::string Objet::effet() const
{
	return _effet;
}

int Objet::rareter() const
{
	return _rareter;
}

std::string Objet::rareterTexte() {
	std::string txt;
	switch (_rareter)
	{
	case 10:
		txt = "Commun";
		break;
	case 100:
		txt = "Rare";
		break;
	case 1000:
		txt = "Epique";
		break;
	case 10000:
		txt = "Legendaire";
		break;
	case 100000:
		txt = "Mythique";
		break;
	}

	return txt;
}

void Objet::appliquerEffet(Personnage* P) {
	switch (_numero)
	{
	case 3:
		P->ajouterVie(P->vieMax() / 2);
		break;
	case 6:
		P->ajouterChanceHabileter(10);
		break;
	case 7:
		P->ajouterVitesse(P->vitesse()/3);
		break;
	case 8:
		P->ajouterVitesse((int)(-0.80 * (double)P->vitesse()));
		break;
	case 9:
		P->ajouterDeviation(6);
		break;
	case 11:
		P->ajouterReduction(10);
		break;
	case 14:
		P->ajouterReduction(10);
		break;
	case 15:
		P->ajouterCoupCritique(5);
		P->ajouterEsquive(10);
		break;
	case 17:
		P->ajouterVitesse(P->vitesse()/10);
		break;
	case 18:
		P->ajouterCoupCritique(5);
		break;
	case 19:
		P->ajouterForce(10);
		P->ajouterVie(100);
		P->ajouterVitesse(10);
		break;
	case 20:
		P->ajouterForce(100);
		P->ajouterVie(1000);
		P->ajouterVitesse(100);
		break;
	case 21:
		P->ajouterForce(1000);
		P->ajouterVie(10000);
		P->ajouterVitesse(1000);
		break;
	case 22:
		P->ajouterForce( P->force()/20);
		break;
	case 23:
		P->ajouterVie( P->vieMax()/20);
		break;
	case 24:
		P->ajouterForce( P->force()/10);
		P->ajouterCoupCritique(5);
		P->ajouterDegatsCritique(10);
		break;
	case 26:
		P->ajouterForce(10000);
		P->ajouterVie(100000);
		P->ajouterVitesse(10000);
		break;
	case 27:
		P->ajouterChanceRicochet(7);
		break;
	case 30:
		P->status().ajouterCompteurRessurections();
		break;
	case 47:
		P->ajouterForce((int)(0.08*P->force()));
		P->ajouterVie((int)(0.08*P->vieMax()));
		P->ajouterVitesse((int)(0.08*P->vitesse()));
		P->ajouterChanceHabileter(8);
		P->ajouterDeviation(8);
		P->ajouterReduction(8);
		P->ajouterCoupCritique(8);
		P->ajouterDegatsCritique(8);
		P->ajouterEsquive(8);
		P->ajouterChanceRicochet(8);
		P->ajouterChanceDoubleAttaque(8);
	default:
		break;
	}
}
int Objet::numero() const
{
	return _numero;
}
