/*************************************************************************
                           Evenement  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Evenement> (fichier Evenement.h) ------
#if ! defined ( EVENEMENT_H )
#define EVENEMENT_H

//--------------------------------------------------- Interfaces utilis�es
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
// R�le de la classe <Evenement>
// La classe �v�nement repr�sente le trafic per�u par un Capteur � un temps donn�.
// Elle est compos�e d'un temps et d'un trafic, ce dernier �tant traduit par une �num�ration basique (V, J, R ou N).
// Elle permet un acc�s plus direct � chacune de ces composantes.
//------------------------------------------------------------------------

class Evenement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

	Trafic GetTrafic() const { return trafic; }
    // Mode d'emplois :	Donne le trafic

	int GetD7() const { return temps.GetD7(); }
	// Mode d'emplois :	Donne le jour de la semaine

	int GetHeure() const {  return temps.GetHeure(); }
	// Mode d'emplois :	Donne l'heure

	int GetMinute() const { return temps.GetMinute(); }
	// Mode d'emplois :	Donne la minute

//------------------------------------------------- Surcharge d'op�rateurs
    Evenement & operator = ( const Evenement & unEvenement );
	// Mode d'emploi : R�affecte l'instance courante pour la rendre en tout point similaire � unEvenement.

    bool operator== ( const Evenement & unEvenement ) const;
	// Mode d'emploi : Retourne true si les deux Evenements sont �gaux (en termes de temps), false sinon.

    bool operator< ( const Evenement & unEvenement ) const;
	// Mode d'emploi : Retourne true si l'Evenement courant est ant�rieur � unEvenement, false sinon.


//-------------------------------------------- Constructeurs - destructeur
    Evenement ( const Evenement & unEvenement );
	// Mode d'emploi (constructeur de copie) : Construit une nouvelle instance de Evenement � partir d'un Evenement existant unEvenement.

    Evenement ( );
	// Mode d'emploi : Construit par d�faut un Evenement se produisant � un Temps nul et de trafic maximum.

    Evenement ( Trafic unTrafic, Temps unTemps );
	// Mode d'emploi : Construit un Evenement dont les attributs sont donn�s par l'utilisateur.

    virtual ~Evenement ( );
	// Mode d'emploi : Detruit une instance d'Evenement

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs prot�g�s
Trafic trafic;
Temps temps;

};

//----------------------------------------- Types d�pendants de <Evenement>

#endif // EVENEMENT_H
