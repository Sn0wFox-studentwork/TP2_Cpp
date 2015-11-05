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
// Complexité : O(1), avec 2 switchs
{
	// Variables permettant de positionner l'insertion
	Vecteur<Evenement>* jour = nullptr;
	int * caseResume = nullptr;

	// Détermination du jour de la semaine
	switch ( unEvenement.GetD7() )
	{
	case 1:
		jour = &d1Contenu;
		caseResume = d1Resume;
		break;
	case 2:
		jour = &d2Contenu;
		caseResume = d2Resume;
		break;
	case 3:
		jour = &d3Contenu;
		caseResume = d3Resume;
		break;
	case 4:
		jour = &d4Contenu;
		caseResume = d4Resume;
		break;
	case 5:
		jour = &d5Contenu;
		caseResume = d5Resume;
		break;
	case 6:
		jour = &d6Contenu;
		caseResume = d6Resume;
		break;
	case 7:
		jour = &d7Contenu;
		caseResume = d7Resume;
		break;
	default:
		// Erreur d'insertion
		break;
	} //----- Fin de switch ( unEvenement.GetD7() )

	// Incrémentation de la bonne case de trafic
	switch ( unEvenement.GetTrafic() )
	{
	case V:
		caseResume[0]++;
		break;
	case J:
		caseResume[1]++;
		break;
	case R:
		caseResume[2]++;
		break;
	default:	// case N:
		caseResume[3]++;
		break;

	} //----- Fin de switch ( unEvenement.GetTrafic() )

	// Insertion dans le vecteur et incrementation du nombre total d'évènements
	jour->insererFin( unEvenement );
	caseResume[4]++;

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

Vecteur<int> Capteur::EmbouteillageJour( int d7 )
// Algorithme :
// Complexité : O(n), avec 1 switch et un for de taille n = taille du vecteur d'évènement du jour
// TODO: a noter qu'on pourrait passer la complexité en O(1) en ajoutant juste 24 tableau de resume par heure
// Structure de retour :	Vecteur 0->23 : nombre d'embouteillage recense par heure
//							24->47 : nombre total de donnees par heure
{
	// Création structure de retour et variables pratiques
	Vecteur<int> donneesRetour;
	Vecteur<Evenement>* jour = nullptr;
	Trafic trafic;

	// Détermination de la branche dans laquelle prendre les données
	switch ( d7 )
	{
	case 1:
		jour = &d1Contenu;
		break;
	case 2:
		jour = &d2Contenu;
		break;
	case 3:
		jour = &d3Contenu;
		break;
	case 4:
		jour = &d4Contenu;
		break;
	case 5:
		jour = &d5Contenu;
		break;
	case 6:
		jour = &d6Contenu;
		break;
	case 7:
		jour = &d7Contenu;
		break;
	default:
		// Erreur : mauvaise demande de jour
		break;
	}  //----- Fin de switch ( d7 )

	// Init de la structure de retour
	for ( int i = 0; i < 48; i++ )
	{
		donneesRetour.insererFin(0);
	}

	// Parcours du tableau d'événements et remplissage de la structure de retour
	for ( int i = 0; i < jour->GetTaille(); i++ )
	{
		trafic = (*jour)[i].GetTrafic();
		if ( trafic == R || trafic == N )
		{
			donneesRetour[(*jour)[i].GetHeure()] += 1;
		}
		donneesRetour[(*jour)[i].GetHeure() + 24] += 1;		// TODO: plus rapide avec creation de variable ?
	}

	return donneesRetour;

} //----- Fin de EmbouteillageJour

// TODO: Vecteur<int> Capteur::TempsSegment2 ( int d7, int hDebut, int hFin, int mDebut, int mFin )
int Capteur::TempsSegment ( int d7, int heure, int minute )
// Algorithme :
// Complexité : O(n), avec un switch et un if+switch dans un for de taille n = taille du vecteur d'évènement du jour
// A noter : toutefois, on sort de la boucle dès qu'on a trouvé le bon horaire
// TODO: complexité améliorable en utilisant un index... encore faut-il pouvoir le mettre en place,
//		 ce qui ne semble pas réalisable malgré le fait qu'on sache que les évènement arrivent dans l'ordre
//		 puisqu'on ne peut pas savoir combien d'instants n'auront pas d'évènements...
//		 à moins de réaliser un tableau avec beaucoup trop de trous
{
	// Création variable de retour et variables pratiques
	int tempsParcours = 0;
	Vecteur<Evenement>* jour = nullptr;

	// Détermination de la branche dans laquelle prendre les données
	switch ( d7 )
	{
	case 1:
		jour = &d1Contenu;
		break;
	case 2:
		jour = &d2Contenu;
		break;
	case 3:
		jour = &d3Contenu;
		break;
	case 4:
		jour = &d4Contenu;
		break;
	case 5:
		jour = &d5Contenu;
		break;
	case 6:
		jour = &d6Contenu;
		break;
	case 7:
		jour = &d7Contenu;
		break;
	default:
		// Erreur : mauvaise demande de jour
		break;
	}  //----- Fin de switch ( d7 )

	for ( int i = 0; i < jour->GetTaille(); i++ )
	{
		// Recherche de l'horaire
		if ( (*jour)[i].GetHeure() == heure && (*jour)[i].GetMinute() == minute )
		{
			switch ( (*jour)[i].GetTrafic() )
			{
			case V:
				tempsParcours += 1;
				break;
			case J:
				tempsParcours += 2;
				break;
			case R:
				tempsParcours += 4;
				break;
			default:	// case N:
				tempsParcours += 10;
				break;
			}
			break;		// On a trouve, on sort de la boucle
		}

	}

	return tempsParcours;

} //----- Fin de TempsSegment

//------------------------------------------------- Surcharge d'opérateurs
Capteur &Capteur::operator = ( const Capteur &unCapteur )
// Algorithme :
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

	// Utilisation de la surcharge de = pour Vecteur
	d1Contenu = unCapteur.d1Contenu;
	d2Contenu = unCapteur.d2Contenu;
	d3Contenu = unCapteur.d3Contenu;
	d4Contenu = unCapteur.d4Contenu;
	d5Contenu = unCapteur.d5Contenu;
	d6Contenu = unCapteur.d6Contenu;
	d7Contenu = unCapteur.d7Contenu;

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
	
	// Utilisation de la surcharge de = pour Vecteur
	d1Contenu = unCapteur.d1Contenu;
	d2Contenu = unCapteur.d2Contenu;
	d3Contenu = unCapteur.d3Contenu;
	d4Contenu = unCapteur.d4Contenu;
	d5Contenu = unCapteur.d5Contenu;
	d6Contenu = unCapteur.d6Contenu;
	d7Contenu = unCapteur.d7Contenu;

} //----- Fin de Capteur (constructeur de copie)

Capteur::Capteur( int id ) :
	d1Contenu(), d2Contenu(), d3Contenu(), d4Contenu(), d5Contenu(), d6Contenu(), d7Contenu(),
	identifiant(id)
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
