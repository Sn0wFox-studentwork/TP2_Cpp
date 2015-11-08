/*************************************************************************
                           Ville  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Ville> (fichier Ville.h) ------
#if ! defined ( VILLE_H )
#define VILLE_H

//--------------------------------------------------- Interfaces utilis�es
#include "Capteur.h"
#include "TableHachage.h"

//------------------------------------------------------------- Constantes
const int NB_MAX_CAPTEURS = 1500;

//------------------------------------------------------------------------
// R�le de la classe <Ville> :
// La classe Ville repr�sente une ville dont les rues sont mod�lis�es par
// des segments repr�sent�s par des capteurs. Elle contient donc une structure
// de donn�es repr�sentant chacun des capteurs.
// Elle permet d'ajouter des �v�nements � un Temps et sur une rue (i.e. un Capteur) donn�s.
// Elle permet de r�aliser des statistiques sur chaque instance de la classe
// (% d'embouteillages pour un jour de la semaine donn�e, statistiques journali�res,
// temps de parcours optimal d'un trajet donn� sur une plage horaire donn�e).
//------------------------------------------------------------------------

class Ville
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

	void StatsJour ( int d7 );
	// Mode d'emploi :	Affiche les statistiques de trafic d'une ville pour un jour de la semaine.
	// Contrat :		L'utilisateur s'engage � donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche)

	void EmbouteillageJour ( int d7 );
	// Mode d'emploi :	Affiche le pourcentage de R et N pour chaque heure d'un jour de la semaine.
	// Contrat :		L'utilisateur s'engage � donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche)

	void TempsParcours ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments );
	// Mode d'emploi :	Affiche l'heure de depart et le temps de parcours minimal pour parcourir 
	//					les segments idSegments entre tdebut et tfin au jour d7 de la semaine.
	//					Les plages horaires sans donn�es seront consid�r�es comme ayant un trafic noir.
	// Contrat :		L'utilisateur s'engage � donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche),
	//					ainsi que hDebut et hFin positifs, et un Vecteur d'identifiants de segments positifs.

	void AjouterEvenement ( int id, Evenement& evenement );
	// Mode d'emploi :	Ajoute un Evenement evenement � l'un des capteurs de la ville,
	//					ou le cr�e s'il n'existe pas puis ajoute l'Evenement.
	// Contrat :		L'utilisateur s'engage � donner un identifiant id positif.

//------------------------------------------------- Surcharge d'op�rateurs
	Ville & operator = ( const Ville & uneVille );
	// Mode d'emploi :	R�affecte l'instance courante pour la rendre en tout point similaire � uneVille.
	//					Les deux villes auront les m�mes donn�es, mais non partag�es (copies).

	Capteur& operator[] ( int idCapteur );
	// Mode d'emploi :	Permet d'acc�der au capteur d'identifiant idCapteur.
	//					Retourne une r�f�rence non-constante (op�rande de gauche).
	// Contrat :		L'utilisateur s'engage � fournir un identifiant idCapteur positif.

	Capteur& operator[] ( int idCapteur ) const;
	// Mode d'emploi :	Permet d'acc�der au capteur d'identifiant idCapteur.
	//					Retourne une r�f�rence constante (pour op�rande de droite uniquement donc).
	// Contrat :		L'utilisateur s'engage � fournir un identifiant idCapteur positif.

//-------------------------------------------- Constructeurs - destructeur
	Ville ( const Ville & unVille );
	// Mode d'emploi :	Consruit une nouvelle instance de Ville � partir d'une Ville existante uneVille.
	//					Les deux villes auront les m�mes donn�es, mais non partag�es (copies).

	Ville ( int nombreSegments = NB_MAX_CAPTEURS, int nombrePremier = NB_PREMIER_BASE );
	// Mode d'emploi :	Construit une nouvelle instance de Ville.
	//					Le param�tre nombrePremier servira � g�n�rer la structure de donn�es qui contient
	//					les Capteurs.
	// Contrat :		Pour que la structure de donn�es soit utile, l'utilisateur doit fournir un nombre
	//					premier strictement sup�rieur � 5 fois le nombre maximal de Capteurs qu'il pense stocker.
	//					Les constantes NB_MAX_CAPTEURS et NB_PREMIER_BASE v�rifient ces crit�res.

	virtual ~Ville ( );
	// Mode d'emploi :	D�truit une instance de Ville et lib�re la m�moire. Appel� automatiquement.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- M�thodes prot�g�es

	void creerCapteur ( int id );
	// Mode d'emploi :	Cree un capteur et l'insert dans la structure contenant les capteurs de la ville.
	// Contrat :		L'utilisateur s'engage � v�rifier que le capteur d'identifiant id n'existe pas,
	//					sans quoi deux capteurs avec le m�me identifiant seront pr�sents dans la ville.

protected:
//----------------------------------------------------- Attributs prot�g�s

	TableHachage tableDeHachage;	// Structure stockant des pointeurs vers chaque Capteur de la ville
	Vecteur<int> listeId;			// Liste des identifiants des Capteurs de la ville
	int nombreCapteurs;				// Nombre total de Capteurs de la ville (= listeId.getTaille())
	int semaineResume[MIN_PAR_SEMAINE][NB_STATS];
	/* NB : Structure de semaineResume :
		[i][0] : nombre de V
		[i][1] : nombre de J
		[i][2] : nombre de R
		[i][3] : nombre de N
	L'indice i correspond � la i�me minute de la semaine.
	*/

};

#endif // VILLE_H
