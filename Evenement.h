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
const int TEMPS_PARCOURS_V = 1;
const int TEMPS_PARCOURS_J = 2;
const int TEMPS_PARCOURS_R = 4;
const int TEMPS_PARCOURS_N = 10;

//------------------------------------------------------------------ Types

enum Trafic{
	V,J,R,N
};

//------------------------------------------------------------------------
// Rôle de la classe <Evenement>
// La classe Événement représente le trafic perçu par un Capteur à un temps donné.
// Elle est composée d'un temps et d'un trafic, ce dernier étant traduit par une énumération basique (V, J, R ou N).
// Elle permet un accès plus direct à chacune de ces composantes.
//------------------------------------------------------------------------

class Evenement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	Trafic GetTrafic() const { return trafic; }
    // Mode d'emplois :	Donne le trafic

	int GetD7() const { return temps.GetD7(); }
	// Mode d'emplois :	Donne le jour de la semaine

	int GetHeure() const {  return temps.GetHeure(); }
	// Mode d'emplois :	Donne l'heure

	int GetMinute() const { return temps.GetMinute(); }
	// Mode d'emplois :	Donne la minute

//------------------------------------------------- Surcharge d'opérateurs
    Evenement & operator = ( const Evenement & unEvenement );
	// Mode d'emploi : Réaffecte l'instance courante pour la rendre en tout point similaire à unEvenement.

    bool operator== ( const Evenement & unEvenement ) const;
	// Mode d'emploi : Retourne true si les deux Evenements sont égaux (en termes de temps), false sinon.

    bool operator< ( const Evenement & unEvenement ) const;
	// Mode d'emploi : Retourne true si l'Evenement courant est antérieur à unEvenement, false sinon.


//-------------------------------------------- Constructeurs - destructeur
    Evenement ( const Evenement & unEvenement );
	// Mode d'emploi (constructeur de copie) : Construit une nouvelle instance de Evenement à partir d'un Evenement existant unEvenement.

    Evenement ( );
	// Mode d'emploi : Construit par défaut un Evenement se produisant à un Temps nul et de trafic maximum.

    Evenement ( Trafic unTrafic, Temps unTemps );
	// Mode d'emploi : Construit un Evenement dont les attributs sont donnés par l'utilisateur.

    virtual ~Evenement ( );
	// Mode d'emploi : Detruit une instance d'Evenement

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
Trafic trafic;
Temps temps;

};

//----------------------------------------- Types dépendants de <Evenement>

#endif // EVENEMENT_H
