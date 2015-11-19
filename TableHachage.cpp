/*************************************************************************
					TableHachage  -  description
-------------------
d�but                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- R�alisation de la classe <TableHachage> (fichier TableHachage.cpp) --

//---------------------------------------------------------------- INCLUDE
using namespace std;
#include <iostream>
#include <cstddef>		// Utilisation de nullptr

//-------------------------------------------------------- Include syst�me

//------------------------------------------------------ Include personnel
#include "TableHachage.h"

//------------------------------------------------------------- Constantes
//#define MAP	// Permet de visualiser les appels aux constructeurs/destructeurs et certains �l�ments de debugging

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- M�thodes publiques

int TableHachage::Hacher ( Capteur * capteur ) const
// Algorithme :	Retroune Hacher( int ) avec l'identifiant du Capteur point� par capteur en param�tre.
{
	return Hacher( capteur->GetID( ) );

} //----- Fin de Hacher ( Capteur* )

int TableHachage::Hacher ( int idCapteur ) const
// Algorithme :	Retourne une clef g�n�r�e avec une fonction de hachage basique.
//				Cette clef est g�n�r�e en faisant l'identifiant idCapteur modulo avec un nombre premier
//				(strictement sup�rieur � la taille maximale de la table si on veut que �a soit utile)
//				puis modulo la taille du tableau pour faire en sorte que la clef soit l'indice d'une
//				case du tableau. Permet alors un acc�s en O(1), sauf collisions.
//				Le nombre premier permet d'�viter toutes les collisions li�es au multiples.
{
	return ( idCapteur % nombrePremier) % tailleTable;

} //----- Fin de Hacher ( int )

void TableHachage::Inserer ( Capteur * capteur )
// Algorithme :	On g�n�re la clef � partir du Capteur* capteur.
//				S'il s'av�re que cette case du tableau table n'est pas occup�e, on fait seulement
//				pointer le pointeur de cette cas vers la m�me chose que capteur.
//				Sinon, il y a collision. On traite les collisions par liste cha�n�e avec insertion en queue :
//				tant que le pointeur suivant du Capteur point� par le Capteur* c n'est pas null,
//				on avance dans la liste cha�n�e. D�s qu'on est arriv� au bout de la liste (i.e. suivant == nullptr),
//				on fait pointer suivant vers capteur.
// NB :	Le SI et le SINON sont invers�s entre la description et l'impl�mentation, mais il �tait plus simple de faire
//		dans ce sens pour les deux.
{
	// Cr�ation de variables pratiques
	int indice = Hacher( capteur );		// G�n�ration de la clef
		// Pour traiter les collisions :
	Capteur* c = table[indice];			// Capteur courant
	Capteur* cPrecedent = nullptr;		// Capteur pr�c�dent le courant

	// Tant qu'il y a collision, on avance dans la liste cha�n�e
	while ( c != nullptr )
	{
		cPrecedent = c;
		c = c->GetSuivant( );
	}
	
	// Si collision
	if ( cPrecedent )
	{
#ifdef MAP
		cout << "Collision !" << cPrecedent->GetID() << endl;
#endif
		cPrecedent->SetSuivant( capteur );	// Insertion en queue
	}
	// Sinon
	else
	{
		table[indice] = capteur;			// Insertion dans la premi�re case
	}

}  //----- Fin de Inserer

Capteur * TableHachage::GetCapteur ( int idCapteur ) const
// Algorithme :	Retourne le capteur d'identifiant idCapteur pr�sent � l'indice g�n�r� par son identifiant idCapteur.
//				Pour �tre certain de retourner le bon Capteur et non pas un autre membre de la liste cha�n�e,
//				on parcours la liste et on retourne le premier dont l'identifiant correspond (donc en cas de doublons, le prmier aussi).
//				Si le Capteur d'identifiant idCapteur n'existe pas dans la TableHachage courante,
//				on retourne un pointeur null nullptr.
{
	// Cr�ation et initialisation de la variable de retour
	Capteur* capteur = nullptr;
	capteur = table[Hacher( idCapteur )];

	// V�rification de l'identifiant
	while ( capteur != nullptr )
	{
		if ( capteur->GetID( ) == idCapteur )
		{
			return capteur;		// Retour du premier capteur dont l'identifiant correspond
		}
		else
		{
			capteur = capteur->GetSuivant( );
		}
	}

	// Si on arrive ici, c'est que ce capteur n'existe pas : on retourne un pointeur null
	return capteur;

} //----- Fin de GetCapteur

//------------------------------------------------- Surcharge d'op�rateurs
TableHachage & TableHachage::operator= ( const TableHachage & uneTableHachage )
// Algorithme :	Si on n'est pas en train de faire uneTableHachage = uneTableHachage,
//				on "copie" tout les champs :
//				on les modifie pour qu'ils soient comme ceux de uneTableHachage.
//				On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	if ( this != &uneTableHachage )
	{
		// D�sallocation
		Liberer( );

		// R�allocation
		tailleTable = uneTableHachage.tailleTable;
		nombrePremier = uneTableHachage.nombrePremier;
		table = new Capteur*[tailleTable];

		for ( int i = 0; i < tailleTable; i++ )
		{
			// Cr�ation variables de recopie des collisions (r�initialisation � chaque boucle)
			Capteur* c = nullptr;
			Capteur* cSuivUneTableDeHachage = nullptr;

			// Si il y a un capteur � l'indice i
			if ( uneTableHachage.table[i] )
			{
				table[i] = new Capteur( *uneTableHachage.table[i] );	// On le recopie (et notre table ne g�re que des allocations dynamiques)
			}
			// Sinon on initialise � nullptr;
			else
			{
				table[i] = nullptr;
			}

			// Recopie des collisions
			c = table[i];
			if ( uneTableHachage.table[i] )
			{
				cSuivUneTableDeHachage = uneTableHachage.table[i]->GetSuivant();
			}

			while ( cSuivUneTableDeHachage )
			{
				Capteur* nouveauSuivant = new Capteur( *cSuivUneTableDeHachage );	// Notre table ne g�re que des allocation dynamiques
				c->SetSuivant( nouveauSuivant );
				c = c->GetSuivant( );
				cSuivUneTableDeHachage = cSuivUneTableDeHachage->GetSuivant( );
			}
		}		
	} //----- Fin de for ( i<tailleTable ) 

	return *this;

} //----- Fin de operator=

Capteur *& TableHachage::operator[] ( int index )
// Algorithme :	Retourne un pointeur vers le premier Capteur pr�sent dans table � l'indice index,
//				sous forme d'une r�f�rence non-constante (op�rande de gauche).
//				Attention, pas de v�rification de l'int�grit� du pointeur retourn� (nullptr ou non).
//				Gr�ce � l'initialisation de la table, ce pointeur ne pourra pas pointer vers une zone m�moire prot�g�e.
{
	return table[index];
}

Capteur *& TableHachage::operator[] ( int index ) const
// Algorithme :	Retourne un pointeur vers le premier Capteur pr�sent dans table � l'indice index,
//				sous forme d'une r�f�rence constante (op�rande de droite uniquement).
//				Attention, pas de v�rification de l'int�grit� du pointeur retourn� (nullptr ou non).
//				Gr�ce � l'initialisation de la table, ce pointeur ne pourra pas pointer vers une zone m�moire prot�g�e.
{
	return table[index];
}

//-------------------------------------------- Constructeurs - destructeur
TableHachage::TableHachage( const TableHachage & uneTableHachage ) :
	tailleTable( uneTableHachage.tailleTable ),
	nombrePremier( uneTableHachage.nombrePremier )
// Algorithme :	Initialisation des attributs � partir de ceux de uneTableHachage,
//				puis recopie des donn�es de table � partir de celles de uneTableHachage.
//				Allocation dynamique pour la nouvelle table. Tant qu'il y a collision dans
//				uneTableDeHachage, on continue � g�n�rer dynamiquement de nouveaux capteurs
//				� partir de ceux de uneTableDeHachage et � les ins�rer dans la nouvelle liste cha�n�e (si n�cesssaire).
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <TableHachage>" << endl;
#endif

	table = new Capteur*[tailleTable];
	
	for ( int i = 0; i < tailleTable; i++ )
	{
		// Cr�ation variables de recopie des collisions (r�initialisation � chaque boucle)
		Capteur* c = nullptr;
		Capteur* cSuivUneTableDeHachage = nullptr;

		// Allocation
		table[i] = new Capteur( *uneTableHachage.table[i] );

		// Recopie des collisions
		c = table[i];
		if ( uneTableHachage.table[i] )
		{
			cSuivUneTableDeHachage = uneTableHachage.table[i]->GetSuivant();
		}
		while ( cSuivUneTableDeHachage != nullptr )
		{
			Capteur* nouveauSuivant = new Capteur( *cSuivUneTableDeHachage );	// Notre table ne g�re que des allocation dynamiques
			c->SetSuivant( nouveauSuivant );
			c = c->GetSuivant( );
			cSuivUneTableDeHachage = cSuivUneTableDeHachage->GetSuivant( );
		}
	}
} //----- Fin de TableHachage (constructeur de copie)

TableHachage::TableHachage ( int taille, int nbPremier ):
	tailleTable( taille ), nombrePremier( nbPremier )
// Algorithme :	Construit une instance de TableHachage,
//				et initialise tout les pointeurs de table � nullptr pour �viter beaucoup de soucis par la suite.
{
#ifdef MAP
	cout << "Appel au constructeur de <TableHachage>" << endl;
#endif

	table = new Capteur*[ tailleTable ];
	// Initialisation �vitant une tonne de bugs :
	for ( int i = 0; i < tailleTable; i++ )
	{
		table[i] = nullptr;
	}
} //----- Fin de TableHachage


TableHachage::~TableHachage ( )
// Algorithme :	Nous sommes en pr�sence d'un tabeau allou� dynamiquement de pointeurs
//				allou�s dynamiquement.
//				On d�truit donc chaque �l�ment du tableau table (qui gr�ce � l'appel du destructeur
//				de Capteur va d�truire la liste ch�in�e),
//				puis on d�truit le tableau lui-m�me.
//				Un simple delete[] table n'aurait pas lib�r� toute la m�moire.
{
#ifdef MAP
	cout << "Appel au destructeur de <TableHachage>" << endl;
#endif

	Liberer( );

} //----- Fin de ~TableHachage

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M�thodes prot�g�es
void TableHachage::Liberer ( )
// Algorithme :	Nous sommes en pr�sence d'un tabeau allou� dynamiquement de pointeurs
//				allou�s dynamiquement.
//				On d�truit donc chaque �l�ment du tableau table (qui gr�ce � l'appel du destructeur
//				de Capteur va d�truire la liste ch�in�e),
//				puis on d�truit le tableau lui-m�me.
//				Un simple delete[] table n'aurait pas lib�r� toute la m�moire.
{
	for ( int i = 0; i < tailleTable; i++ )
	{
		Capteur* c = table[i];
		Capteur* cTampon = nullptr;
		if ( c )
		{
			c = table[i]->GetSuivant();		// On conserve un pointeur vers l'�l�ment suivant avant la d�sallocation
			delete table[i];				// D�sallocation du premier �l�ment
			while ( c )
			{
				cTampon = c->GetSuivant();	// On conserve un pointeur vers l'�l�ment suivant avant la d�sallocation
				delete c;					// D�sallocation de l'�l�ment suivant dans la liste cha�n�e
				c = cTampon;				// On reprend la valeur tamponn�e deux lignes plus haut
			}
		}
	}

	delete[] table;
	tailleTable = 0;
}
