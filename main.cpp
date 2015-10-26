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
#include "Bench.h"

//------------------------------------------------------------- Constantes
typedef Evenement Evenement;
typedef Temps Temps;
typedef Vecteur<int> Vint;

int main(int argc, char* argv[])
// Algorithme :
{
	Ville v;
	
	// Bancs d'essais: (de la forme bench(&Classe::fonction, objet, param1, ... , paramN, nombreRepetitions), N de 0 à 4)
	
	/*for (int i = 0; i < 500; i++)
	{
		Evenement e;
		Temps t(i%7 +1, 1586 + i, 5, 2, i%24, i%60);
		if (i % 8 == 0) { Evenement ev(V, t); e = ev; }
		else if (i % 8 == 1) { Evenement ev(J, t); e = ev; }
		else if (i % 7 == 2) { Evenement ev(R, t); e = ev; }
		else { Evenement ev(N, t); e = ev; }

		v.AjouterEvenement(i%5, e);
		
	}*/

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

	cout << v[4].TempsSegment(5, 5, 6) << endl;
	v.StatsJour(5);

	v.EmbouteillageJour(5);
	
	Vint s;
	s.insererFin(4);
	s.insererFin(2);
	s.insererFin(1);

	v.TempsParcours(5, 0, 23, s);

	//bench(&Capteur::TempsSegment, v[2], 5, 6, 6, 1000000);
	//bench(&Ville::StatsJour, v, 5, 100);
	cout << sizeof(int) << endl;
	bench(&Ville::AjouterEvenement, v, 55, Evenement(J, Temps(5, 1586, 5, 2, 5, 5)), 20000000);
	//bench(&Ville::TempsParcours, v, 5, 0, 23, s, 100);

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
		else if ( lecture == "STATS_C" )
		{
			// Code cmd2 STATS_C
			int idCapteur;
			cin >> idCapteur;

			Vecteur<double> stats = v[idCapteur].StatsPropres();

			cout << "V " << stats[0] * 100 << "%\r\n";	// TODO: quelle tronche a la fin de ligne ?
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