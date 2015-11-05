/*************************************************************************
TableHachage  -  description
-------------------
début                : 19/10/2015
copyright            : (C) 2015 par ${user}
*************************************************************************/

//---------- Interface de la classe <TableHachage> (fichier TableHachage.h) ------
#if ! defined ( TABLE_HACHAGE_H )
#define TABLE_HACHAGE_H

//--------------------------------------------------- Interfaces utilisées
#include "Capteur.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <TableHachage>
//
//
//------------------------------------------------------------------------ 

class TableHachage
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- Méthodes publiques
	// type Méthode ( liste de paramètres );
	// Mode d'emploi :
	//
	// Contrat :
	//
	int Hacher ( Capteur* capteur );
	// Retourne l'index de positionnnement associé au Capteur capteur

	int Hacher ( int idCapteur );
	// Retourne l'index de positionnnement associé au Capteur d'identifiant idCapteur

	void Inserer ( Capteur* capteur );
	// Insere le Capteur* capteur dans la table de hachage

	Capteur* GetCapteur ( int idCapteur );
	// Retourne un pointeur vers le capteur d'identifiant idCapteur,
	// si celui-ci est présent dans la table.
	// Sinon, retourne un pointeur null.


	//------------------------------------------------- Surcharge d'opérateurs
	TableHachage &operator = ( const TableHachage &uneTableHachage );
	// Mode d'emploi :
	//
	// Contrat :
	//


	//-------------------------------------------- Constructeurs - destructeur
	TableHachage ( const TableHachage &uneTableHachage );
	// Mode d'emploi (constructeur de copie) :
	//
	// Contrat :
	//

	TableHachage ( int tailleTable, int nombrePremier );
	// Mode d'emploi :
	//
	// Contrat :
	//

	virtual ~TableHachage ();
	// Mode d'emploi :
	//
	// Contrat :
	//

	//------------------------------------------------------------------ PRIVE 

protected:
	//----------------------------------------------------- Méthodes protégées

private:
	//------------------------------------------------------- Méthodes privées

protected:
	//----------------------------------------------------- Attributs protégés
	int tailleTable;
	int nombrePremier;
	Capteur** table;

};

//----------------------------------------- Types dépendants de <TableHachage>

#endif // TABLE_HACHAGE_H
