/*************************************************************************
                           Ville  -  description
                             -------------------
    début                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Ville> (fichier Ville.h) ------
#if ! defined ( VILLE_H )
#define VILLE_H

//--------------------------------------------------- Interfaces utilisées
#include "Capteur.h"


//------------------------------------------------------------- Constantes 
const int NB_MAX_CAPTEURS = 1500;
//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Ville>
//
//
//------------------------------------------------------------------------ 

class Ville
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
	void StatsJour( int d7 );
	// Affiche les statistiques de trafic d'une ville pour un jour de la semaine
	
	void EmbouteillageJour( int d7 );
	// Affiche le pourcentage de R et N pour chaque heure d'un jour de la semaine
	
	void TempsParcours( int d7, int hDebut, int hFin, Vecteur<int>& idSegments );
	// Affiche l'heure de depart et le temps de parcours minimal pour parcourir idSegments entre tdebut et tfin au jour d7 de la semaine
	// Passage par référence pour aller + vite
	// TODO: heures de debut et de fin comprises ou pas ?
	// TODO: complexité à diminuer (n^4 ...)

	void AjouterEvenement( int id, Evenement& evenement );
	// Ajoute un evenement à l'un des capteurs de la ville,
	// ou le crée s'il n'existe pas

//------------------------------------------------- Surcharge d'opérateurs
    Ville & operator = ( const Ville & unVille );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    Capteur& operator[] ( int idCapteur );
    // Accès à un capteur

	Capteur& operator[] ( int idCapteur ) const;
	// Accès à un capteur

//-------------------------------------------- Constructeurs - destructeur
    Ville ( const Ville & unVille );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Ville ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Ville ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

void CreerCapteur( int id );
// Cree un capteur et l'insert dans le tableau des capteurs de la ville
// Contrat :	on vérifie avant que ce capteur n'existe pas déjà

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
Capteur* capteurs[NB_MAX_CAPTEURS];
int nombreCapteurs;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Ville>

#endif // VILLE_H
