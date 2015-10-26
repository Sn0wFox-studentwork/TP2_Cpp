/*************************************************************************
                           Evenement  -  description
                             -------------------
    d�but                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- R�alisation de la classe <Evenement> (fichier ${file_name}) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Evenement.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types priv�s


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- M�thodes publiques
// type Evenement::M�thode ( liste de param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode


//------------------------------------------------- Surcharge d'op�rateurs
Evenement & Evenement::operator = ( const Evenement & unEvenement )
// Algorithme :
//
{
    temps = unEvenement.temps;		// appel � la surcharge de = de Temps
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
    cout << "Appel au constructeur par param�tres de <Evenement>" << endl;
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

//----------------------------------------------------- M�thodes prot�g�es

//------------------------------------------------------- M�thodes priv�es
