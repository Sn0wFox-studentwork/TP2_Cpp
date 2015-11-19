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
//#define MAP	// Permet de visualiser les appels aux constructeurs/destructeurs et certains éléments de debugging

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Ville::StatsJour( int d7 )
// Algorithme :	On somme le nombre d'apparitions de chaque valeur de trafic (V, J, R, N)
//				sur chaque minute de la journée d7.
//				On crée les 4 statistiques voulues à partir des 4 sommes précédentes en les
//				divisant par le total (= la somme des 4 sommes) si celui-ci est différent de 0.
//				On affiche les statistique en %.
//
// Complexité :	O(1) (1440 itérations à chaque fois)
{
	// Création structure pour affichage et variables pratiques
	int total = 0;		// Nombre total d'évènements
	int nbVert = 0;
	int nbJaune = 0;
	int nbRouge = 0;
	int nbNoir = 0;
	int minuteInitiale = (d7 - 1) * HEURE_PAR_JOUR * MIN_PAR_HEURE;
	int minuteMax = d7 * HEURE_PAR_JOUR * MIN_PAR_HEURE;
	double stats[NB_STATS];

	// Récupération du nombre total de chaque valeur de Trafic
	for ( int minute = minuteInitiale; minute < minuteMax; minute++ )
	{
		nbVert += semaineResume[minute][0];
		nbJaune += semaineResume[minute][1];
		nbRouge += semaineResume[minute][2];
		nbNoir += semaineResume[minute][3];
	}
	total = nbVert + nbJaune + nbRouge + nbNoir;

	// Création des statistiques
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
	cout << "V " << stats[0] * 100 << "%\r\n";
	cout << "J " << stats[1] * 100 << "%\r\n";
	cout << "R " << stats[2] * 100 << "%\r\n";
	cout << "N " << stats[3] * 100 << "%\r\n";

} //----- Fin de statsJour

void Ville::EmbouteillageJour( int d7 )
// Algorithme :	On somme le nombre d'apparitions de chaque valeur de trafic (V, J, R, N)
//				sur chaque minute pour chaque heure de la journée d7.
//				On crée les 24 statistiques voulues à partir des 24 sommes précédentes en les
//				divisant par le total de l'heure correspondante présent dans le tableau total
//				(si ce total est différent de 0).
//				On affiche les statistique en %.
//				
// Complexité :	O(1) (1440 itérations à chaque fois)
{
	// Création structure pour affichage et variables pratiques
	int total[HEURE_PAR_JOUR];						// Nombre total d'évènements par heure
	int nbEmbouteillage[HEURE_PAR_JOUR];			// Nombre d'événements avec un Trafic R ou N
	double stats[HEURE_PAR_JOUR];					// Tableau pour affichage
	int heureInitiale = (d7 - 1) * HEURE_PAR_JOUR;
	int heureMax = d7 * HEURE_PAR_JOUR;	

	// Init de la structure d'affichage
	for ( int i = 0; i < HEURE_PAR_JOUR; i++ )
	{
		nbEmbouteillage[i] = 0;
		total[i] = 0;
		stats[i] = 0;
	}

	// Prise des données
	for (int h = heureInitiale; h < heureMax; h++)
	{
		for ( int minute = 0; minute < MIN_PAR_HEURE; minute++ )
		{
			// Trafic V ou J pour le total :
			total[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][0];
			total[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][1];
			// Trafic R ou N pour les embouteillages :
			nbEmbouteillage[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][2];
			nbEmbouteillage[h - heureInitiale] += semaineResume[h * MIN_PAR_HEURE + minute][3];
		}
		// Pour le total, il faut ajouter aussi le nombre d'embouteillages :
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
		cout << d7 << " " << i << " " << stats[i] * 100 << "%\r\n";
	}

} //----- Fin de EmbouteillageJour

void Ville::TempsParcours ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments )
// Algorithme :	Pour chaque minute de chaque heure de la plage horaire dédinie par hDebut et hFin
//				(chacun de ces couples correspondant à un instant de départ), on calcul le temps
//				de parcours total en additionnant le temps unitaire de parcours de chaque segment
//				(via l'appel de la fonction TempsSegment(jour, heure, minute) de Capteur)
//				LE PLUS PROBABLE. En cas d'égalité, c'est le trafic le plus emcombré qui est pris en compte.
//				Il en résulte que les plages horaires sans données seront considérées comme ayant un trafic noir.
//				Dans le cas où le capteur n'existe pas, on revient au cas d'absence de données : trafic considéré noir.
//				Si le temps final est strictement inférieur au temps minimal actuel
//				(ou que ce temps est actuellement nul), on remplace le meilleur temps par le temps actuel.
//				Le temps de déplacement de chaque segment est pris en compte.
//				Exemple :	départ à 00h00 du premier segment. Si il faut 4 minutes pour le traverser, on regarde
//							alors combien de temps il faut pour traverser le segment 2 en partant de celui-ci à 00h04.
//				Si le temps des premiers segments fait dépasser dimanche 23h59, on revient à lundi par un simple modulo.
//				Il en va de même lorsqu'on dépasse 59 minutes ou 23h par heure/jour.
//				On affiche le jour, l'heure et la minute de départ ainsi que le temps de trajet estimé.
//				
// Complexite : O(nbHeures*nbSegments)
{
	// Création variables pour affichage et variables pratiques
	int temps = 0;				// Servira a calculer le temps de parcours courant
	int tempsAdditionnel = 0;	// Temps unitaire de parcours, fonction du Trafic : V = 1min, J = 2min, R = 4min, N = 10min
	int meilleurTemps = 0;		// Pour garder en mémoire l'actuel meilleur temps
	int meilleureMinute = 0;
	int meilleureHeure = 0;
		// Les trois dernières variables permettent de parcourir correctement la boucle :
	int heureActuelle = hDebut;
	int minuteActuelle = 0;
	int jourActuel = d7;

	// Recherche du meilleur temps
	for ( int heure = hDebut; heure <= hFin; heure++ )
	{
		for ( int minute = 0; minute < MIN_PAR_HEURE; minute++ )
		{

			temps = 0;	// Remise à jour pour calcul du temps lors du départ à heureActuelle:minuteActuelle
			minuteActuelle = minute;
			heureActuelle = heure;
			jourActuel = d7;
			for (int i = 0; i < idSegments.GetTaille(); i++)
			{
				// Si le segment existe, on calcul le temps le plus probable de parcours :
				if ( (*this)[idSegments[i]] )
				{
					tempsAdditionnel = (*this)[idSegments[i]]->TempsSegment(jourActuel, heureActuelle, minuteActuelle);
				}
				// Sinon, on considère que nous n'avons pas de données ; on prend donc le temps maximal :
				else
				{
					tempsAdditionnel = TEMPS_PARCOURS_N;
				}

				temps += tempsAdditionnel;
				minuteActuelle += tempsAdditionnel;
				// Lors d'un dépassement de jourActuel = 7, heureActuelle = 23 ou minuteActuelle = 60 :
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
			} //----- Fin de for ( segment )
			
			// En cas de nouveau meilleur temps : mise a jour
			if ( (temps < meilleurTemps || meilleurTemps == 0) && temps > 0 )
			{
				meilleurTemps = temps;
				meilleureHeure = heure;
				meilleureMinute = minute;
			}
		} //----- Fin de for ( minute )
	} //----- Fin de for ( heure ) ; recherche du meilleur temps

	// Affichage
	cout << d7 << " " << meilleureHeure << " " << meilleureMinute << " " << meilleurTemps << "\r\n";

} //----- Fin de TempsParcours

void Ville::AjouterEvenement( int id, Evenement& evenement )
// Algorithme :	On tente d'accéder directement au capteur par son identifiant id dans la table de hachage.
//				Si ce Capteur n'existe pas encore (i.e. on a un pointeur null), on crée le Capteur
//				et on l'insère grâce à creerCapteur( id ).
//				Lorsqu'on est sûr que le Capteur existe, on insère l'Evenement evenement grâce à
//				la méthode Inserer( Evenement ) de Capteur.
//				On incrémente ensuite la bonne case du tableau semaineResume (en fonction de l'heure, de la
//				minute et du Trafic de l'Evenement evenement).
//				
// Complexité : O(1) Grace à la table de Hachage, s'il n'y a pas de collisions.
//				O(n) dans le pire des cas, ce qui n'arrivera pas avec notre fonction de hash.
{
	// Création et initialisation des variables
    Capteur* capteur = nullptr;
    capteur = tableDeHachage.GetCapteur( id );

	// Insertion de l'Evenement
    if ( capteur != nullptr )
    {
        capteur->Inserer( evenement );
    }
    else	//si le capteur n'existe pas
    {
        capteur = new Capteur( id );
		tableDeHachage.Inserer( capteur );
		listeId.InsererFin( id );							//on le crée
        capteur = tableDeHachage.GetCapteur( id );			//on est donc sur qu'il existe maintenant
        capteur->Inserer( evenement );
    }

	// Incrementation du tableau permettant de faire les statistiques semaineResume
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

	semaineResume[numMinute][posStat]++;

} //----- Fin de AjouterEvenement

//------------------------------------------------- Surcharge d'opérateurs
Ville &Ville::operator = ( const Ville &uneVille )
// Algorithme :		Si on n'est pas en train de faire uneVille = uneVille,
//					on "copie" tout les champs :
//					on les modifie pour qu'ils soient comme ceux de uneVille.
//					On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	if ( this != &uneVille )
	{
		// On utilise la surcharge de operator= pour TableHachage et Vecteur
		tableDeHachage = uneVille.tableDeHachage;
		listeId = uneVille.listeId;
		nombreCapteurs = uneVille.nombreCapteurs;

		// Recopie des autres données de uneVille
		for ( int minute = 0; minute < MIN_PAR_SEMAINE; minute++ )
		{
			for ( int numStat = 0; numStat < NB_STATS; numStat++ )
			{
				semaineResume[minute][numStat] = uneVille.semaineResume[minute][numStat];
			}
		}
	}

	return *this;

} //----- Fin de operator =


Capteur*& Ville::operator[] ( int idCapteur )
// Algorithme : Retourne le capteur d'identifiant idCapteur en se servant
//				de la surcharge de [] de TableHachage.
// Complexité : O(1) Grace à la table de Hachage, s'il n'y a pas de collisions.
//				O(n) dans le pire des cas, ce qui n'arrivera pas avec notre fonction de hash.
{
	return tableDeHachage[tableDeHachage.Hacher( idCapteur )];

} //----- Fin de operator []

Capteur*& Ville::operator[] ( int idCapteur ) const
// Algorithme : Retourne le capteur d'identifiant idCapteur en se servant
//				de la surcharge de [] de TableHachage.
// Complexité : O(1) Grace à la table de Hachage, s'il n'y a pas de collisions.
//				O(n) dans le pire des cas, ce qui n'arrivera pas avec notre fonction de hash.
{
	return tableDeHachage[tableDeHachage.Hacher( idCapteur )];

} //----- Fin de operator [] const


//-------------------------------------------- Constructeurs - destructeur
Ville::Ville ( const Ville &uneVille ) :
	tableDeHachage( uneVille.tableDeHachage ),
	listeId( uneVille.listeId ), nombreCapteurs( uneVille.nombreCapteurs )
// Algorithme :	Initialisation des attributs à partir de ceux de uneVille,
//				puis recopie des données de semaineResume à partir de celles de uneVille.
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Ville>" << endl;
#endif

	for (int minute = 0; minute < MIN_PAR_SEMAINE; minute++)
	{
		for (int numStat = 0; numStat < NB_STATS; numStat++)
		{
			semaineResume[minute][numStat] = uneVille.semaineResume[minute][numStat];
		}
	}

} //----- Fin de Ville (constructeur de copie)

Ville::Ville ( int nombreSegments, int nombrePremier ) :
	tableDeHachage( nombreSegments * 4, nombrePremier ),
	listeId( ), nombreCapteurs( NB_MAX_CAPTEURS )
// Algorithme :	Construit une instance de Ville.
//				Pour le bon fonctionnement de la table de hachage, il faut donner un nombre premier
//				supérieur à la taille de la table, et une taille de table supérieure au nombre maximum
//				d'éléments qu'on souhaite qu'elle contienne.
{
#ifdef MAP
	cout << "Appel au constructeur de <Ville>" << endl;
#endif

	// Initialisation du résumé hebdomadaire
	for ( int minute = 0; minute < MIN_PAR_SEMAINE; minute++ )
	{
		for ( int numStat = 0; numStat < NB_STATS; numStat++ )
		{
			semaineResume[minute][numStat] = 0;
		}
	}

} //----- Fin de Ville


Ville::~Ville ( )
// Algorithme :	Le destructeur de TableHacahe va être appelé pour tableDeHachage automatiquement.
//				C'est ce dernier qui va se charger de libérer la mémoire pour tout les capteurs
//				alloués dynamiquement.
//				Rien de plus à faire ici donc.
{
#ifdef MAP
	cout << "Appel au destructeur de <Ville>" << endl;
#endif

} //----- Fin de ~Ville


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void Ville::creerCapteur( int id )
// Algorithme : Allocation dynamique d'un nouveau capteur et "insertion" dans la table de hachage.
//				Insertion de l'identifiant dans la liste des identifiants.
// NB:	On suppose que la vérification de l'existence du capteur a été traitée avant l'appel à cette fonction.
{

} //----- Fin de creerCapteur
