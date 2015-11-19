/*************************************************************************
main  -  contient le point d'entrée de l'application
-------------------
début                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Réalisation du main (fichier main.cpp) ----------------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <string>
#include <ctime>

//------------------------------------------------------ Include personnel
#include "Ville.h"

//----------------------------------------------------------- Types privés
typedef Vecteur<int> Vint;


int main( int argc, char* argv[] )
// Algorithme :	On lit mot à mot ce qui arrive par l'entrée du programme et on le stocke dans une
//				variable de type string.
//				Tant qu'on ne lit pas la commande "EXIT", on lit en boucle jusqu'à tomber sur l'une
//				des en-têtes de commandes utilisables dans cette application (ADD, NB_STATS_C, NB_STATS_D7,
//				JAM_DH, OPT).
//				Lorsqu'on arrive sur l'une d'entre elle, on suppose que l'utilisateur va envoyer par la suite
//				les bons paramètres permettant d'exécuter une méthode affichant les statistiques voulues,
//				ajoutant un Evenement ou calculant un instant de départ optimal.
//				En effet, nous sommes en présence d'une application fonctionnant par saisie formatée. Il est donc
//				du devoir de l'utilisateur de ne pas envoyer des commandes érronées.
//				Lorsquela commande rentrée est correcte, on l'exécute puis on continu à lire pour arriver à une
//				nouvelle commande.
//				L'application se ferme lorsqu'on arrive sur la commande "EXIT".
{

	Ville v;

	string lecture;
	cin >> lecture;

	while ( lecture != "EXIT" )
	{
		if ( lecture == "ADD" )
		{
			// Code cmd1 ADD
			int id;
			int annee;
			int mois;
			int jour;
			int heure;
			int minute;
			int d7;
			char traf;
			Trafic trafic;

			cin >> id;
			cin >> annee;
			cin >> mois;
			cin >> jour;
			cin >> heure;
			cin >> minute;
			cin >> d7;
			cin >> traf;
			
			switch ( traf )
			{
			case 'V':
				trafic = V;
				break;
			case 'J':
				trafic = J;
				break;
			case 'R':
				trafic = R;
				break;
			case 'N':
				trafic = N;
				break;
			default:
				// Erreur lors du chargement de trafic
				break;
			}

			Temps temps( d7, annee, mois, jour, heure, minute );
			Evenement evenement( trafic, temps );
			
			v.AjouterEvenement( id, evenement );

		}
		else if ( lecture == "STATS_C" )
		{
			// Code cmd2 STATS_C
			int idCapteur;
			cin >> idCapteur;
			Vecteur<double> stats;

			// On vérifie que le capteur d'identifiant idCapteur existe
			if ( v[idCapteur] )
			{
				stats = v[idCapteur]->StatsPropres();	// Si c'est le cas, on calcul ses statistiques
			}
			else
			{
				for ( int i = 0; i < NB_STATS; i++ )	// Sinon, on considère que nous n'avons pas de données
				{
					stats.InsererFin( 0 );				// On crée donc des statistiques de 0%
				}
			}

			cout << "V " << stats[0] * 100 << "%\r\n";
			cout << "J " << stats[1] * 100 << "%\r\n";
			cout << "R " << stats[2] * 100 << "%\r\n";
			cout << "N " << stats[3] * 100 << "%\r\n";
			
		}
		else if ( lecture == "STATS_D7" )
		{
			// Code cmd3 STATS_D7
			int d7;
			cin >> d7;

			v.StatsJour( d7 );

		}
		else if ( lecture == "JAM_DH" )
		{
			// Code cmd4 JAM_DH
			int d7;
			cin >> d7;

			v.EmbouteillageJour( d7 );
			
		}
		else if ( lecture == "OPT" )
		{
			// Code cmd5 OPT
			int d7;
			int hDebut;
			int hFin;
			int nombreSegments;
			int idSegment;
			Vecteur<int> segments;

			cin >> d7;
			cin >> hDebut;
			cin >> hFin;
			cin >> nombreSegments;
			for ( int i = 0; i < nombreSegments; i++ )
			{
				cin >> idSegment;
				segments.InsererFin( idSegment );
			}

			v.TempsParcours( d7, hDebut, hFin, segments );

		}

		// clean de lecture non-necessaire
		cin >> lecture;		// Cette ligne de code fait aussi le nettoyage du buffer
							// jusqu'à la prochaine commande rencontrée

	} //----- Fin de while (exit)

	return 0;

} //----- Fin de main
