/*************************************************************************
                           Evenement  -  description
                             -------------------
    début                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Evenement> (fichier Evenement.h) ------
#if ! defined ( EVENEMENT_H )
#define EVENEMENT_H

//--------------------------------------------------- Interfaces utilisées
#include "Temps.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

enum Trafic{
	V,J,R,N
};

//------------------------------------------------------------------------
// Rôle de la classe <Evenement>
//
//
//------------------------------------------------------------------------

class Evenement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
	Trafic GetTrafic() const { return trafic; }
    // Donne le trafic

	int GetD7() const { return temps.GetD7(); }
	// Donne le jour de la semaine

	int GetHeure() const {  return temps.GetHeure(); }
	// Donne l'heure

	int GetMinute() const { return temps.GetMinute(); }
	// Donne la minute

//------------------------------------------------- Surcharge d'opérateurs
    Evenement & operator = ( const Evenement & unEvenement );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool operator== ( const Evenement & unEvenement ) const;
    //surcharge de comparaison

    bool operator< ( const Evenement & unEvenement ) const;
    //surcharge de comparaison


//-------------------------------------------- Constructeurs - destructeur
    Evenement ( const Evenement & unEvenement );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Evenement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Evenement (Trafic unTrafic, Temps unTemps );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Evenement ( );
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
Trafic trafic;
Temps temps;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Evenement>

#endif // EVENEMENT_H
