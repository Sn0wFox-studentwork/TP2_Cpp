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
// Complexit� : O(n), avec n le nombre de capteurs de la ville
// TODO: un for de taille 4 est-il + ou - long que de faire les 4 op�rations inline ? je dirais +, mais de combien ?
// A noter que l'affichage prend beacoup de temps!
// Note :   La table de hachage n'ameliore pas la complexit� � chaque fois qu'on veut parcourir tous les capteurs
//          on n'aura donc pas d'amelioration de complexit� sur cette m�thode
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
// Complexit� : O(n*m), avec un for de taille 24 dans un for de taille n = nombre de capteurs de la ville
//				m est le nombre d'�v�nements dans le vecteur du jour dans EmbouteillageJour( d7 )
// Note :   La table de hachage n'ameliore pas la complexit� � chaque fois qu'on veut parcourir tous les capteurs
//          on n'aura donc pas d'amelioration de complexit� sur cette m�thode
{
	// Cr�ation structure pour affichage et variables pratiques
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
//		 � adapter pour Capteur::TempsSgement2
void Ville::TempsParcours ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments )
// Algorithme :
// Complexite : O(nbH*nbSegments*60*nbEvent)... A ameliorer sans doute
// TODO: pour le moment , non-prise en compte des endroits sans donn�es
// TODO: et si on part dimanche � 23H ?
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
// Complexit� : O(1) Grace � la table de Hachage
{

    Capteur* capteur = nullptr;
    capteur = tableDeHachage.GetCapteur(id);
    if ( capteur != nullptr )
    {
        capteur->inserer( evenement );
    }
    else//si le capteur n'existe pas
    {
        CreerCapteur( id );//on le cr�e
        capteur = tableDeHachage.GetCapteur( id );//on est donc sur qu'il existe maintenant
        capteur->inserer( evenement );
    }
	return;

} //----- Fin de AjouterEvenement

//------------------------------------------------- Surcharge d'op�rateurs
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
// Complexit� : O(1) Grace � la table de Hachage
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
    tableDeHachage = new TableHachage( NB_PREMIER_BASE, NB_PREMIER_BASE );//Il n'est pas necessaire ici de faire une taille diff�rente du nombre premier
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
