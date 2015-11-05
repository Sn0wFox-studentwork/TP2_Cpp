/*************************************************************************
Ville  -  description
-------------------
d�but                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- R�alisation de la classe <Ville> (fichier Ville.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Ville.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types priv�s


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- M�thodes publiques
// type Ville::M�thode ( liste de param�tres )
// Algorithme :
//
//{
//} //----- Fin de M�thode


void Ville::StatsJour( int d7 )
// Algorithme :
// Complexit� : O(1) (1440 it�rations � chaque fois)
// A noter que l'affichage prend beacoup de temps!
{
	// Cr�ation structure pour affichage et variables pratiques
	int total = 0;
	int nbVert = 0;
	int nbJaune = 0;
	int nbRouge = 0;
	int nbNoir = 0;
	int minuteInitiale = (d7 - 1) * HEURE_PAR_JOUR * MIN_PAR_HEURE;
	int minuteMax = d7 * HEURE_PAR_JOUR * MIN_PAR_HEURE;
	double stats[NB_STATS];

	for (int minute = minuteInitiale; minute < minuteMax; minute++)
	{
		nbVert += semaineResume[minute][0];
		nbJaune += semaineResume[minute][1];
		nbRouge += semaineResume[minute][2];
		nbNoir += semaineResume[minute][3];
	}
	total = nbVert + nbJaune + nbRouge + nbNoir;

	// Cr�ation des statistiques
	if ( total == 0 )
	{
		for ( int i = 0; i < NB_STATS; i++ )
		{
			stats[i] = 0;
		}
	}
	else
	{
		stats[0] = (double)nbVert / total;
		stats[1] = (double)nbJaune / total;
		stats[2] = (double)nbRouge / total;
		stats[3] = (double)nbNoir / total;
	}

	// Affichage
	cout << "V " << stats[0] * 100 << "%\r\n";	// TODO: quelle tronche a la fin de ligne ?
	cout << "J " << stats[1] * 100 << "%\r\n";
	cout << "R " << stats[2] * 100 << "%\r\n";
	cout << "N " << stats[3] * 100 << "%\r\n";

} //----- Fin de statsJour

void Ville::EmbouteillageJour( int d7 )
// Algorithme :
// Complexit� : O(1) (1440 it�rations � chaque fois)
{
	// Cr�ation structure pour affichage et variables pratiques
	int total[HEURE_PAR_JOUR];
	int nbEmbouteillage[HEURE_PAR_JOUR];
	double stats[HEURE_PAR_JOUR];
	int heureInitiale = (d7 - 1) * HEURE_PAR_JOUR;
	int heureMax = d7 * HEURE_PAR_JOUR;	

	// Init de la structure d'affichage
	for ( int i = 0; i < HEURE_PAR_JOUR; i++ )
	{
		nbEmbouteillage[i] = 0;
		total[i] = 0;
		stats[i] = 0;
	}

	// Prise des donn�es
	for (int h = heureInitiale; h < heureMax; h++)
	{
		for (int minute = 0; minute < MIN_PAR_HEURE; minute++)
		{
			total[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][0];
			total[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][1];
			nbEmbouteillage[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][2];
			nbEmbouteillage[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][3];
		}
		total[h - heureInitiale] += nbEmbouteillage[h - heureInitiale];
	}

	// Creation des stats et affichage
	for ( int i = 0; i < 24; i++ )
	{
		if ( total[i] != 0 )
		{
			stats[i] = (double)nbEmbouteillage[i] / total[i];
		}
		// Affichage
		cout << d7 << " " << i << " " << stats[i] * 100 << "%\r\n";		// TODO: quelle tronche a la fin de ligne ?
	}

} //----- Fin de EmbouteillageJour

// TODO: void Ville::TempsParcours2 ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments )
//		 � adapter pour Capteur::TempsSgement2
void Ville::TempsParcours ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments )
// Algorithme :
// Complexite : O(nbH*nbSegments*60*nbEvent)... Le seul sur lequel on peut jouer est nbEvent
// TODO: pour le moment , non-prise en compte des endroits sans donn�es
{
	// Cr�ation variables pour affichage et variables pratiques
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
	// Prise une fois pour toutes des capteurs qui nous int�ressent
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

			temps = 0;	// Remise � jour pour calcul du temps lors du d�part � heure:minuteActuelle
			minuteActuelle = minute;
			heureActuelle = heure;
			for (int i = 0; i < idSegments.GetTaille(); i++)
			{
				int tempsAdditionnel = (*this)[idSegments[i]].TempsSegment(jourActuel, heureActuelle, minuteActuelle);
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
// Complexit� : O(1) Grace � la table de Hachage, s'il n'y a pas de collisions
{

    Capteur* capteur = nullptr;
	cout << capteur << ends;
    capteur = tableDeHachage.GetCapteur(id);
	cout << capteur << endl;

    if ( capteur != nullptr )
    {
        capteur->Inserer( evenement );
    }
    else	//si le capteur n'existe pas
    {
        CreerCapteur( id );							//on le cr�e
        capteur = tableDeHachage.GetCapteur( id );	//on est donc sur qu'il existe maintenant
        capteur->Inserer( evenement );
    }

	int posStat = 0;
	int numMinute = ( ( evenement.GetD7( ) - 1 ) * HEURE_PAR_JOUR + evenement.GetHeure( ) ) * MIN_PAR_HEURE + evenement.GetMinute( );
	switch (evenement.GetTrafic( ))
	{
	case V:
		posStat = 0;
		break;
	case J:
		posStat = 1;
		break;
	case R:
		posStat = 2;
		break;
	default:	// case N:
		posStat = 3;
		break;
	}

	cout << numMinute << endl;
	semaineResume[numMinute][posStat]++;

} //----- Fin de AjouterEvenement

//------------------------------------------------- Surcharge d'op�rateurs
Ville &Ville::operator = ( const Ville &uneVille )
// Algorithme :
{
	nombreCapteurs = uneVille.nombreCapteurs;
	for (int i = 0; i < nombreCapteurs; i++)
	{
		tableDeHachage[listeId[i]] = new Capteur(*uneVille.tableDeHachage[listeId[i]]);
	}

	return *this;

} //----- Fin de operator =


Capteur& Ville::operator[] ( int idCapteur )
// Algorithme :
// Complexit� : O(1) Grace � la table de Hachage
{
	return *tableDeHachage[idCapteur];

} //----- Fin de operator []

Capteur & Ville::operator[] ( int idCapteur ) const
// Algorithme :
{
	return *tableDeHachage[idCapteur];

} //----- Fin de operator [] const


//-------------------------------------------- Constructeurs - destructeur
Ville::Ville ( const Ville &uneVille ) :	tableDeHachage( uneVille.tableDeHachage ),
											nombreCapteurs( uneVille.nombreCapteurs ), listeId( uneVille.listeId )
// Algorithme :
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Ville>" << endl;
#endif

} //----- Fin de Ville (constructeur de copie)


Ville::Ville () :	tableDeHachage( NB_MAX_CAPTEURS, NB_PREMIER_BASE ),
					nombreCapteurs( NB_MAX_CAPTEURS ), listeId()
// Algorithme :
// NB: Il EST necessaire ici de faire une taille diff�rente du nombre premier pour �viter les collisions
{
#ifdef MAP
	cout << "Appel au constructeur de <Ville>" << endl;
#endif

	// Initialisation du r�sum� hebdomadaire
	for (int minute = 0; minute < NB_MIN_PAR_SEMAINE; minute++)
	{
		for (int numStat = 0; numStat < NB_STATS; numStat++)
		{
			semaineResume[minute][numStat] = 0;
		}
	}

} //----- Fin de Ville


Ville::~Ville ()
// Algorithme :
{
#ifdef MAP
	cout << "Appel au destructeur de <Ville>" << endl;
#endif

} //----- Fin de ~Ville


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es
void Ville::CreerCapteur( int id )
// Algorithme : allocation dynamique d'un nouveau capteur et "insertion" dans le tableau
{
	// La verification de l'existence du capteur a �t� trait�e avant l'appel � cette fonction
	Capteur* capteur = new Capteur( id );
	tableDeHachage.Inserer( capteur );
    listeId.insererFin( id );

} //----- Fin de creerCapteur

//------------------------------------------------------- M�thodes priv�es
