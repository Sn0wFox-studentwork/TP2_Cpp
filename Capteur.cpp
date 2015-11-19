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
//#define MAP	// Permet de visualiser les appels aux constructeurs/destructeurs et certains éléments de debugging

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Capteur::Inserer ( Evenement& unEvenement )
// Algorithme :	On détermine quel tableau de semaineResume incrémenter en se basant sur le jour, l'heure et la minute
//				de unEvenement.
//				On détermine quelle tableau de résumé journalié modifier grâce au jour de unEvenement.
//				On incrémente la bonne case de chacun des deux tableaux déterminés précédement grâce au Trafic
//				de unEvenement, sans oublier la case représentant le nombre total d'Evenement (4) pour un jour donné.
// Complexité : O(1)
{
	// Variables permettant de positionner l'insertion
	int indice = ( (unEvenement.GetD7( ) - 1) * HEURE_PAR_JOUR + unEvenement.GetHeure( ) ) * MIN_PAR_HEURE + unEvenement.GetMinute( );
	int * jourTab = nullptr;

	// Détermination du tableau de résumé journalié dans lequel prendre les données
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

	// Incrémentation du nombre total d'Evenement
	jourTab[4]++;

} //----- Fin de Inserer

Vecteur<double> Capteur::StatsPropres()
// Algorithme :	On calcul le total d'Evenement que le Capteur courant a enregistré en sommant les valeurs
//				des cases d'indice 4 des résumés journaliés.
//				Si ce total est différent de 0, on divise alors le nombre d'occurence de chaque état du trafic
//				(V, J, R ou N) par ce total, et on l'insère dans la structure de retour statsRetour.
//				On retourne le Vecteur<double> de taille 4 statsRetour qui contient les statistiques
//				comprise entre 0 et 1 (0 partout si le total vaut 0).
// Complexité : O(1)
{
	// Creation de la structure de retour et variables pratiques
	Vecteur<double> statsRetour;
	double total =	d1Resume[4] + d2Resume[4] + d3Resume[4] + d4Resume[4] +
					d5Resume[4] + d6Resume[4] + d7Resume[4];
	double statTrafic = 0;

	// Remplissage
	for ( int i = 0; i < TAILLE_RESUME - 1; i++ )
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
		statsRetour.InsererFin(statTrafic);
	}
	
	return statsRetour;

} //----- Fin de StatsPropres

int Capteur::TempsSegment ( int d7, int heure, int minute )
// Algorithme :	On detérmine dans quelle case prendre les données en se basant sur la construction même
//				de la structure semaineResume.
//				On détermine quel Trafic est le plus probable en prenant celui qui est apparu le plus grand
//				nombre de fois. En cas d'égalité, c'est le trafic le plus perturbé qui sera comptabilisé.
//				Ceci implique que les INSTANTS SANS DONNES seront compté comme ayant un Trafic NOIR (N).
//				On retourne le temps de parcours le plus probable défini en fonction de la valeur du Trafic précédent.
// Complexité : O(1)
{
	// Création variables pratiques
	int nombreTrafic = 0;
	int traficLePlusProbable = 0;
	int indice = ((d7 - 1) * HEURE_PAR_JOUR + heure) * MIN_PAR_HEURE + minute;

	for ( int i = 0; i < NB_STATS; i++ )
	{
		if ( semaineResume[indice][i] >= nombreTrafic )	// >= fait prendre le trafic avec le plus long temps de parcours en cas d'égalité
		{												// ceci se traduit par un trafic N pour les endroits sans données (égalité avec 0 partout)
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
// Algorithme :	Si on n'est pas en train de faire unCapteur = unCapteur,
//				on libère la mémoire des données actuelles,
//				puis on "copie" tout les champs :
//				on les modifie pour qu'ils soient comme ceux de unCapteur.
//				On retourne *this pour la bonne marche de la surcharge d'operateur.
// A noter :	Pas d'allocation dynamique ici. A priori, nul besoin de dupliquer le(s) capteur(s)
//				pointé(s) par suivant.
{
#ifdef MAP
	cout << "Operator = de <Capteur>" << endl;
#endif
	if ( this != &unCapteur )
	{
		// Pas d'opération "delete suivant" car a priori suivant n'a pas forcément été alloué dynamiquement.

		// Réallocation de la chaîne
		suivant = nullptr;
		Capteur* cSuiv = unCapteur.GetSuivant( );
		while ( cSuiv )
		{
			cout << "Here !" << endl;
			suivant = cSuiv;
			cSuiv = cSuiv->GetSuivant( );
			suivant = suivant->GetSuivant( );
			// suivant vaut déjà nullptr ici.
		}

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

		for ( int m = 0; m < MIN_PAR_SEMAINE; m++ )
		{
			for ( int j = 0; j < NB_STATS; j++ )
			{
				semaineResume[m][j] = unCapteur.semaineResume[m][j];
			}
		}
	}

	return  *this;

} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Capteur::Capteur ( const Capteur &unCapteur ) : identifiant( unCapteur.identifiant ), suivant( unCapteur.suivant )
// Algorithme :	Initialisation des attributs à partir de ceux de unCapteur,
//				puis recopie des données des dXResume et semaineResume à partir de celles de unCapteur.
//				Attention, on se retrouve alors avec deux capteurs ayant le même identifiant.
//				Etant donné la manière dont sont gérés les id (à cause du cahier des charges qui force à
//				faire confiance à l'utilisateur sur l'id lors de l'insertion de données), ce n'est pas grave.
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Capteur>" << endl;
#endif
	
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

Capteur::Capteur( int id ) : identifiant( id ), suivant( nullptr )
// Algorithme :	Construit une instance de Capteur, d'idendifiant id.
//				Le pointeur suivant est initialisé comme un nullptr (ne pointe vers rien).
//				On initialise ensuite toutes les statistiques à 0 pour éviter des comportements indéfinis.
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


Capteur::~Capteur ( )
// Algorithme :	Détruit une instance de Capteur et libère la mémoire occupée par le pointeur suivant
//				(ne pose pas de problème si le pointeur est null).
//				TODO: (?) Ceci appel donc le destructeur pour le Capteur pointé par suivant qui fonctionne
//				de la même manière. Ce destructeur détruit donc toute la liste chaînée éventuelle présente
//				dans une case d'une TableHachage, de manière récursive.
//				Ceci ne pose pas de problème ici puisque les destructeurs ne seront appelés qu'à la fin de l'application.
{
#ifdef MAP
	cout << "Appel au destructeur de <Capteur>" << endl;
#endif

	// NB:	on ne fait pas d'opération "delete suivant;" car a priori le capteur pointé par suivant n'a
	//		pas forcément été alloué dynamiquement.
	//		Il le sera en revanche dans TableHachage : se sera au destructeur de TableHachage de gérer la désallocation.

} //----- Fin de ~Capteur
