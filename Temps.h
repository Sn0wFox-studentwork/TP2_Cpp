/*************************************************************************
                           Temps  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Temps> (fichier ${file_name}) ------
#if ! defined ( TEMPS_H )
#define TEMPS_H

//--------------------------------------------------- Interfaces utilis�es

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// R�le de la classe <Temps>
//
//
//------------------------------------------------------------------------

class Temps
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    // type M�thode ( liste de param�tres );
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


//------------------------------------------------- Surcharge d'op�rateurs
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
//----------------------------------------------------- M�thodes prot�g�es

private:
//------------------------------------------------------- M�thodes priv�es

protected:
//----------------------------------------------------- Attributs prot�g�s
int d7;			//1 = lundi, 7 = dimanche
int annee;
int mois;
int jour;
int heure;
int minute;

private:
//------------------------------------------------------- Attributs priv�s

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <Temps>

#endif // TEMPS_H
