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
// Algorithme :
// Complexité : O(n), avec n le nombre de capteurs de la ville
// TODO: un for de taille 4 est-il + ou - long que de faire les 4 opérations inline ? je dirais +, mais de combien ?
// A noter que l'affichage prend beacoup de temps!
// Note :   La table de hachage n'ameliore pas la complexité à chaque fois qu'on veut parcourir tous les capteurs
//          on n'aura donc pas d'amelioration de complexité sur cette méthode
{
	// Creation de la structure de retour et variables pratiques
	Vecteur<double> statsRetour;
	int total = 0;
    int nombreCapteurs = listeId.GetTaille();
    Capteur* capteur = nullptr;
	// Init de la structure d'affichage
	for ( int i = 0; i < 4; i++ )
	{
		statsRetour.insererFin(0);
	}

	// Parcours du tableau de capteurs et remplissage de la structure de retour
	for ( int i = 0; i < nombreCapteurs; i++ )
	{
	    capteur = tableDeHachage.GetCapteur(listeId[i]);
		for (int j = 0; j < 4; j++)
		{
			statsRetour[j] += (capteur->DonneesJour(d7))[j];	// TODO: plus rapide a l'execution si on stocke dans une variable ou pas ?
		}
		total += (capteurs->DonneesJour(d7))[4];
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
// Note :   La table de hachage n'ameliore pas la complexité à chaque fois qu'on veut parcourir tous les capteurs
//          on n'aura donc pas d'amelioration de complexité sur cette méthode
{
	// Création structure pour affichage et variables pratiques
	Vecteur<double> stats;
	Vecteur<int> total;
	Vecteur<int> statsCapteur;
	int nombreCapteurs = listeId.GetTaille();

	// Init de la structure d'affichage
	for ( int i = 0; i < 24; i++ )
	{
		stats.insererFin(0);
		total.insererFin(0);
	}

	// Remplissage de la structure d'affichage
	for ( int i = 0; i < nombreCapteurs; i++ )
	{
        statsCapteur = this[i]->EmbouteillageJour( d7 )
		for ( int j = 0; j < 24; j++ )
		{
			stats[j] += statsCapteur[j];	// TODO: plus rapide a l'execution si on stocke dans une variable ou pas ?
			total[j] += statsCapteur[j + 24];
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
	//Vecteur<Capteur*> capteursSegment;

	// Init variables
	temps = 0;
	meilleurTemps = 0;
	meilleureHeure = 0;
	meilleureMinute = 0;
/*
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
*/
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
				int tempsAdditionnel = this[idSegments[i]]->TempsSegment(jourActuel, heureActuelle, minuteActuelle);
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
// Complexité : O(1) Grace à la table de Hachage
{

    Capteur* capteur = nullptr;
    capteur = tableDeHachage.GetCapteur(id);
    if ( capteur != nullptr )
    {
        capteur->inserer( evenement );
    }
    else//si le capteur n'existe pas
    {
        CreerCapteur( id );//on le crée
        capteur = tableDeHachage.GetCapteur( id );//on est donc sur qu'il existe maintenant
        capteur->inserer( evenement );
    }
	return;

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
// Complexité : O(1) Grace à la table de Hachage
{
	return tableDeHachage.GetCapteur( idCapteur );

} //----- Fin de operator []

Capteur & Ville::operator[] ( int idCapteur ) const
// Algorithme :
{
	return tableDeHachage.GetCapteur( idCapteur );

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


Ville::Ville () :
// Algorithme :
{
#ifdef MAP
	cout << "Appel au constructeur de <Ville>" << endl;
#endif
    tableDeHachage = new TableHachage( NB_PREMIER_BASE, NB_PREMIER_BASE );//Il n'est pas necessaire ici de faire une taille différente du nombre premier
	listeId = new vecteur<int>;
} //----- Fin de Ville


Ville::~Ville ()
// Algorithme :
{
#ifdef MAP
	cout << "Appel au destructeur de <Ville>" << endl;
#endif
	delete tableDeHachage;
	delete [] listeId;
} //----- Fin de ~Ville


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Ville::CreerCapteur( int id )
// Algorithme : allocation dynamique d'un nouveau capteur et "insertion" dans le tableau
{
	// La verification de l'existence du capteur a été traitée avant l'appel à cette fonction
	Capteur* capteur = new Capteur( id );
	tableDeHachage.Inserer( capteur );
    listeId.insererFin( id );
} //----- Fin de creerCapteur

//------------------------------------------------------- Méthodes privées
