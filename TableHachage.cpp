/*************************************************************************
					TableHachage  -  description
-------------------
début                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Réalisation de la classe <TableHachage> (fichier TableHachage.cpp) --

//---------------------------------------------------------------- INCLUDE
using namespace std;
#include <iostream>
#include <cstddef>		// Utilisation de nullptr

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "TableHachage.h"

//------------------------------------------------------------- Constantes
//#define MAP	// Permet de visualiser les appels aux constructeurs/destructeurs et certains éléments de debugging

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

int TableHachage::Hacher ( Capteur * capteur ) const
// Algorithme :	Retroune Hacher( int ) avec l'identifiant du Capteur pointé par capteur en paramètre.
{
	return Hacher( capteur->GetID( ) );

} //----- Fin de Hacher ( Capteur* )

int TableHachage::Hacher ( int idCapteur ) const
// Algorithme :	Retourne une clef générée avec une fonction de hachage basique.
//				Cette clef est générée en faisant l'identifiant idCapteur modulo avec un nombre premier
//				(strictement supérieur à la taille maximale de la table si on veut que ça soit utile)
//				puis modulo la taille du tableau pour faire en sorte que la clef soit l'indice d'une
//				case du tableau. Permet alors un accès en O(1), sauf collisions.
//				Le nombre premier permet d'éviter toutes les collisions liées au multiples.
{
	return ( idCapteur % nombrePremier) % tailleTable;

} //----- Fin de Hacher ( int )

void TableHachage::Inserer ( Capteur * capteur )
// Algorithme :	On génère la clef à partir du Capteur* capteur.
//				S'il s'avère que cette case du tableau table n'est pas occupée, on fait seulement
//				pointer le pointeur de cette cas vers la même chose que capteur.
//				Sinon, il y a collision. On traite les collisions par liste chaînée avec insertion en queue :
//				tant que le pointeur suivant du Capteur pointé par le Capteur* c n'est pas null,
//				on avance dans la liste chaînée. Dès qu'on est arrivé au bout de la liste (i.e. suivant == nullptr),
//				on fait pointer suivant vers capteur.
// NB :	Le SI et le SINON sont inversés entre la description et l'implémentation, mais il était plus simple de faire
//		dans ce sens pour les deux.
{
	// Création de variables pratiques
	int indice = Hacher( capteur );		// Génération de la clef
		// Pour traiter les collisions :
	Capteur* c = table[indice];			// Capteur courant
	Capteur* cPrecedent = nullptr;		// Capteur précédent le courant

	// Tant qu'il y a collision, on avance dans la liste chaînée
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
		table[indice] = capteur;			// Insertion dans la première case
	}

}  //----- Fin de Inserer

Capteur * TableHachage::GetCapteur ( int idCapteur ) const
// Algorithme :	Retourne le capteur d'identifiant idCapteur présent à l'indice généré par son identifiant idCapteur.
//				Pour être certain de retourner le bon Capteur et non pas un autre membre de la liste chaînée,
//				on parcours la liste et on retourne le premier dont l'identifiant correspond (donc en cas de doublons, le prmier aussi).
//				Si le Capteur d'identifiant idCapteur n'existe pas dans la TableHachage courante,
//				on retourne un pointeur null nullptr.
{
	// Création et initialisation de la variable de retour
	Capteur* capteur = nullptr;
	capteur = table[Hacher( idCapteur )];

	// Vérification de l'identifiant
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

//------------------------------------------------- Surcharge d'opérateurs
TableHachage & TableHachage::operator= ( const TableHachage & uneTableHachage )
// Algorithme :	Si on n'est pas en train de faire uneTableHachage = uneTableHachage,
//				on "copie" tout les champs :
//				on les modifie pour qu'ils soient comme ceux de uneTableHachage.
//				On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	if ( this != &uneTableHachage )
	{
		// Désallocation
		Liberer( );

		// Réallocation
		tailleTable = uneTableHachage.tailleTable;
		nombrePremier = uneTableHachage.nombrePremier;
		table = new Capteur*[tailleTable];

		for ( int i = 0; i < tailleTable; i++ )
		{
			// Création variables de recopie des collisions (réinitialisation à chaque boucle)
			Capteur* c = nullptr;
			Capteur* cSuivUneTableDeHachage = nullptr;

			// Si il y a un capteur à l'indice i
			if ( uneTableHachage.table[i] )
			{
				table[i] = new Capteur( *uneTableHachage.table[i] );	// On le recopie (et notre table ne gère que des allocations dynamiques)
			}
			// Sinon on initialise à nullptr;
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
				Capteur* nouveauSuivant = new Capteur( *cSuivUneTableDeHachage );	// Notre table ne gère que des allocation dynamiques
				c->SetSuivant( nouveauSuivant );
				c = c->GetSuivant( );
				cSuivUneTableDeHachage = cSuivUneTableDeHachage->GetSuivant( );
			}
		}		
	} //----- Fin de for ( i<tailleTable ) 

	return *this;

} //----- Fin de operator=

Capteur *& TableHachage::operator[] ( int index )
// Algorithme :	Retourne un pointeur vers le premier Capteur présent dans table à l'indice index,
//				sous forme d'une référence non-constante (opérande de gauche).
//				Attention, pas de vérification de l'intégrité du pointeur retourné (nullptr ou non).
//				Grâce à l'initialisation de la table, ce pointeur ne pourra pas pointer vers une zone mémoire protégée.
{
	return table[index];
}

Capteur *& TableHachage::operator[] ( int index ) const
// Algorithme :	Retourne un pointeur vers le premier Capteur présent dans table à l'indice index,
//				sous forme d'une référence constante (opérande de droite uniquement).
//				Attention, pas de vérification de l'intégrité du pointeur retourné (nullptr ou non).
//				Grâce à l'initialisation de la table, ce pointeur ne pourra pas pointer vers une zone mémoire protégée.
{
	return table[index];
}

//-------------------------------------------- Constructeurs - destructeur
TableHachage::TableHachage( const TableHachage & uneTableHachage ) :
	tailleTable( uneTableHachage.tailleTable ),
	nombrePremier( uneTableHachage.nombrePremier )
// Algorithme :	Initialisation des attributs à partir de ceux de uneTableHachage,
//				puis recopie des données de table à partir de celles de uneTableHachage.
//				Allocation dynamique pour la nouvelle table. Tant qu'il y a collision dans
//				uneTableDeHachage, on continue à générer dynamiquement de nouveaux capteurs
//				à partir de ceux de uneTableDeHachage et à les insérer dans la nouvelle liste chaînée (si nécesssaire).
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <TableHachage>" << endl;
#endif

	table = new Capteur*[tailleTable];
	
	for ( int i = 0; i < tailleTable; i++ )
	{
		// Création variables de recopie des collisions (réinitialisation à chaque boucle)
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
			Capteur* nouveauSuivant = new Capteur( *cSuivUneTableDeHachage );	// Notre table ne gère que des allocation dynamiques
			c->SetSuivant( nouveauSuivant );
			c = c->GetSuivant( );
			cSuivUneTableDeHachage = cSuivUneTableDeHachage->GetSuivant( );
		}
	}
} //----- Fin de TableHachage (constructeur de copie)

TableHachage::TableHachage ( int taille, int nbPremier ):
	tailleTable( taille ), nombrePremier( nbPremier )
// Algorithme :	Construit une instance de TableHachage,
//				et initialise tout les pointeurs de table à nullptr pour éviter beaucoup de soucis par la suite.
{
#ifdef MAP
	cout << "Appel au constructeur de <TableHachage>" << endl;
#endif

	table = new Capteur*[ tailleTable ];
	// Initialisation évitant une tonne de bugs :
	for ( int i = 0; i < tailleTable; i++ )
	{
		table[i] = nullptr;
	}
} //----- Fin de TableHachage


TableHachage::~TableHachage ( )
// Algorithme :	Nous sommes en présence d'un tabeau alloué dynamiquement de pointeurs
//				alloués dynamiquement.
//				On détruit donc chaque élément du tableau table (qui grâce à l'appel du destructeur
//				de Capteur va détruire la liste châinée),
//				puis on détruit le tableau lui-même.
//				Un simple delete[] table n'aurait pas libéré toute la mémoire.
{
#ifdef MAP
	cout << "Appel au destructeur de <TableHachage>" << endl;
#endif

	Liberer( );

} //----- Fin de ~TableHachage

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void TableHachage::Liberer ( )
// Algorithme :	Nous sommes en présence d'un tabeau alloué dynamiquement de pointeurs
//				alloués dynamiquement.
//				On détruit donc chaque élément du tableau table (qui grâce à l'appel du destructeur
//				de Capteur va détruire la liste châinée),
//				puis on détruit le tableau lui-même.
//				Un simple delete[] table n'aurait pas libéré toute la mémoire.
{
	for ( int i = 0; i < tailleTable; i++ )
	{
		Capteur* c = table[i];
		Capteur* cTampon = nullptr;
		if ( c )
		{
			c = table[i]->GetSuivant();		// On conserve un pointeur vers l'élément suivant avant la désallocation
			delete table[i];				// Désallocation du premier élément
			while ( c )
			{
				cTampon = c->GetSuivant();	// On conserve un pointeur vers l'élément suivant avant la désallocation
				delete c;					// Désallocation de l'élément suivant dans la liste chaînée
				c = cTampon;				// On reprend la valeur tamponnée deux lignes plus haut
			}
		}
	}

	delete[] table;
	tailleTable = 0;
}
