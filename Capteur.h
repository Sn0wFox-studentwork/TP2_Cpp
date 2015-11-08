/*************************************************************************
                           Capteur  -  description
                             -------------------
    début                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Capteur> (fichier Capteur.h) ------
#if ! defined ( Capteur_H )
#define Capteur_H

//--------------------------------------------------- Interfaces utilisées
#include "Evenement.h"
#include "Vecteur.h"

//------------------------------------------------------------- Constantes
const int TAILLE_RESUME = 5;
const int NB_STATS = 4;

//------------------------------------------------------------------------
// Rôle de la classe <Capteur>
// La classe Capteur modélise un capteur présent sur une rue de la ville (i.e. un segment).
// Elle contient une structure de données permettant l'accès rapide aux Événements ainsi
// qu'aux informations les plus utilisées.
// Elle permet l'ajout d’Evenements à chaque instance de la classe.
// Elle permet de calculer des statistiques sur chaque instance de la classe.
// Chaque instance dispose d'un pointeur vers un autre Capteur, permettant ainsi de les insérer
// dans une instance de TableHachage.
//------------------------------------------------------------------------

class Capteur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void Inserer( Evenement& unEvenement );
	// Mode d'emploi :	Insere l'événement unEvenement dans la structure de donnée du capteur courant.
	//					Si l'événement existe déjà, il est inséré tout de même (présent en double par la suite).

	Vecteur<double> StatsPropres();
	// Mode d'emploi :	Calcul les statistiques du capteur courant tout jours confondus.
	//					Les statistiques sont sous la forme de doubles compris entre 0 et 1 (précision du double).
	//					Si on ne dispose d'aucune donnée, toutes les statistiques seront à 0.
	//					Retourne une instance de Vecteur<double> de taille 4 contenant les statistiques dans l'ordre suivant :
	//					% de N (indice 0), % de R, % de J, % de V (indice 3).

	int TempsSegment ( int d7, int heure, int minute );
	// Mode d'emploi :	Calcul le temps le plus probable necessaire pour passer par le segment (= le capteur courant)
	//					le jour d7, à l'heure heure et à la minute minute.
	//					Retourne ce temps en minutes : c'est à l'appelant de faire la conversion si besoin.
	// Contrat :		L'utilisateur s'engage à donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche),
	//					ainsi qu'une heure comprise entre 0 et 23 et une minute comprise entre 0 et 59.

	int GetID ( ) const { return identifiant; }
	// Mode d'emploi :	Retourne l'identifiant du capteur courant.

	Capteur* GetSuivant ( ) const { return suivant; }
	// Mode d'emploi :	Retourne la valeur du pointeur suivant (= adresse de la variable pointée).

	void SetSuivant ( Capteur* suiv ) { suivant = suiv; }
	// Mode d'emploi :	Fait pointer le pointeur suivant vers le capteur pointé par suiv,.
	//					Suiv peut être un pointeur null (ou un pointeur litéral null nullptr).


//------------------------------------------------- Surcharge d'opérateurs
    Capteur& operator= ( const Capteur& unCapteur );
    // Mode d'emploi :	Réaffecte l'instance courante pour la rendre en tout point similaire à unCapteur.
    //					Les deux capteurs auront alors les même données, mais non partagées (copies).

//-------------------------------------------- Constructeurs - destructeur
    Capteur ( const Capteur& unCapteur );
    // Mode d'emploi :	Consruit une nouvelle instance de Capteur à partir d'un Capteur existant unCapteur.
    //					Les deux capteurs auront alors les même données, mais non partagées (copies).

    Capteur ( int id );
    // Mode d'emploi :	Construit une nouvelle instance de Ville.
    //					L'identifiant id du Capteur n'a de sens que s'il est unique (ou au moins unique
	//					pour chaque Ville à laquelle le Capteur appartiendra). Cependant, aucune vérification
	//					de cette unicité ne sera faîte.
    // Contrat :		Pour maintenir la cohérence des données, il est souhaitable que l'utilisateur ne fournisse
	//					que des identifiants id différents pour chaque instance de Capteur.

    virtual ~Capteur ( );
    // Mode d'emploi :	Détruit une instance de Ville et libère la mémoire. Appelé automatiquement.
    //					On peut noter que détruire un Capteur détruira le Capteur pointé par le pointeur suivant,
	//					et ainsi de suite (fonctionnement récursif).

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés

int identifiant;
Capteur* suivant;	// Pour insertion dans une TableHachage qui gère les collisions grâce à une liste chaînée.
	// Statistiques hebdomadaires :
int semaineResume[MIN_PAR_SEMAINE][NB_STATS];
/* NB : Structure de semaineResume :
	[i][0] : nombre de V
	[i][1] : nombre de J
	[i][2] : nombre de R
	[i][3] : nombre de N
	L'indice i correspond à la ième minute de la semaine.
*/
	// Résumé des statistique par jour de la semaine : (évite de faire 1440 itérations pour certains algos)
int d1Resume[TAILLE_RESUME];
int d2Resume[TAILLE_RESUME];
int d3Resume[TAILLE_RESUME];
int d4Resume[TAILLE_RESUME];
int d5Resume[TAILLE_RESUME];
int d6Resume[TAILLE_RESUME];
int d7Resume[TAILLE_RESUME];
/* Contenu d'un resume
	0 : nombre de V
	1 : nombre de J
	2 : nombre de R
	3 : nombre de N
	4 : nombre total d'évènements
*/

};

#endif // Capteur_H
