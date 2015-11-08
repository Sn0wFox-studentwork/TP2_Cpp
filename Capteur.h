/*************************************************************************
                           Capteur  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Capteur> (fichier Capteur.h) ------
#if ! defined ( Capteur_H )
#define Capteur_H

//--------------------------------------------------- Interfaces utilis�es
#include "Evenement.h"
#include "Vecteur.h"

//------------------------------------------------------------- Constantes
const int TAILLE_RESUME = 5;
const int NB_STATS = 4;

//------------------------------------------------------------------------
// R�le de la classe <Capteur>
// La classe Capteur mod�lise un capteur pr�sent sur une rue de la ville (i.e. un segment).
// Elle contient une structure de donn�es permettant l'acc�s rapide aux �v�nements ainsi
// qu'aux informations les plus utilis�es.
// Elle permet l'ajout d�Evenements � chaque instance de la classe.
// Elle permet de calculer des statistiques sur chaque instance de la classe.
// Chaque instance dispose d'un pointeur vers un autre Capteur, permettant ainsi de les ins�rer
// dans une instance de TableHachage.
//------------------------------------------------------------------------

class Capteur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

	void Inserer( Evenement& unEvenement );
	// Mode d'emploi :	Insere l'�v�nement unEvenement dans la structure de donn�e du capteur courant.
	//					Si l'�v�nement existe d�j�, il est ins�r� tout de m�me (pr�sent en double par la suite).

	Vecteur<double> StatsPropres();
	// Mode d'emploi :	Calcul les statistiques du capteur courant tout jours confondus.
	//					Les statistiques sont sous la forme de doubles compris entre 0 et 1 (pr�cision du double).
	//					Si on ne dispose d'aucune donn�e, toutes les statistiques seront � 0.
	//					Retourne une instance de Vecteur<double> de taille 4 contenant les statistiques dans l'ordre suivant :
	//					% de N (indice 0),�% de R,�% de J,�% de V (indice 3).

	int TempsSegment ( int d7, int heure, int minute );
	// Mode d'emploi :	Calcul le temps le plus probable necessaire pour passer par le segment (= le capteur courant)
	//					le jour d7, � l'heure heure et � la minute minute.
	//					Retourne ce temps en minutes : c'est � l'appelant de faire la conversion si besoin.
	// Contrat :		L'utilisateur s'engage � donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche),
	//					ainsi qu'une heure comprise entre 0 et 23 et une minute comprise entre 0 et 59.

	int GetID ( ) const { return identifiant; }
	// Mode d'emploi :	Retourne l'identifiant du capteur courant.

	Capteur* GetSuivant ( ) const { return suivant; }
	// Mode d'emploi :	Retourne la valeur du pointeur suivant (= adresse de la variable point�e).

	void SetSuivant ( Capteur* suiv ) { suivant = suiv; }
	// Mode d'emploi :	Fait pointer le pointeur suivant vers le capteur point� par suiv,.
	//					Suiv peut �tre un pointeur null (ou un pointeur lit�ral null nullptr).


//------------------------------------------------- Surcharge d'op�rateurs
    Capteur& operator= ( const Capteur& unCapteur );
    // Mode d'emploi :	R�affecte l'instance courante pour la rendre en tout point similaire � unCapteur.
    //					Les deux capteurs auront alors les m�me donn�es, mais non partag�es (copies).

//-------------------------------------------- Constructeurs - destructeur
    Capteur ( const Capteur& unCapteur );
    // Mode d'emploi :	Consruit une nouvelle instance de Capteur � partir d'un Capteur existant unCapteur.
    //					Les deux capteurs auront alors les m�me donn�es, mais non partag�es (copies).

    Capteur ( int id );
    // Mode d'emploi :	Construit une nouvelle instance de Ville.
    //					L'identifiant id du Capteur n'a de sens que s'il est unique (ou au moins unique
	//					pour chaque Ville � laquelle le Capteur appartiendra). Cependant, aucune v�rification
	//					de cette unicit� ne sera fa�te.
    // Contrat :		Pour maintenir la coh�rence des donn�es, il est souhaitable que l'utilisateur ne fournisse
	//					que des identifiants id diff�rents pour chaque instance de Capteur.

    virtual ~Capteur ( );
    // Mode d'emploi :	D�truit une instance de Ville et lib�re la m�moire. Appel� automatiquement.
    //					On peut noter que d�truire un Capteur d�truira le Capteur point� par le pointeur suivant,
	//					et ainsi de suite (fonctionnement r�cursif).

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs prot�g�s

int identifiant;
Capteur* suivant;	// Pour insertion dans une TableHachage qui g�re les collisions gr�ce � une liste cha�n�e.
	// Statistiques hebdomadaires :
int semaineResume[MIN_PAR_SEMAINE][NB_STATS];
/* NB : Structure de semaineResume :
	[i][0] : nombre de V
	[i][1] : nombre de J
	[i][2] : nombre de R
	[i][3] : nombre de N
	L'indice i correspond � la i�me minute de la semaine.
*/
	// R�sum� des statistique par jour de la semaine : (�vite de faire 1440 it�rations pour certains algos)
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
	4 : nombre total d'�v�nements
*/

};

#endif // Capteur_H
