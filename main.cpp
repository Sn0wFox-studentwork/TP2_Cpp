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

int main(int argc, char* argv[])
// Algorithme :
{
	Ville v;
	
	// Bancs d'essais: (de la forme bench(&Classe::fonction, objet, param1, ... , paramN, nombreRepetitions), N de 0 à 4)
	
	Temps t(5, 1586, 5, 2, 5, 6);
	Evenement e(N, t);
	for (int i = 0; i < 3; i++)
	{
		v.AjouterEvenement(i, e);
	}

	cout << v[2].GetID() << ends;
	cout << v[2].TempsSegment(5, 5, 6) << endl;
	v.StatsJour(5);

	Ville v2(v);
	v2.StatsJour(5);
	v.EmbouteillageJour(5);
	
	
	typedef Vecteur<int> Vint;
	Vint s;
	s.insererFin(4);
	bench(&Capteur::TempsSegment, v[2], 5, 6, 6, 1000000);
	//bench(&Ville::StatsJour, v, 5, 100);

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
			cin >> annee;
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
			Evenement evenement(temps, trafic);

			v.AjouterEvenement( id, evenement );*/

			cout << lecture  << "!" << endl;

		}
		else if ( lecture == "STATS_C" )
		{
			// Code cmd2 STATS_C
		}
		else if ( lecture == "STATS_D7" )
		{
			// Code cmd3 STATS_D7
		}
		else if ( lecture == "JAM_DH" )
		{
			// Code cmd4 JAM_DH
		}
		else if ( lecture == "OPT" )
		{
			// Code cmd5 OPT
		}

		// clean non-necessaire
		cin >> lecture;

	} //----- Fin de while (exit)

	return 0;

} //----- Fin de main