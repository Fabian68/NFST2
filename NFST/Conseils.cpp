#include "Conseils.h"
#include "Aleatoire.h"

Conseils::Conseils()
{
	_listeConseils.push_back("Nicolas aime ce faire mal, mais ca le rend plus fort !");
	_listeConseils.push_back("Florian un soutien indiscutable.");
	_listeConseils.push_back("Tout le monde aime les tortues.");
	_listeConseils.push_back("Maelle fait très mal.");
	_listeConseils.push_back("Un coup habile fais deux fois plus mal, ou soigne deux fois mieux.");
	_listeConseils.push_back("Un ricochet habile et/ou critique fais du bien.");
	_listeConseils.push_back("Un ricochet habile et/ou critique fais du bien.");
	_listeConseils.push_back("Thomas améliore la resistance des alliers quand il se fait attaquer.");
	_listeConseils.push_back("Amine est le personnage qui fait le plus de dégats.");
	_listeConseils.push_back("Le jeu ne serait pas aussi parfait sans Salim.");
	_listeConseils.push_back("Seb envoie du lourd.");
	_listeConseils.push_back("Les animaux sont efficaces sur les attaques répétés !");
	_listeConseils.push_back("Penser a regarder si vous avez débloquer une place dans l'équipe");
	_listeConseils.push_back("JB le bon coéquipier, a ne pas utiliser tout seul.");
	_listeConseils.push_back("Moustick deviens plus puissant quand il a moins de vie !");
	_listeConseils.push_back("Moustick deviens plus resistant quand il a moins de vie !");
	_listeConseils.push_back("Cloé un personnage comme un autre .");
	_listeConseils.push_back("Isidore un personnage sympathique.");
	_listeConseils.push_back("Sur David la vitesse joue beaucoup.");
	_listeConseils.push_back("Bryan un dps monstrueux.");
	_listeConseils.push_back("Amine est un anti-tank.");
	_listeConseils.push_back("Bryan deviens plus fort au fur et a mesure d'une partie.");
	_listeConseils.push_back("La bonne repartition des orbes est parfois vital .");
	_listeConseils.push_back("Ne pas jouer d'animal offensif sur Fiona, surtout pas ! .");
	_listeConseils.push_back("Fabian n'est pas le meilleur personne, mais non x) .");
	_listeConseils.push_back("Florian adore les vieux jeux vidéos .");
	_listeConseils.push_back("NaN .");
}

std::string Conseils::conseilAleatoire() const
{
	return _listeConseils[Aleatoire(0, _listeConseils.size() - 1).entier()];
}
