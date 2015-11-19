/*************************************************************************
                           Temps  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Temps> (fichier Temps.cpp) ------
#if ! defined ( TEMPS_H )
#define TEMPS_H

//------------------------------------------------------------- Constantes
const int MIN_PAR_HEURE = 60;
const int HEURE_PAR_JOUR = 24;
const int JOUR_PAR_SEMAINE = 7;
const int MIN_PAR_SEMAINE = JOUR_PAR_SEMAINE * HEURE_PAR_JOUR * MIN_PAR_HEURE;

//------------------------------------------------------------------------
// R�le de la classe <Temps>
// La classe Temps repr�sente une date. Elle contient un champs pour chaque d�composition d'une date
// (ann�e, mois, jour.... etc, etc) ainsi qu'un champ d7, de 1 � 7, qui indique le jour de la semaine � la date,
// afin d��viter d'avoir � le recalculer r�guli�rement. Il dispose du coup d'un constructeur qui prend
// l'ensemble des champs en param�tre pour simplifier l'ajout d'un �v�nement.
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

	int GetD7( ) const { return d7; }
	// Mode d'emploi :	Donne le jour de la semaine

	int GetHeure( ) const { return heure; }
	// Mode d'emploi :	Donne l'heure

	int GetMinute( ) const { return minute;  }
	// Mode d'emploi :	Donne la minute


//------------------------------------------------- Surcharge d'op�rateurs
    Temps & operator = ( const Temps & unTemps );
	// Mode d'emploi :	R�affecte l'instance courante pour la rendre en tout point similaire � unTemps.

    bool operator== ( const Temps & unTemps ) const;
	// Mode d'emploi :	Retourne true si les deux Evenements sont �gaux (en termesde d7, ann�e, mois, jour, minute, seconde),
	//					false sinon.

    bool operator< ( const Temps & unTemps ) const;
	// Mode d'emploi : Retourne true si le Temps courant est ant�rieur � unTemps, false sinon.


//-------------------------------------------- Constructeurs - destructeur
    Temps ( const Temps & unTemps );
	// Mode d'emploi (constructeur de copie) :	Consruit une nouvelle instance de Temps � partir d'un Temps existant unTemps.

    Temps ( );
	// Mode d'emploi :	Construit un Temps avec toutes ses valeurs � 0 et un D7 de 1

    Temps ( int und7, int uneAnnee, int unMois, int unJour, int uneHeure, int uneMinute );
	// Mode d'emploi :	Construit un Temps avec initialisation des valeurs par l'utilisateurs
	// Contrat :		Respecter le syst�me d'unit�s pour les temps afin de donner une date coh�rente.


    virtual ~Temps ( );
	// Mode d'emploi :	Detruit une instance de temps

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs prot�g�s
int d7;			//1 = lundi, 7 = dimanche
int annee;
int mois;
int jour;
int heure;
int minute;

private:

};

#endif // TEMPS_H
