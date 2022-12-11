#pragma once
class Statistiques
{
public:
	Statistiques();
	void incrementerNbAttaques();
	void incrementerNbAttaquesRecues();
	void ajouterDegatsProvoquer(int montant);
	void ajouterDegatsRecu(long long int montant);
	void ajouterSoinsDonner(int montant);
	void ajouterBouclierDonner(int montant);

	void ajouterAugmentationVieMax(long long int montant);
	void ajouterAugmentationReduction(int montant);
	void ajouterAugmentationChanceDoubleAttaque(int montant);
	void ajouterAugmentationChanceHabileter(int montant);
	void ajouterAugmentationCoupCritiques(int montant);
	void ajouterAugmentationDegatsCritique(int montant);
	void ajouterAugmentationForce(int montant);

	int nbAttaques()const;
	int nbAttaquesRecues()const;
	long long int degatsProvoquer()const;
	long long int degatsRecu()const;
	long long int soinsDonner()const;
	long long int bouclierDonner()const;

	long long int augmentationVieMax()const;
	int augmentationReduction()const;
	int augmentationChanceDoubleAttaque()const;
	int augmentationChanceHabileter()const;
	int augmentationCoupCritiques()const;
	int augmentationDegatsCritique()const;
	int augmentationForce()const;

	int plusGrosseAttaqueRecue()const;
	int plusGrosseAttaqueEnvoyer()const;
	void changerPlusGrosseAttaqueRecue(int montant);
	void changerPlusGrosseAttaqueEnvoyer(int montant);
	

private:
	int _nbAttaques;
	int _nbAttaquesRecues;
	long long int _degatsProvoquer;
	long long int _degatsRecu;
	long long int _soinsDonner;
	long long int _bouclierDonner;

	long long int _augmentationVieMax;
	int _augmentationReduction;
	int _augmentationChanceDoubleAttaque;
	int _augmentationChanceHabileter;
	int _augmentationCoupCritiques;
	int _augmentationDegatsCritique;
	int _augmentationForce;
	int _plusGrosseAttaqueRecue;
	int _plusGrosseAttaqueEnvoyer;
};

