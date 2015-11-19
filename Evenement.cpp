/*************************************************************************
                           Evenement  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- R�alisation de la classe <Evenement> (fichier Evenement.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Evenement.h"

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques

//------------------------------------------------- Surcharge d'op�rateurs
Evenement & Evenement::operator = (const Evenement & unEvenement)
// Algorithme :	Si on n'est pas en train de faire unEvenement = unEvenement,
//				on "copie" tout les champs :
//				on les modifie pour qu'ils soient comme ceux de unEvenement.
//				On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	if ( this != &unEvenement )
	{
		temps = unEvenement.temps;		// appel � la surcharge de = de Temps
		trafic = unEvenement.trafic;
	}

    return *this;

} //----- Fin de operator =

bool Evenement::operator== ( const Evenement & unEvenement ) const
// Algorithme :	comparaison sur l'attribut temps
{
    return temps == unEvenement.temps;
} //----- Fin de operator ==

bool Evenement::operator< ( const Evenement & unEvenement ) const
// Algorithme : comparaison sur l'attribut temps
{
    return temps < unEvenement.temps;
} //----- Fin de operator <

//-------------------------------------------- Constructeurs - destructeur
Evenement::Evenement ( const Evenement & unEvenement ) : trafic(unEvenement.trafic), temps(unEvenement.temps)
// Algorithme :	les constructeurs de copies des membres sont d�j� d�finis
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Evenement>" << endl;
#endif

} //----- Fin de Evenement (constructeur de copie)


Evenement::Evenement ( ) : trafic( N ), temps( )
// Algorithme : On donne � l'Evenement le temps par d�faut et le trafic maximum
{
#ifdef MAP
    cout << "Appel au constructeur de <Evenement>" << endl;
#endif
   
} //----- Fin de Evenement

Evenement::Evenement ( Trafic unTrafic, Temps unTemps ) : trafic( unTrafic ) , temps( unTemps )
// Algorithme : Affectation en utilisant les constructeurs d�j� d�finis
{
#ifdef MAP
    cout << "Appel au constructeur par param�tres de <Evenement>" << endl;
#endif

} //----- Fin de Evenement

Evenement::~Evenement ( )
// Algorithme : Les membres ont d�j� un destructeur bien d�fini. Rien de particulier � g�rer.
{
#ifdef MAP
    cout << "Appel au destructeur de <Evenement>" << endl;
#endif

} //----- Fin de ~Evenement

