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

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Capteur>
//
//
//------------------------------------------------------------------------

class Capteur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
	void Inserer( Evenement& unEvenement );
	// Mode d'emploi :	insere l'événement unEvenement dans la structure de donnée du capteur courant.
	//					Si l'événement existe déjà, il est inséré tout de même (présent en double par la suite).

	Vecteur<double> StatsPropres();
	// Mode d'emploi :	Calcul les statistiques du capteur courant tout jours confondus.
	//					Les statistiques sont sous la forme de doubles compris entre 0 et 1 (précision du double).
	//					Si on ne dispose d'aucune donnée, toutes les statistiques seront à 0.
	//					Retourne une instance de Vecteur<double> de taille 4 contenant les statistiques dans l'ordre suivant :
	//					% de N (indice 0), % de R, % de J, % de V (indice 3).

	Vecteur<double> StatsJour( int d7 );
	// Mode d'emploi :	Calcul les statistiques du capteur courant pour le jour d7.
	//					Les statistiques sont sous la forme de doubles compris entre 0 et 1.
	//					Si on ne dispose d'aucune donnée, toutes les statistiques seront à 0.
	//					Retourne une instance de Vecteur<double> de taille 4 contenant les statistiques dans l'ordre suivant :
	//					% de N (indice 0), % de R, % de J, % de V (indice 3).

	Vecteur<int> DonneesJour( int d7 );
	// Mode d'emploi :	renvoie les données pour un jour de la semaine

	int TempsSegment( int d7, int heure, int minute );
	// Mode d'emploi :	Calcul le temps moyen necessaire pour passer par le segment (= le capteur courant)
	//					le jour d7, à l'heure heure et à la minute minute.
	//					Retourne ce temps en minutes : c'est à l'appelant de faire la conversion si besoin.

	int GetID() const { return identifiant; }
	// Mode d'emploi :	Retourne l'identifiant du capteur courant.



//------------------------------------------------- Surcharge d'opérateurs
    Capteur& operator= ( const Capteur& unCapteur );
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Capteur ( const Capteur& unCapteur );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Capteur ( int id );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Capteur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

int identifiant;
int semaineResume[MIN_PAR_SEMAINE][NB_STATS];
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



private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Capteur>

#endif // Capteur_H
