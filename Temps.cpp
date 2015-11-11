/*************************************************************************
                           Temps  -  description
                             -------------------
    début                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Réalisation de la classe <Temps> (fichier Temps.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Temps.h"

//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type Temps::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
Temps & Temps::operator = ( const Temps & unTemps )
// Algorithme :	Si on n'est pas en train de faire unTemps = unTemps,
//				on "copie" tout les champs :
//				on les modifie pour qu'ils soient comme ceux de unTemps.
//				On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	if ( this != &unTemps )
	{
		d7 = unTemps.d7;
		annee = unTemps.annee;
		mois = unTemps.mois;
		jour = unTemps.jour;
		heure = unTemps.heure;
		minute = unTemps.minute;
	}

    return *this;

} //----- Fin de operator =

bool Temps::operator== (const Temps & unTemps) const
//Algorithme :
{
    if ( d7 != unTemps.d7 )
    {
        return false;
    }
    else if ( annee != unTemps.annee )
    {
        return false;
    }
    else if( mois != unTemps.mois )
    {
        return false;
    }
    else if( jour != unTemps.jour )
    {
        return false;
    }
    else if( heure != unTemps.heure )
    {
        return false;
    }
    else if( minute != unTemps.minute )
    {
        return false;
    }
    else
    {
        return true;
    }
} //----- Fin de operator==

bool Temps::operator< ( const Temps & unTemps ) const
//Algorithme :
{
    if ( annee < unTemps.annee )
    {
        return true;
    }
    else if ( annee == unTemps.annee )
    {
        if ( mois < unTemps.mois )
        {
            return true;
        }
        else if ( mois == unTemps.mois )
        {
            if ( jour < unTemps.jour )
            {
                return true;
            }
            else if ( jour == unTemps.jour )
            {
                if ( heure < unTemps.heure )
                {
                    return true;
                }
                else if ( heure == unTemps.heure )
                {
                    return minute < unTemps.minute;
                }
            }
        }
    }
    return false;
} //----- Fin de operator<


//-------------------------------------------- Constructeurs - destructeur
Temps::Temps ( const Temps & unTemps )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Temps>" << endl;
#endif
    d7 = unTemps.d7;
    annee = unTemps.annee;
    mois = unTemps.mois;
    jour = unTemps.jour;
    heure = unTemps.heure;
    minute = unTemps.minute;
} //----- Fin de Temps (constructeur de copie)


Temps::Temps ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Temps>" << endl;
#endif
    d7 = 0;
    annee = 0;
    mois = 0;
    jour = 0;
    heure = 0;
    minute = 0;
} //----- Fin de Temps

Temps::Temps ( int und7, int uneAnnee, int unMois, int unJour, int uneHeure, int uneMinute )
//Algorithme :
{
#ifdef MAP
    cout << "Appel au constructeur de <Temps> par paramètres" << endl;
#endif
    d7 = und7;
    annee = uneAnnee;
    mois = unMois;
    jour = unJour;
    heure = uneHeure;
    minute = uneMinute;
}

Temps::~Temps ( )
// Algorithme : Rien de particulier à detruire
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Temps>" << endl;
#endif
} //----- Fin de ~Temps


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
