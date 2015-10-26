/*************************************************************************
                           Temps  -  description
                             -------------------
    début                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Temps> (fichier ${file_name}) ------
#if ! defined ( TEMPS_H )
#define TEMPS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Temps>
//
//
//------------------------------------------------------------------------

class Temps
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

	int GetD7() const { return d7; }
	// Donne le jour de la semaine

	int GetHeure() const { return heure; }
	// Donne l'heure

	int GetMinute() const { return minute;  }
	// Donne la minute


//------------------------------------------------- Surcharge d'opérateurs
    Temps & operator = ( const Temps & unTemps );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool operator== ( const Temps & unTemps ) const;
    //surcharge de comparaison

    bool operator< ( const Temps & unTemps ) const;
    //surcharge de comparaison


//-------------------------------------------- Constructeurs - destructeur
    Temps ( const Temps & unTemps );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Temps ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Temps ( int und7, int uneAnnee, int unMois, int unJour, int uneHeure, int uneMinute );
    // Mode d'emploi :
    //
    // Contrat :
    //


    virtual ~Temps ( );
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
int d7;			//1 = lundi, 7 = dimanche
int annee;
int mois;
int jour;
int heure;
int minute;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Temps>

#endif // TEMPS_H
