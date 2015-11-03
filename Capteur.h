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
	//insere un evenement dans le bon tableau
	
	Vecteur<double> StatsPropres();
	//renvoie les stats tous jours confondus
	
	Vecteur<double> StatsJour( int d7 );
	//renvoie les stats pour un jour de la semaine

	Vecteur<int> DonneesJour( int d7 );
	//renvoie les données pour un jour de la semaine
	
	Vecteur<int> EmbouteillageJour( int d7 );
	//renvoie le nombre de R et de N pour chaque heure d'un jour de la semaine, et le total
	
	int TempsSegment( int d7, int heure, int minute );
	// Temps necessaire pour passer par le segment selon l'heure entre tdebut et tfin au jour de la semaine d7
	// Temps en minutes : c'est à l'appelant de faire la conversion si besoin

	int GetID() const { return identifiant; }
	// Retourne l'identifiant du capteur

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

// TODO: optimiser structure / dédoubler structure pour + d'efficacite
Vecteur <Evenement> d1Contenu;
Vecteur <Evenement> d2Contenu;
Vecteur <Evenement> d3Contenu;
Vecteur <Evenement> d4Contenu;
Vecteur <Evenement> d5Contenu;
Vecteur <Evenement> d6Contenu;
Vecteur <Evenement> d7Contenu;
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
