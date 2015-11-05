/*************************************************************************
Ville  -  description
-------------------
début                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Réalisation de la classe <Ville> (fichier Ville.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Ville.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type Ville::Méthode ( liste de paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


void Ville::StatsJour( int d7 )
// ALgorithme :
// Complexité : O(n), avec n le nombre de capteurs de la ville
// TODO: un for de taille 4 est-il + ou - long que de faire les 4 opérations inline ? je dirais +, mais de combien ?
// A noter que l'affichage prend beacoup de temps!
{
	// Creation de la structure de retour et variables pratiques
	Vecteur<double> statsRetour;
	int total = 0;

	// Init de la structure d'affichage
	for ( int i = 0; i < 4; i++ )
	{
		statsRetour.insererFin(0);
	}

	// Parcours du tableau de capteurs et remplissage de la structure de retour
	for ( int i = 0; i < nombreCapteurs; i++ )
	{
		for (int j = 0; j < 4; j++)
		{
			statsRetour[j] += (capteurs[i]->DonneesJour(d7))[j];	// TODO: plus rapide a l'execution si on stocke dans une variable ou pas ?
		}
		total += (capteurs[i]->DonneesJour(d7))[4];
	}

	// Creation des stats
	if ( total != 0 )
	{
		for ( int i = 0; i < 4; i++ )
		{
			statsRetour[i] /= total;
		}
	}

	// Affichage
	cout << "V " << statsRetour[0] * 100 << "%\r\n";	// TODO: quelle tronche a la fin de ligne ?
	cout << "J " << statsRetour[1] * 100 << "%\r\n";
	cout << "R " << statsRetour[2] * 100 << "%\r\n";
	cout << "N " << statsRetour[3] * 100 << "%\r\n";

} //----- Fin de statsJour

void Ville::EmbouteillageJour( int d7 )
// Algorithme :
// Complexité : O(n*m), avec un for de taille 24 dans un for de taille n = nombre de capteurs de la ville
//				m est le nombre d'évènements dans le vecteur du jour dans EmbouteillageJour( d7 )
{
	// Création structure pour affichage et variables pratiques
	Vecteur<double> stats;
	Vecteur<int> total;
	
	// Init de la structure d'affichage
	for ( int i = 0; i < 24; i++ )
	{
		stats.insererFin(0);
		total.insererFin(0);
	}

	// Remplissage de la structure d'affichage
	for (int i = 0; i < nombreCapteurs; i++)
	{
		for ( int j = 0; j < 24; j++ )
		{
			stats[j] += (capteurs[i]->EmbouteillageJour(d7))[j];	// TODO: plus rapide a l'execution si on stocke dans une variable ou pas ?
			total[j] += (capteurs[i]->EmbouteillageJour(d7))[j + 24];
		}
	}

	// Creation des stats et affichage
	for ( int i = 0; i < 24; i++ )
	{
		if ( total[i] != 0 )
		{
			stats[i] /= total[i];
		}
		// Affichage
		cout << d7 << " " << i << " " << stats[i] * 100 << "%\r\n";		// TODO: quelle tronche a la fin de ligne ?
	}

} //----- Fin de EmbouteillageJour

// TODO: void Ville::TempsParcours2 ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments )
//		 à adapter pour Capteur::TempsSgement2
void Ville::TempsParcours ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments )
// Algorithme :
// Complexite : O(nbH*nbSegments*60*nbEvent)... A ameliorer sans doute
// TODO: pour le moment , non-prise en compte des endroits sans données
// TODO: et si on part dimanche à 23H ?
{
	// Création variables pour affichage et variables pratiques
	int temps;
	int meilleurTemps;
	int meilleureMinute;
	int meilleureHeure;
	int meilleurJour;
	int nombreMinutes = (hFin - hDebut + 1) * 60;
	int heureActuelle = hDebut;
	int minuteActuelle = 0;
	int jourActuel = d7;
	Vecteur<Capteur*> capteursSegment;

	// Init variables
	temps = 0;
	meilleurTemps = 0;
	meilleureHeure = 0;
	meilleureMinute = 0;

	// Prise une fois pour toutes des capteurs qui nous intéressent
	for ( int i = 0; i < idSegments.GetTaille(); i++ )
	{
		for ( int j = 0; j < nombreCapteurs; j++ )
		{
			if ( capteurs[j]->GetID() == idSegments[i] )
			{
				capteursSegment.insererFin(capteurs[j]);
				break;
			}
		}
	}

	// Recherche du meilleur temps
	for ( int heure = hDebut; heure <= hFin; heure++ )
	{
		for ( int minute = 0; minute < 60; minute++ )
		{

			temps = 0;	// Remise à jour pour calcul du temps lors du départ à heure:minuteActuelle
			minuteActuelle = minute;
			heureActuelle = heure;
			for (int i = 0; i < idSegments.GetTaille(); i++)
			{
				int tempsAdditionnel = capteursSegment[i]->TempsSegment(jourActuel, heureActuelle, minuteActuelle);
				temps += tempsAdditionnel;
				minuteActuelle += tempsAdditionnel;
				if ( minuteActuelle >= 60 )
				{
					heureActuelle++;
					minuteActuelle %= 60;
					if ( heureActuelle >= 24 )
					{
						jourActuel++;
						if ( jourActuel == 8 )
						{
							jourActuel = 1;
						}
						heureActuelle %= 24;
					}
				}

			}
			// En cas de nouveau meilleur temps : mise a jour
			if ( (temps < meilleurTemps || meilleurTemps == 0) && temps > 0 )
			{
				meilleurTemps = temps;
				meilleureHeure = heure;
				meilleureMinute = minute;
			}
		}
	} //----- Fin de for ( heure ) ; recherche du meilleur temps

	// Affichage
	cout << d7 << " " << meilleureHeure << " " << meilleureMinute << " " << meilleurTemps << "\r\n";	// TODO: quelle tronche a la fin de ligne ?

} //----- Fin de TempsParcours

void Ville::AjouterEvenement( int id, Evenement& evenement )
// Algorithme :
// Complexité : O(n), avec n le nombre de capteur de la ville
// TODO: complexité améliorable en triant le tableau
{
	for ( int i = 0; i < nombreCapteurs; i++ )
	{
		if (capteurs[i]->GetID() == id)
		{
			capteurs[i]->Inserer( evenement );
			return;
		}
	}

	CreerCapteur( id );
	capteurs[nombreCapteurs - 1]->Inserer( evenement );

} //----- Fin de AjouterEvenement

//------------------------------------------------- Surcharge d'opérateurs
Ville &Ville::operator = ( const Ville &uneVille )
// Algorithme :
{
	nombreCapteurs = uneVille.nombreCapteurs;
	for (int i = 0; i < nombreCapteurs; i++)
	{
		capteurs[i] = new Capteur(*uneVille.capteurs[i]);
	}

	return *this;

} //----- Fin de operator =


Capteur& Ville::operator[] ( int idCapteur )
// Algorithme :
// Complexité : O(n), avec break dès qu'on a trouvé
// TODO: complexité améliorable en O(log2(n)) si tableau trié
{
	for (int i = 0; i < nombreCapteurs; i++)
	{
		if ( capteurs[i]->GetID() == idCapteur )
		{
			return *capteurs[i];
		}
	}
	cout << "Error, attempted to access an inexistant element" << endl;
	return *capteurs[0];	// Retour du premier élément pour que le programme ne plante pas

} //----- Fin de operator []

Capteur & Ville::operator[] ( int idCapteur ) const
// Algorithme :
{
	for (int i = 0; i < nombreCapteurs; i++)
	{
		if (capteurs[i]->GetID() == idCapteur)
		{
			return *capteurs[i];
		}
	}
	cout << "Error, attempted to access an inexistant element" << endl;
	return *capteurs[0];	// Retour du premier élément pour que le programme ne plante pas

} //----- Fin de operator [] const


//-------------------------------------------- Constructeurs - destructeur
Ville::Ville ( const Ville &uneVille )
// Algorithme :
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Ville>" << endl;
#endif

	nombreCapteurs = uneVille.nombreCapteurs;
	for ( int i = 0; i < nombreCapteurs; i++ )
	{
		capteurs[i] = new Capteur(*uneVille.capteurs[i]);
	}

} //----- Fin de Ville (constructeur de copie)


Ville::Ville () : nombreCapteurs(0)
// Algorithme :
{
#ifdef MAP
	cout << "Appel au constructeur de <Ville>" << endl;
#endif
	//Rien de plus a faire a priori
} //----- Fin de Ville


Ville::~Ville ()
// Algorithme :
{
#ifdef MAP
	cout << "Appel au destructeur de <Ville>" << endl;
#endif
	for ( int i = 0; i < nombreCapteurs; i++ )
	{
		delete capteurs[i];
	}
} //----- Fin de ~Ville


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Ville::CreerCapteur( int id )
// Algorithme : allocation dynamique d'un nouveau capteur et "insertion" dans le tableau
{
	// La verification de l'existence du capteur a été traitée avant l'appel à cette fonction
	Capteur* capteur = new Capteur( id );
	capteurs[nombreCapteurs++] = capteur;

} //----- Fin de creerCapteur

//------------------------------------------------------- Méthodes privées
