/*************************************************************************
                           Temps  -  description
                             -------------------
    début                : 19/10/2015
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
// Rôle de la classe <Temps>
// La classe Temps représente une date. Elle contient un champs pour chaque décomposition d'une date
// (année, mois, jour.... etc, etc) ainsi qu'un champ d7, de 1 à 7, qui indique le jour de la semaine à la date,
// afin d’éviter d'avoir à le recalculer régulièrement. Il dispose du coup d'un constructeur qui prend
// l'ensemble des champs en paramètre pour simplifier l'ajout d'un événement.
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

	int GetD7( ) const { return d7; }
	// Mode d'emploi :	Donne le jour de la semaine

	int GetHeure( ) const { return heure; }
	// Mode d'emploi :	Donne l'heure

	int GetMinute( ) const { return minute;  }
	// Mode d'emploi :	Donne la minute


//------------------------------------------------- Surcharge d'opérateurs
    Temps & operator = ( const Temps & unTemps );
	// Mode d'emploi :	Réaffecte l'instance courante pour la rendre en tout point similaire à unTemps.

    bool operator== ( const Temps & unTemps ) const;
	// Mode d'emploi :	Retourne true si les deux Evenements sont égaux (en termesde d7, année, mois, jour, minute, seconde),
	//					false sinon.

    bool operator< ( const Temps & unTemps ) const;
	// Mode d'emploi : Retourne true si le Temps courant est antérieur à unTemps, false sinon.


//-------------------------------------------- Constructeurs - destructeur
    Temps ( const Temps & unTemps );
	// Mode d'emploi (constructeur de copie) :	Consruit une nouvelle instance de Temps à partir d'un Temps existant unTemps.

    Temps ( );
	// Mode d'emploi :	Construit un Temps avec toutes ses valeurs à 0 et un D7 de 1

    Temps ( int und7, int uneAnnee, int unMois, int unJour, int uneHeure, int uneMinute );
	// Mode d'emploi :	Construit un Temps avec initialisation des valeurs par l'utilisateurs
	// Contrat :		Respecter le système d'unités pour les temps afin de donner une date cohérente.


    virtual ~Temps ( );
	// Mode d'emploi :	Detruit une instance de temps

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs protégés
int d7;			//1 = lundi, 7 = dimanche
int annee;
int mois;
int jour;
int heure;
int minute;

private:

};

#endif // TEMPS_H
