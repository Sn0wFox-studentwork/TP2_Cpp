/*************************************************************************
                           Ville  -  description
                             -------------------
    début                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Ville> (fichier Ville.h) ------
#if ! defined ( VILLE_H )
#define VILLE_H

//--------------------------------------------------- Interfaces utilisées
#include "Capteur.h"
#include "TableHachage.h"

//------------------------------------------------------------- Constantes
const int NB_MAX_CAPTEURS = 1500;

//------------------------------------------------------------------------
// Rôle de la classe <Ville> :
// La classe Ville représente une ville dont les rues sont modélisées par
// des segments représentés par des capteurs. Elle contient donc une structure
// de données représentant chacun des capteurs.
// Elle permet d'ajouter des Événements à un Temps et sur une rue (i.e. un Capteur) donnés.
// Elle permet de réaliser des statistiques sur chaque instance de la classe
// (% d'embouteillages pour un jour de la semaine donnée, statistiques journalières,
// temps de parcours optimal d'un trajet donné sur une plage horaire donnée).
//------------------------------------------------------------------------

class Ville
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void StatsJour ( int d7 );
	// Mode d'emploi :	Affiche les statistiques de trafic d'une ville pour un jour de la semaine.
	// Contrat :		L'utilisateur s'engage à donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche)

	void EmbouteillageJour ( int d7 );
	// Mode d'emploi :	Affiche le pourcentage de R et N pour chaque heure d'un jour de la semaine.
	// Contrat :		L'utilisateur s'engage à donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche)

	void TempsParcours ( int d7, int hDebut, int hFin, Vecteur<int>& idSegments );
	// Mode d'emploi :	Affiche l'heure de depart et le temps de parcours minimal pour parcourir 
	//					les segments idSegments entre tdebut et tfin au jour d7 de la semaine.
	//					Les plages horaires sans données seront considérées comme ayant un trafic noir.
	// Contrat :		L'utilisateur s'engage à donner un jour compris entre 1 et 7 (1 = lundi, 7 = dimanche),
	//					ainsi que hDebut et hFin positifs, et un Vecteur d'identifiants de segments positifs.

	void AjouterEvenement ( int id, Evenement& evenement );
	// Mode d'emploi :	Ajoute un Evenement evenement à l'un des capteurs de la ville,
	//					ou le crée s'il n'existe pas puis ajoute l'Evenement.
	// Contrat :		L'utilisateur s'engage à donner un identifiant id positif.

//------------------------------------------------- Surcharge d'opérateurs
	Ville & operator = ( const Ville & uneVille );
	// Mode d'emploi :	Réaffecte l'instance courante pour la rendre en tout point similaire à uneVille.
	//					Les deux villes auront les mêmes données, mais non partagées (copies).

	Capteur& operator[] ( int idCapteur );
	// Mode d'emploi :	Permet d'accéder au capteur d'identifiant idCapteur.
	//					Retourne une référence non-constante (opérande de gauche).
	// Contrat :		L'utilisateur s'engage à fournir un identifiant idCapteur positif.

	Capteur& operator[] ( int idCapteur ) const;
	// Mode d'emploi :	Permet d'accéder au capteur d'identifiant idCapteur.
	//					Retourne une référence constante (pour opérande de droite uniquement donc).
	// Contrat :		L'utilisateur s'engage à fournir un identifiant idCapteur positif.

//-------------------------------------------- Constructeurs - destructeur
	Ville ( const Ville & unVille );
	// Mode d'emploi :	Consruit une nouvelle instance de Ville à partir d'une Ville existante uneVille.
	//					Les deux villes auront les mêmes données, mais non partagées (copies).

	Ville ( int nombreSegments = NB_MAX_CAPTEURS, int nombrePremier = NB_PREMIER_BASE );
	// Mode d'emploi :	Construit une nouvelle instance de Ville.
	//					Le paramètre nombrePremier servira à générer la structure de données qui contient
	//					les Capteurs.
	// Contrat :		Pour que la structure de données soit utile, l'utilisateur doit fournir un nombre
	//					premier strictement supérieur à 5 fois le nombre maximal de Capteurs qu'il pense stocker.
	//					Les constantes NB_MAX_CAPTEURS et NB_PREMIER_BASE vérifient ces critères.

	virtual ~Ville ( );
	// Mode d'emploi :	Détruit une instance de Ville et libère la mémoire. Appelé automatiquement.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

	void creerCapteur ( int id );
	// Mode d'emploi :	Cree un capteur et l'insert dans la structure contenant les capteurs de la ville.
	// Contrat :		L'utilisateur s'engage à vérifier que le capteur d'identifiant id n'existe pas,
	//					sans quoi deux capteurs avec le même identifiant seront présents dans la ville.

protected:
//----------------------------------------------------- Attributs protégés

	TableHachage tableDeHachage;	// Structure stockant des pointeurs vers chaque Capteur de la ville
	Vecteur<int> listeId;			// Liste des identifiants des Capteurs de la ville
	int nombreCapteurs;				// Nombre total de Capteurs de la ville (= listeId.getTaille())
	int semaineResume[MIN_PAR_SEMAINE][NB_STATS];
	/* NB : Structure de semaineResume :
		[i][0] : nombre de V
		[i][1] : nombre de J
		[i][2] : nombre de R
		[i][3] : nombre de N
	L'indice i correspond à la ième minute de la semaine.
	*/

};

#endif // VILLE_H
