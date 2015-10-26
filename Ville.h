/*************************************************************************
                           Ville  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Ville> (fichier Ville.h) ------
#if ! defined ( VILLE_H )
#define VILLE_H

//--------------------------------------------------- Interfaces utilis�es
#include "Capteur.h"


//------------------------------------------------------------- Constantes 
const int NB_MAX_CAPTEURS = 1500;
//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <Ville>
//
//
//------------------------------------------------------------------------ 

class Ville
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    // type M�thode ( liste de param�tres );
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
	// Passage par r�f�rence pour aller + vite
	// TODO: heures de debut et de fin comprises ou pas ?
	// TODO: complexit� � diminuer (n^4 ...)

	void AjouterEvenement( int id, Evenement& evenement );
	// Ajoute un evenement � l'un des capteurs de la ville,
	// ou le cr�e s'il n'existe pas

//------------------------------------------------- Surcharge d'op�rateurs
    Ville & operator = ( const Ville & unVille );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    Capteur& operator[] ( int idCapteur );
    // Acc�s � un capteur

	Capteur& operator[] ( int idCapteur ) const;
	// Acc�s � un capteur

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
//----------------------------------------------------- M�thodes prot�g�es

void CreerCapteur( int id );
// Cree un capteur et l'insert dans le tableau des capteurs de la ville
// Contrat :	on v�rifie avant que ce capteur n'existe pas d�j�

private:
//------------------------------------------------------- M�thodes priv�es

protected:
//----------------------------------------------------- Attributs prot�g�s
Capteur* capteurs[NB_MAX_CAPTEURS];
int nombreCapteurs;

private:
//------------------------------------------------------- Attributs priv�s

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <Ville>

#endif // VILLE_H
