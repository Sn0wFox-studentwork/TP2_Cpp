/*************************************************************************
${file_base}  -  description
-------------------
début                : ${date}
copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Réalisation de la classe <${file_base}> (fichier ${file_name}) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "TableHachage.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
// type ${file_base}::Méthode ( liste de paramètres )
	// Algorithme :
	//
	//{
	//} //----- Fin de Méthode

int TableHachage::Hacher ( Capteur * capteur )
{
	return Hacher( capteur->GetID( ) );

} //----- Fin de Hacher ( Capteur* )

int TableHachage::Hacher ( int idCapteur )
{
	return ( idCapteur % nombrePremier) % tailleTable;

} //----- Fin de Hacher ( int )

void TableHachage::Inserer ( Capteur * capteur )
{
	int indice = Hacher( capteur );
	Capteur* c = table[indice];
	Capteur* cPrecedent = nullptr;
	while ( c != nullptr )
	{
		cPrecedent = c;
		//c = c->getNext( );
	}
	
	if ( cPrecedent )
	{
		//c->setNext( capteur );
	}
	else
	{
		table[indice] = capteur;
	}
	

}  //----- Fin de Inserer

Capteur * TableHachage::GetCapteur ( int idCapteur )
{
	Capteur* capteur = nullptr;
	capteur = table[Hacher( idCapteur )];

	while ( capteur != nullptr )
	{
		if ( capteur->GetID( ) == idCapteur )
		{
			return capteur;
		}
		else
		{
			// capteur = capteur->getNext( );
		}
	}

	// Si on arrive ici, c'est que ce capteur n'existe pas : on retourne un pointeur null
	return capteur;

} //----- Fin de GetCapteur


//------------------------------------------------- Surcharge d'opérateurs
TableHachage & TableHachage::operator= ( const TableHachage & uneTableHachage )
// Algorithme :		Si on n'est pas en train de faire uneTableHachage = uneTableHachage,
//					on "copie" tout les champs :
//					on les modifie pour qu'ils soient comme ceux de uneTableHachage.
//					On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	if ( this != &uneTableHachage )
	{
		tailleTable = uneTableHachage.tailleTable;
		nombrePremier = uneTableHachage.nombrePremier;

		table = new Capteur*[tailleTable];
		for ( int i = 0; i < tailleTable; i++ )
		{
			table[i] = uneTableHachage.table[i];
		}
	}

	return *this;

} //----- Fin de operator=

Capteur *& TableHachage::operator[]( int index )
{
	return table[index];
}

Capteur *& TableHachage::operator[]( int index ) const
{
	return table[index];
}

//-------------------------------------------- Constructeurs - destructeur
TableHachage::TableHachage( const TableHachage & uneTableHachage ) :
	tailleTable(uneTableHachage.tailleTable),
	nombrePremier(uneTableHachage.nombrePremier)
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <${file_base}>" << endl;
#endif

	table = new Capteur*[tailleTable];
	for ( int i = 0; i < tailleTable; i++ )
	{
		table[i] = uneTableHachage.table[i];
	}
} //----- Fin de ${file_base} (constructeur de copie)

TableHachage::TableHachage ( int taille, int nbPremier ):
	tailleTable( taille ), nombrePremier( nbPremier )
{
#ifdef MAP
	cout << "Appel au constructeur de <${file_base}>" << endl;
#endif

	table = new Capteur*[ tailleTable ];
	// Initialisation évitant une tonne de bugs :
	for ( int i = 0; i < tailleTable; i++ )
	{
		table[i] = nullptr;
	}
} //----- Fin de ${file_base}


TableHachage::~TableHachage()
{
#ifdef MAP
	cout << "Appel au destructeur de <${file_base}>" << endl;
#endif

	delete[] table;
} //----- Fin de ~${file_base}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées