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


int main(int argc, char* argv[])
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
	
	v.AjouterEvenement(10011, Evenement(J, Temps(5, 1586, 5, 2, 5, 5)));	// Collision avec l'ID 4
	v.AjouterEvenement(2, Evenement(J, Temps(5, 1586, 5, 2, 5, 5)));
	v.AjouterEvenement(2, Evenement(R, Temps(5, 1586, 5, 2, 5, 6)));
	v.AjouterEvenement(2, Evenement(N, Temps(5, 1586, 5, 2, 5, 7)));
	v.AjouterEvenement(2, Evenement(V, Temps(5, 1586, 5, 2, 6, 8)));
	v.AjouterEvenement(1, Evenement(J, Temps(5, 1586, 5, 2, 5, 5)));
	v.AjouterEvenement(1, Evenement(R, Temps(5, 1586, 5, 2, 5, 6)));
	v.AjouterEvenement(1, Evenement(N, Temps(5, 1586, 5, 2, 5, 7)));
	v.AjouterEvenement(1, Evenement(V, Temps(5, 1586, 5, 2, 6, 8)));
	v.AjouterEvenement(4, Evenement(J, Temps(5, 1586, 5, 2, 5, 5)));
	v.AjouterEvenement(4, Evenement(R, Temps(5, 1586, 5, 2, 5, 6)));
	v.AjouterEvenement(4, Evenement(N, Temps(5, 1586, 5, 2, 5, 7)));
	v.AjouterEvenement(4, Evenement(V, Temps(5, 1586, 5, 2, 6, 8)));

	for (int i = 0; i < 1400000; i+=1000)
	{
		v.AjouterEvenement(i, Evenement(J, Temps(5, 1586, 5, 2, 5, 5)));
	}

	cout << v[1121000].GetSuivant( ) << endl;
	cout << v[4].GetSuivant( )->GetID() << endl;

	cout << v[4].TempsSegment(5, 5, 6) << endl;
	v.StatsJour(5);

	v.EmbouteillageJour(5);
	
	Vint s;
	s.insererFin(4);
	s.insererFin(2);
	s.insererFin(1);

	v.TempsParcours(5, 0, 23, s);

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

			/*Temps temps(annee, mois, jour, heure, minute, d7);
			Evenement evenement(temps, trafic);*/

			v.AjouterEvenement( id, Evenement(trafic, Temps( d7, annee, mois, jour, heure, minute ) ) );

		}
		else if ( lecture == "NB_STATS_C" )
		{
			// Code cmd2 NB_STATS_C
			int idCapteur;
			cin >> idCapteur;

			Vecteur<double> stats = v[idCapteur].StatsPropres();

			cout << "V " << stats[0] * 100 << "%\r\n";	// TODO: quelle tronche a la fin de ligne ?
			cout << "J " << stats[1] * 100 << "%\r\n";
			cout << "R " << stats[2] * 100 << "%\r\n";
			cout << "N " << stats[3] * 100 << "%\r\n";
			
		}
		else if ( lecture == "NB_STATS_D7" )
		{
			// Code cmd3 NB_STATS_D7
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
				segments.insererFin( idSegment );
			}

			v.TempsParcours( d7, hDebut, hFin, segments );

		}

		// clean de lecture non-necessaire
		cin >> lecture;		// Cette ligne de code fait aussi le nettoyage du buffer
							// jusqu'à la prochaine commande rencontrée

	} //----- Fin de while (exit)

	return 0;

} //----- Fin de main