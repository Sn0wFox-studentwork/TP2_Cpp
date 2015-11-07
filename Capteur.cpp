/*************************************************************************
Capteur  -  description
-------------------
début                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Réalisation de la classe <Capteur> (fichier Capteur.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstddef>		// Utilisation de nullptr

//------------------------------------------------------ Include personnel
#include "Capteur.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

void Capteur::Inserer( Evenement& unEvenement )
// Algorithme :
// Complexité : O(1)
{
	// Variables permettant de positionner l'insertion
	int indice = ( (unEvenement.GetD7( ) - 1) * HEURE_PAR_JOUR + unEvenement.GetHeure( ) ) * MIN_PAR_HEURE + unEvenement.GetMinute( );
	int * jourTab = nullptr;

	// Détermination de la branche dans laquelle prendre les données
	switch ( unEvenement.GetD7( ) )
	{
	case 1:
		jourTab = d1Resume;
		break;
	case 2:
		jourTab = d2Resume;
		break;
	case 3:
		jourTab = d3Resume;
		break;
	case 4:
		jourTab = d4Resume;
		break;
	case 5:
		jourTab = d5Resume;
		break;
	case 6:
		jourTab = d6Resume;
		break;
	case 7:
		jourTab = d7Resume;
		break;
	default:
		// Erreur : mauvaise demande de jour
		break;
	}  //----- Fin de switch ( d7 )

	// Incrémentation du résumé de la semaine
	switch ( unEvenement.GetTrafic() )
	{
	case V:
		semaineResume[indice][0]++;
		jourTab[0]++;
		break;
	case J:
		semaineResume[indice][1]++;
		jourTab[1]++;
		break;
	case R:
		semaineResume[indice][2]++;
		jourTab[2]++;
		break;
	default:	// case N:
		semaineResume[indice][3]++;
		jourTab[3]++;
		break;

	} //----- Fin de switch ( unEvenement.GetTrafic() )

	// Incrémentation du total
	jourTab[4]++;

} //----- Fin de Inserer

Vecteur<double> Capteur::StatsPropres()
// Algorithme :
// Complexité : O(1), avec un for de taille 4
{
	// Creation de la structure de retour et variables pratiques
	Vecteur<double> statsRetour;
	double total =	d1Resume[4] + d2Resume[4] + d3Resume[4] + d4Resume[4] +
					d5Resume[4] + d6Resume[4] + d7Resume[4];
	double statTrafic;

	// Remplissage
	for (int i = 0; i < TAILLE_RESUME - 1; i++)
	{
		if ( total != 0 )
		{
			statTrafic = ( d1Resume[i] + d2Resume[i] + d3Resume[i] + d4Resume[i] +
				d5Resume[i] + d6Resume[i] + d7Resume[i] ) / total;			
		}
		else
		{
			statTrafic = 0;
		}
		statsRetour.insererFin(statTrafic);
	}
	
	return statsRetour;

} //----- Fin de StatsPropres

Vecteur<double> Capteur::StatsJour( int d7 )
// Algorithme :
// Complexité : O(1), avec un switch et un for de taille 4
{
	// Création structure de retour et variables pratiques
	Vecteur<double> statsRetour;
	int * jourTab = nullptr;
	double total;

	// Détermination de la branche dans laquelle prendre les données
	switch ( d7 )
	{
	case 1:
		jourTab = d1Resume;
		break;
	case 2:
		jourTab = d2Resume;
		break;
	case 3:
		jourTab = d3Resume;
		break;
	case 4:
		jourTab = d4Resume;
		break;
	case 5:
		jourTab = d5Resume;
		break;
	case 6:
		jourTab = d6Resume;
		break;
	case 7:
		jourTab = d7Resume;
		break;
	default:
		// Erreur : mauvaise demande de jour
		break;
	}  //----- Fin de switch ( d7 )

	total = jourTab[4];

	// Insertion dans la structure de retour
	for ( int i = 0; i < TAILLE_RESUME - 1; i++ )
	{
		statsRetour.insererFin( jourTab[i] / total );
	}

	return statsRetour;

} //----- Fin de StatsJour

Vecteur<int> Capteur::DonneesJour( int d7 )
// Algorithme :
// Complexité : O(1), avec un switch et for de taille 5
{
	// Création structure de retour et variables pratiques
	Vecteur<int> donneesRetour;
	int * jourTab = nullptr;

	// Détermination de la branche dans laquelle prendre les données
	switch ( d7 )
	{
	case 1:
		jourTab = d1Resume;
		break;
	case 2:
		jourTab = d2Resume;
		break;
	case 3:
		jourTab = d3Resume;
		break;
	case 4:
		jourTab = d4Resume;
		break;
	case 5:
		jourTab = d5Resume;
		break;
	case 6:
		jourTab = d6Resume;
		break;
	case 7:
		jourTab = d7Resume;
		break;
	default:
		// Erreur : mauvaise demande de jour
		break;
	}  //----- Fin de switch ( d7 )

	// Insertion dans la structure de retour
	for ( int i = 0; i < TAILLE_RESUME; i++ )
	{
		donneesRetour.insererFin( jourTab[i] );
	}

	return donneesRetour;

}  //----- Fin de DonneesJour

int Capteur::TempsSegment ( int d7, int heure, int minute )
// Algorithme :
// Complexité : O(1)
// TODO: les endroits sans données comptes comme des N pour le moment
{
	// Création variable de retour et variables pratiques
	int nombreTrafic = 0;
	int traficLePlusProbable = 0;
	int indice = ((d7 - 1) * HEURE_PAR_JOUR + heure) * MIN_PAR_HEURE + minute;

	for ( int i = 0; i < NB_STATS; i++ )
	{
		if ( semaineResume[indice][i] >= nombreTrafic )	// >= fait prendre le trafic avec le plus long temps de parcours en cas d'égalité
		{												// ceci se traduit par un trafic N pour les endroits sans données
			nombreTrafic = semaineResume[indice][i];
			traficLePlusProbable = i;
		}
	}
	// Retour du temps de parcours le plus probable
	switch ( traficLePlusProbable )
	{
	case 0:		// Trafic = V : temps de parcours de 1 minute
		return TEMPS_PARCOURS_V;
	case 1:		// Trafic = J : temps de parcours de 2 minutes
		return TEMPS_PARCOURS_J;
	case 2:		// Trafic = R : temps de parcours de 4 minutes
		return TEMPS_PARCOURS_R;
	default:	// case 3 ; Trafic = N : temps de parcours de 10 minutes
		return TEMPS_PARCOURS_N;
	}

} //----- Fin de TempsSegment

//------------------------------------------------- Surcharge d'opérateurs
Capteur &Capteur::operator = ( const Capteur &unCapteur )
// Algorithme :		Si on n'est pas en train de faire unCapteur = unCapteur,
//					on "copie" tout les champs :
//					on les modifie pour qu'ils soient comme ceux de unCapteur.
//					On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	identifiant = unCapteur.identifiant;

	for ( int i = 0; i < TAILLE_RESUME; i++ )
	{
		d1Resume[i] = unCapteur.d1Resume[i];
		d2Resume[i] = unCapteur.d2Resume[i];
		d3Resume[i] = unCapteur.d3Resume[i];
		d4Resume[i] = unCapteur.d4Resume[i];
		d5Resume[i] = unCapteur.d5Resume[i];
		d6Resume[i] = unCapteur.d6Resume[i];
		d7Resume[i] = unCapteur.d7Resume[i];
	}

	for (int m = 0; m < MIN_PAR_SEMAINE; m++)
	{
		for (int j = 0; j < NB_STATS; j++)
		{
			semaineResume[m][j] = unCapteur.semaineResume[m][j];
		}
	}

	return  *this;

} //----- Fin de operator =


  //-------------------------------------------- Constructeurs - destructeur
Capteur::Capteur ( const Capteur &unCapteur )
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Capteur>" << endl;
#endif
	
	identifiant = unCapteur.identifiant;

	for ( int i = 0; i < TAILLE_RESUME; i++ )
	{
		d1Resume[i] = unCapteur.d1Resume[i];
		d2Resume[i] = unCapteur.d2Resume[i];
		d3Resume[i] = unCapteur.d3Resume[i];
		d4Resume[i] = unCapteur.d4Resume[i];
		d5Resume[i] = unCapteur.d5Resume[i];
		d6Resume[i] = unCapteur.d6Resume[i];
		d7Resume[i] = unCapteur.d7Resume[i];
	}

	for (int m = 0; m < MIN_PAR_SEMAINE; m++)
	{
		for (int j = 0; j < NB_STATS; j++)
		{
			semaineResume[m][j] = unCapteur.semaineResume[m][j];
		}
	}

} //----- Fin de Capteur (constructeur de copie)

Capteur::Capteur( int id ) : identifiant( id )
{
#ifdef MAP
	cout << "Appel au constructeur de <Capteur>" << endl;
#endif

	for ( int i = 0; i < TAILLE_RESUME; i++ )
	{
		d1Resume[i] = 0;
		d1Resume[i] = 0;
		d1Resume[i] = 0;
		d1Resume[i] = 0;
		d1Resume[i] = 0;
		d1Resume[i] = 0;
		d1Resume[i] = 0;
	}

	for (int m = 0; m < MIN_PAR_SEMAINE; m++)
	{
		for (int s = 0; s < NB_STATS; s++)
		{
			semaineResume[m][s] = 0;
		}
	}

} //----- Fin de Capteur


Capteur::~Capteur ()
// Algorithme :
{
#ifdef MAP
	cout << "Appel au destructeur de <Capteur>" << endl;
#endif

	// Pas d'allocation dynamique ici

} //----- Fin de ~Capteur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées
