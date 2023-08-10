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
	case OBJET_BENEDICTION:
		P->ajouterVie(P->vieMax() / 2);
		break;
	case OBJET_CAPE_HABILETE:
		P->ajouterChanceHabileter(10);
		break;
	case OBJET_PATTE_LAPIN:
		P->ajouterVitesse(P->vitesse()/3);
		break;
	case OBJET_BEUH:
		P->ajouterVitesse((int)(-0.80 * (double)P->vitesse()));
		break;
	case OBJET_VOILE_MIROIR:
		P->ajouterDeviation(6);
		break;
	case OBJET_ARMURE_PROTECTEUR:
		P->ajouterReduction(10);
		break;
	case OBJET_ARMURE_SAKERATSU:
		P->ajouterReduction(10);
		break;
	case OBJET_CAPE_NINJA:
		P->ajouterCoupCritique(3);
		P->ajouterEsquive(10);
		break;
	case OBJET_DAGUE_NINJA:
		P->ajouterDegatsCritique(20);
		break;
	case OBJET_SOIE_LAPIN:
		P->ajouterVitesse(P->vitesse()/10);
		break;
	case OBJET_SAUCIFLAR:
		P->ajouterCoupCritique(5);
		break;
	case OBJET_J_B:
		P->ajouterForce(10);
		P->ajouterVie(100);
		P->ajouterVitesse(10);
		break;
	case OBJET_COLERE_FLORIAN:
		P->ajouterForce(50);
		P->ajouterVie(500);
		P->ajouterVitesse(50);
		break;
	case OBJET_TRINITE:
		P->ajouterForce(100);
		P->ajouterVie(1000);
		P->ajouterVitesse(100);
		break;
	case OBJET_DEBARDEUR_NICOLAS:
		P->ajouterForce( P->force()/20);
		break;
	case OBJET_JUS_POMME:
		P->ajouterVie( P->vieMax()/20);
		break;
	case OBJET_EXCALIBUER:
		P->ajouterForce(500);
		P->ajouterVie(5000);
		P->ajouterVitesse(500);
		break;
	case OBJET_FLECHES_TRANCHANTES:
		P->ajouterChanceRicochet(7);
		break;
	case OBJET_TOTEM_IMMUNITE:
		P->status().ajouterCompteurRessurections();
		break;
	case OBJET_HUIT_BALL:
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
