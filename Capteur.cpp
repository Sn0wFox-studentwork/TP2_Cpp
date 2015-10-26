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
{
	// Creation de la structure de retour et variables pratiques
	Vecteur<double> statsRetour;
	double total =	d1Resume[4] + d2Resume[4] + d3Resume[4] + d4Resume[4] +
					d5Resume[4] + d6Resume[4] + d7Resume[4];

	// Remplissage
	if ( total != 0 )
	{
		statsRetour.insererFin( ( d1Resume[0] + d2Resume[0] + d3Resume[0]
			+ d4Resume[0] + d5Resume[0] + d6Resume[0] + d7Resume[0]) / total );		// Lundi
		statsRetour.insererFin( ( d1Resume[1] + d2Resume[1] + d3Resume[1]
			+ d4Resume[1] + d5Resume[1] + d6Resume[1] + d7Resume[1]) / total );		// Mardi
		statsRetour.insererFin( ( d1Resume[2] + d2Resume[2] + d3Resume[2]
			+ d4Resume[2] + d5Resume[2] + d6Resume[2] + d7Resume[2]) / total );		// Mercredi
		statsRetour.insererFin( ( d1Resume[3] + d2Resume[3] + d3Resume[3]
			+ d4Resume[3] + d5Resume[3] + d6Resume[3] + d7Resume[3]) / total );		// Jeudi
		statsRetour.insererFin( ( d1Resume[4] + d2Resume[4] + d3Resume[4]
			+ d4Resume[4] + d5Resume[4] + d6Resume[4] + d7Resume[4]) / total );		// Vendredi
		statsRetour.insererFin( ( d1Resume[5] + d2Resume[5] + d3Resume[5]
			+ d4Resume[5] + d5Resume[5] + d6Resume[5] + d7Resume[5]) / total );		// Samedi
		statsRetour.insererFin( ( d1Resume[6] + d2Resume[6] + d3Resume[6]
			+ d4Resume[6] + d5Resume[6] + d6Resume[6] + d7Resume[6]) / total );		// Dimanche
	}

	return statsRetour;

} //----- Fin de StatsPropres

Vecteur<double> Capteur::StatsJour(int d7)
// Algorithme :
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
	statsRetour.insererFin( jourTab[0] / total );
	statsRetour.insererFin( jourTab[1] / total );
	statsRetour.insererFin( jourTab[2] / total );
	statsRetour.insererFin( jourTab[3] / total );

	return statsRetour;

} //----- Fin de StatsJour

Vecteur<int> Capteur::DonneesJour(int d7)
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
	donneesRetour.insererFin( jourTab[0] );
	donneesRetour.insererFin( jourTab[1] );
	donneesRetour.insererFin( jourTab[2] );
	donneesRetour.insererFin( jourTab[3] );
	donneesRetour.insererFin( jourTab[4] );

	return donneesRetour;

}  //----- Fin de DonneesJour

Vecteur<int> Capteur::EmbouteillageJour( int d7 )
// Algorithme :
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
		//total.insererFin(0);
	}

	// Parcours du tableau d'événements et remplissage de la structure de retour
	for (int i = 0; i < jour->GetTaille(); i++)
	{
		trafic = (*jour)[i].GetTrafic();
		if ( trafic == R || trafic == N )
		{
			donneesRetour[(*jour)[i].GetHeure()] += 1;
		}
		donneesRetour[(*jour)[i].GetHeure() + 24] += 1;
		//total[(*jour)[i].GetHeure()] += 1;				// TODO: plus rapide avec creation de variable ?
	}

	/*for (int i = 0; i < statsRetour.GetTaille(); i++)
	{
		if ( total[i] != 0 )
		{
			statsRetour[i] /= total[i];
		}
	}*/

	return donneesRetour;

} //----- Fin de EmbouteillageJour

int Capteur::TempsSegment( int d7, int heure, int minute )
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
