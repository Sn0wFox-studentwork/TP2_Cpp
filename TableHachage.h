/*************************************************************************
TableHachage  -  description
-------------------
début                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <TableHachage> (fichier TableHachage.h) ------
#if ! defined ( TABLE_HACHAGE_H )
#define TABLE_HACHAGE_H

//--------------------------------------------------- Interfaces utilisées
#include "Capteur.h"

//------------------------------------------------------------- Constantes 
const int NB_PREMIER_BASE = 10007;

//------------------------------------------------------------------------ 
// Rôle de la classe <TableHachage>
// La classe TableHachage a été conçue spécialement pour implémenter une hashTable
// permettant de stocker UNIQUEMENT des pointeurs vers Capteurs. Ce n'est donc
// pas une classe générique (template).
// Elle propose deux fonctions de hachage (sous forme de méthodes) qui permettent
// de générer un clé à partir soit d'un identifiant, soit d'un pointeur vers Capteur
// (l'une faisant appel à l'autre, toute la cohérence de la table est conservée).
// Elle permet d'accéder à un capteur précis à partir de son identifiant, ou à une
// case mémoire précise (à utiliser avec une fonction de hachage comme paramètre si
// on veut éviter les accès mémoire incohérents).
//------------------------------------------------------------------------ 

class TableHachage
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	int Hacher ( Capteur* capteur ) const;
	// Mode d'emploi :	Retourne l'index de positionnnement associé au Capteur* capteur.
	//					Cet index est le même que celui généré par l'appel à Hacher( capteur->GetID( ) ).
	//					A noter que deux instances TableHachage n'ont pas forcément la même fonction de hachage.

	int Hacher ( int idCapteur ) const;
	// Mode d'emploi :	Retourne l'index de positionnement associé au Capteur d'identifiant idCapteur.
	//					A noter que deux instances TableHachage n'ont pas forcément la même fonction de hachage.
	// Contrat :		L'utilisateur s'engage à fournir un idCapteur positif.

	void Inserer ( Capteur* capteur );
	// Mode d'emploi :	Insere le Capteur* capteur dans la TableHachage courante.

	Capteur* GetCapteur ( int idCapteur ) const;
	// Mode d'emploi :	Retourne un pointeur vers le capteur d'identifiant idCapteur,
	//					si celui-ci est présent dans la table.
	//					Sinon, retourne un pointeur null.
	// Contrat :		L'utilisateur s'engage à fournir un idCapteur positif.

//------------------------------------------------- Surcharge d'opérateurs
	TableHachage &operator = ( const TableHachage &uneTableHachage );
	// Mode d'emploi :	Réaffecte l'instance courante pour la rendre en tout point similaire à uneTableHachage.
	//					Les deux tables stockeront alors les même données, mais non partagées (copies).

	Capteur*& operator[] ( int index );
	// Mode d'emploi :	Retourne le pointeur contenu à l'index index, sous forme de référence non-constante (opérande de gauche).
	//					Attention, cet élément peut être un nullptr. Pas d'accés illégal en mémoire en revanche.
	// Contrat :		L'utilisateur s'engage à vérifier l'intégrité du pointeur retourné (= si différent de nullptr)
	//					avant d'appliquer des méthodes à l'objet pointé par le pointeur retourné,
	//					et à fournir une valeur d'index positive.

	Capteur*& operator[] ( int index ) const;
	// Mode d'emploi :	Retourne le pointeur contenu à l'index index, sous forme de référence constante (opérande de droite uniquement).
	//					Attention, cet élément peut être un nullptr. Pas d'accés illégal en mémoire en revanche.
	// Contrat :		L'utilisateur s'engage à vérifier l'intégrité du pointeur retourné (= si différent de nullptr)
	//					avant d'appliquer des méthodes à l'objet pointé par le pointeur retourné,
	//					et à fournir une valeur d'index positive.

//-------------------------------------------- Constructeurs - destructeur
	TableHachage ( const TableHachage &uneTableHachage );
	// Mode d'emploi :	Consruit une nouvelle instance de TableHachage à partir d'une TableHachage existante uneTableHachage.
	//					Les deux tables stockeront alors les même données, mais non partagées (copies).

	TableHachage ( int tailleTable, int nombrePremier );
	// Mode d'emploi :	Construit une nouvelle instance de TableHachage.
	//					Le paramètre tailleTable donnera le nombre de cases de la structure de stockage table.
	//					Le paramètre nombrePremier permettra de générer la fonction de hachage présente dans
	//					les deux méthodes Hacher.
	// Contrat :		Pour utiliser au mieux une TableHachage, il est fortement recommandé que nombrePremier soit
	//					strictement supérieur à tailleTable.
	//					L'utilisateur s'engage également à donner des valeurs positives pour ces deux paramètres.

	virtual ~TableHachage ( );
	// Mode d'emploi :	Détruit une instance de TableHachage et libère la mémoire. Appelé automatiquement.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Attributs protégés
	int tailleTable;		// Nombre de cases de table
	int nombrePremier;		// Nombre premier servant à générer une fonction de hachage
	Capteur** table;		// Tableau dynamique de pointeurs de Capteurs

};

#endif // TABLE_HACHAGE_H
