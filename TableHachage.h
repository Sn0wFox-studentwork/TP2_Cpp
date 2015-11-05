/*************************************************************************
TableHachage  -  description
-------------------
d�but                : 19/10/2015
copyright            : (C) 2015 par ${user}
*************************************************************************/

//---------- Interface de la classe <TableHachage> (fichier TableHachage.h) ------
#if ! defined ( TABLE_HACHAGE_H )
#define TABLE_HACHAGE_H

//--------------------------------------------------- Interfaces utilis�es
#include "Capteur.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <TableHachage>
//
//
//------------------------------------------------------------------------ 

class TableHachage
{
	//----------------------------------------------------------------- PUBLIC

public:
	//----------------------------------------------------- M�thodes publiques
	// type M�thode ( liste de param�tres );
	// Mode d'emploi :
	//
	// Contrat :
	//
	int Hacher ( Capteur* capteur );
	// Retourne l'index de positionnnement associ� au Capteur capteur

	int Hacher ( int idCapteur );
	// Retourne l'index de positionnnement associ� au Capteur d'identifiant idCapteur

	void Inserer ( Capteur* capteur );
	// Insere le Capteur* capteur dans la table de hachage

	Capteur* GetCapteur ( int idCapteur );
	// Retourne un pointeur vers le capteur d'identifiant idCapteur,
	// si celui-ci est pr�sent dans la table.
	// Sinon, retourne un pointeur null.


	//------------------------------------------------- Surcharge d'op�rateurs
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
	//----------------------------------------------------- M�thodes prot�g�es

private:
	//------------------------------------------------------- M�thodes priv�es

protected:
	//----------------------------------------------------- Attributs prot�g�s
	int tailleTable;
	int nombrePremier;
	Capteur** table;

};

//----------------------------------------- Types d�pendants de <TableHachage>

#endif // TABLE_HACHAGE_H
