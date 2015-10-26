/*************************************************************************
                           Evenement  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Réalisation de la classe <Evenement> (fichier ${file_name}) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Evenement.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type Evenement::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
Evenement & Evenement::operator = ( const Evenement & unEvenement )
// Algorithme :
//
{
    temps = unEvenement.temps;		// appel à la surcharge de = de Temps
    trafic = unEvenement.trafic;
    return *this;
} //----- Fin de operator =

bool Evenement::operator== ( const Evenement & unEvenement ) const
// Algorithme : comparaison des temps
//
{
    return temps == unEvenement.temps;
} //----- Fin de operator ==

bool Evenement::operator< ( const Evenement & unEvenement ) const
// Algorithme : comparaison des temps
//
{
    return temps < unEvenement.temps;
} //----- Fin de operator <

//-------------------------------------------- Constructeurs - destructeur
Evenement::Evenement ( const Evenement & unEvenement ) : trafic(unEvenement.trafic), temps(unEvenement.temps)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Evenement>" << endl;
#endif

} //----- Fin de Evenement (constructeur de copie)


Evenement::Evenement ( ) : temps(), trafic(N)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Evenement>" << endl;
#endif
   
} //----- Fin de Evenement

Evenement::Evenement (Trafic unTrafic, Temps unTemps ) : trafic(unTrafic) , temps(unTemps)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur par paramètres de <Evenement>" << endl;
#endif

} //----- Fin de Evenement

Evenement::~Evenement ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Evenement>" << endl;
#endif

} //----- Fin de ~Evenement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
