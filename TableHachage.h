/*************************************************************************
TableHachage  -  description
-------------------
d�but                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <TableHachage> (fichier TableHachage.h) ------
#if ! defined ( TABLE_HACHAGE_H )
#define TABLE_HACHAGE_H

//--------------------------------------------------- Interfaces utilis�es
#include "Capteur.h"

//------------------------------------------------------------- Constantes 
const int NB_PREMIER_BASE = 10007;

//------------------------------------------------------------------------ 
// R�le de la classe <TableHachage>
// La classe TableHachage a �t� con�ue sp�cialement pour impl�menter une hashTable
// permettant de stocker UNIQUEMENT des pointeurs vers Capteurs. Ce n'est donc
// pas une classe g�n�rique (template).
// Elle propose deux fonctions de hachage (sous forme de m�thodes) qui permettent
// de g�n�rer un cl� � partir soit d'un identifiant, soit d'un pointeur vers Capteur
// (l'une faisant appel � l'autre, toute la coh�rence de la table est conserv�e).
// Elle permet d'acc�der � un capteur pr�cis � partir de son identifiant, ou � une
// case m�moire pr�cise (� utiliser avec une fonction de hachage comme param�tre si
// on veut �viter les acc�s m�moire incoh�rents).
//------------------------------------------------------------------------ 

class TableHachage
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

	int Hacher ( Capteur* capteur ) const;
	// Mode d'emploi :	Retourne l'index de positionnnement associ� au Capteur* capteur.
	//					Cet index est le m�me que celui g�n�r� par l'appel � Hacher( capteur->GetID( ) ).
	//					A noter que deux instances TableHachage n'ont pas forc�ment la m�me fonction de hachage.

	int Hacher ( int idCapteur ) const;
	// Mode d'emploi :	Retourne l'index de positionnement associ� au Capteur d'identifiant idCapteur.
	//					A noter que deux instances TableHachage n'ont pas forc�ment la m�me fonction de hachage.
	// Contrat :		L'utilisateur s'engage � fournir un idCapteur positif.

	void Inserer ( Capteur* capteur );
	// Mode d'emploi :	Insere le Capteur* capteur dans la TableHachage courante.

	Capteur* GetCapteur ( int idCapteur ) const;
	// Mode d'emploi :	Retourne un pointeur vers le capteur d'identifiant idCapteur,
	//					si celui-ci est pr�sent dans la table.
	//					Sinon, retourne un pointeur null.
	// Contrat :		L'utilisateur s'engage � fournir un idCapteur positif.

//------------------------------------------------- Surcharge d'op�rateurs
	TableHachage &operator = ( const TableHachage &uneTableHachage );
	// Mode d'emploi :	R�affecte l'instance courante pour la rendre en tout point similaire � uneTableHachage.
	//					Les deux tables stockeront alors les m�me donn�es, mais non partag�es (copies).

	Capteur*& operator[] ( int index );
	// Mode d'emploi :	Retourne le pointeur contenu � l'index index, sous forme de r�f�rence non-constante (op�rande de gauche).
	//					Attention, cet �l�ment peut �tre un nullptr. Pas d'acc�s ill�gal en m�moire en revanche.
	// Contrat :		L'utilisateur s'engage � v�rifier l'int�grit� du pointeur retourn� (= si diff�rent de nullptr)
	//					avant d'appliquer des m�thodes � l'objet point� par le pointeur retourn�,
	//					et � fournir une valeur d'index positive.

	Capteur*& operator[] ( int index ) const;
	// Mode d'emploi :	Retourne le pointeur contenu � l'index index, sous forme de r�f�rence constante (op�rande de droite uniquement).
	//					Attention, cet �l�ment peut �tre un nullptr. Pas d'acc�s ill�gal en m�moire en revanche.
	// Contrat :		L'utilisateur s'engage � v�rifier l'int�grit� du pointeur retourn� (= si diff�rent de nullptr)
	//					avant d'appliquer des m�thodes � l'objet point� par le pointeur retourn�,
	//					et � fournir une valeur d'index positive.

//-------------------------------------------- Constructeurs - destructeur
	TableHachage ( const TableHachage &uneTableHachage );
	// Mode d'emploi :	Consruit une nouvelle instance de TableHachage � partir d'une TableHachage existante uneTableHachage.
	//					Les deux tables stockeront alors les m�me donn�es, mais non partag�es (copies).

	TableHachage ( int tailleTable, int nombrePremier );
	// Mode d'emploi :	Construit une nouvelle instance de TableHachage.
	//					Le param�tre tailleTable donnera le nombre de cases de la structure de stockage table.
	//					Le param�tre nombrePremier permettra de g�n�rer la fonction de hachage pr�sente dans
	//					les deux m�thodes Hacher.
	// Contrat :		Pour utiliser au mieux une TableHachage, il est fortement recommand� que nombrePremier soit
	//					strictement sup�rieur � tailleTable.
	//					L'utilisateur s'engage �galement � donner des valeurs positives pour ces deux param�tres.

	virtual ~TableHachage ( );
	// Mode d'emploi :	D�truit une instance de TableHachage et lib�re la m�moire. Appel� automatiquement.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Attributs prot�g�s
	int tailleTable;		// Nombre de cases de table
	int nombrePremier;		// Nombre premier servant � g�n�rer une fonction de hachage
	Capteur** table;		// Tableau dynamique de pointeurs de Capteurs

};

#endif // TABLE_HACHAGE_H
