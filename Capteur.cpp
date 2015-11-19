/*************************************************************************
Capteur  -  description
-------------------
d�but                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- R�alisation de la classe <Capteur> (fichier Capteur.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst�me
using namespace std;
#include <iostream>
#include <cstddef>		// Utilisation de nullptr

//------------------------------------------------------ Include personnel
#include "Capteur.h"

//------------------------------------------------------------- Constantes
//#define MAP	// Permet de visualiser les appels aux constructeurs/destructeurs et certains �l�ments de debugging

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques

void Capteur::Inserer ( Evenement& unEvenement )
// Algorithme :	On d�termine quel tableau de semaineResume incr�menter en se basant sur le jour, l'heure et la minute
//				de unEvenement.
//				On d�termine quelle tableau de r�sum� journali� modifier gr�ce au jour de unEvenement.
//				On incr�mente la bonne case de chacun des deux tableaux d�termin�s pr�c�dement gr�ce au Trafic
//				de unEvenement, sans oublier la case repr�sentant le nombre total d'Evenement (4) pour un jour donn�.
// Complexit� : O(1)
{
	// Variables permettant de positionner l'insertion
	int indice = ( (unEvenement.GetD7( ) - 1) * HEURE_PAR_JOUR + unEvenement.GetHeure( ) ) * MIN_PAR_HEURE + unEvenement.GetMinute( );
	int * jourTab = nullptr;

	// D�termination du tableau de r�sum� journali� dans lequel prendre les donn�es
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

	// Incr�mentation du r�sum� de la semaine
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

	// Incr�mentation du nombre total d'Evenement
	jourTab[4]++;

} //----- Fin de Inserer

Vecteur<double> Capteur::StatsPropres()
// Algorithme :	On calcul le total d'Evenement que le Capteur courant a enregistr� en sommant les valeurs
//				des cases d'indice 4 des r�sum�s journali�s.
//				Si ce total est diff�rent de 0, on divise alors le nombre d'occurence de chaque �tat du trafic
//				(V, J, R ou N) par ce total, et on l'ins�re dans la structure de retour statsRetour.
//				On retourne le Vecteur<double> de taille 4 statsRetour qui contient les statistiques
//				comprise entre 0 et 1 (0 partout si le total vaut 0).
// Complexit� : O(1)
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
// Algorithme :	On det�rmine dans quelle case prendre les donn�es en se basant sur la construction m�me
//				de la structure semaineResume.
//				On d�termine quel Trafic est le plus probable en prenant celui qui est apparu le plus grand
//				nombre de fois. En cas d'�galit�, c'est le trafic le plus perturb� qui sera comptabilis�.
//				Ceci implique que les INSTANTS SANS DONNES seront compt� comme ayant un Trafic NOIR (N).
//				On retourne le temps de parcours le plus probable d�fini en fonction de la valeur du Trafic pr�c�dent.
// Complexit� : O(1)
{
	// Cr�ation variables pratiques
	int nombreTrafic = 0;
	int traficLePlusProbable = 0;
	int indice = ((d7 - 1) * HEURE_PAR_JOUR + heure) * MIN_PAR_HEURE + minute;

	for ( int i = 0; i < NB_STATS; i++ )
	{
		if ( semaineResume[indice][i] >= nombreTrafic )	// >= fait prendre le trafic avec le plus long temps de parcours en cas d'�galit�
		{												// ceci se traduit par un trafic N pour les endroits sans donn�es (�galit� avec 0 partout)
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

//------------------------------------------------- Surcharge d'op�rateurs
Capteur &Capteur::operator = ( const Capteur &unCapteur )
// Algorithme :	Si on n'est pas en train de faire unCapteur = unCapteur,
//				on lib�re la m�moire des donn�es actuelles,
//				puis on "copie" tout les champs :
//				on les modifie pour qu'ils soient comme ceux de unCapteur.
//				On retourne *this pour la bonne marche de la surcharge d'operateur.
// A noter :	Pas d'allocation dynamique ici. A priori, nul besoin de dupliquer le(s) capteur(s)
//				point�(s) par suivant.
{
#ifdef MAP
	cout << "Operator = de <Capteur>" << endl;
#endif
	if ( this != &unCapteur )
	{
		// Pas d'op�ration "delete suivant" car a priori suivant n'a pas forc�ment �t� allou� dynamiquement.

		// R�allocation de la cha�ne
		suivant = nullptr;
		Capteur* cSuiv = unCapteur.GetSuivant( );
		while ( cSuiv )
		{
			cout << "Here !" << endl;
			suivant = cSuiv;
			cSuiv = cSuiv->GetSuivant( );
			suivant = suivant->GetSuivant( );
			// suivant vaut d�j� nullptr ici.
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
// Algorithme :	Initialisation des attributs � partir de ceux de unCapteur,
//				puis recopie des donn�es des dXResume et semaineResume � partir de celles de unCapteur.
//				Attention, on se retrouve alors avec deux capteurs ayant le m�me identifiant.
//				Etant donn� la mani�re dont sont g�r�s les id (� cause du cahier des charges qui force �
//				faire confiance � l'utilisateur sur l'id lors de l'insertion de donn�es), ce n'est pas grave.
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
//				Le pointeur suivant est initialis� comme un nullptr (ne pointe vers rien).
//				On initialise ensuite toutes les statistiques � 0 pour �viter des comportements ind�finis.
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
// Algorithme :	D�truit une instance de Capteur et lib�re la m�moire occup�e par le pointeur suivant
//				(ne pose pas de probl�me si le pointeur est null).
//				TODO: (?) Ceci appel donc le destructeur pour le Capteur point� par suivant qui fonctionne
//				de la m�me mani�re. Ce destructeur d�truit donc toute la liste cha�n�e �ventuelle pr�sente
//				dans une case d'une TableHachage, de mani�re r�cursive.
//				Ceci ne pose pas de probl�me ici puisque les destructeurs ne seront appel�s qu'� la fin de l'application.
{
#ifdef MAP
	cout << "Appel au destructeur de <Capteur>" << endl;
#endif

	// NB:	on ne fait pas d'op�ration "delete suivant;" car a priori le capteur point� par suivant n'a
	//		pas forc�ment �t� allou� dynamiquement.
	//		Il le sera en revanche dans TableHachage : se sera au destructeur de TableHachage de g�rer la d�sallocation.

} //----- Fin de ~Capteur
