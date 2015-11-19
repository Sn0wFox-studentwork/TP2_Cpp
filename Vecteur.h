/*************************************************************************
                           Vecteur  -  description
                             -------------------
    d�but                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Vecteur> (fichier Vecteur.h) ------
#if ! defined ( VECTEUR_H )
#define VECTEUR_H

//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
using namespace std;
//#define MAP

//------------------------------------------------------------- Constantes
const int TAILLE_MAX_BASE = 5;

//------------------------------------------------------------------------
// R�le de la classe <Vecteur>
// Vecteur est un tableau dynamique. Sa taille s'adapte automatiquement � ce
// qu'on tente de lui ajouter. La surcharge de [i] permet d'acc�der au i�me
// �l�ment ajout�.
// Elle permet de manipuler plus facilement des ensembles de donn�es,
// et nottement de faire un retour simple de plusieurs valeurs.
//------------------------------------------------------------------------

template <typename T>
class Vecteur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

    void InsererFin( T objet );
	// Mode d'emploi :	Insere un �l�ment � la fin

    int RechercherPosition( T objet ) const;
	// Mode d'emploi :	Rechercher l'indice d'un objet.
	//					Necessite le surcharge de > sur le type T.
	//					Renvoie -1 si non trouv�.

	int GetTaille() const { return tailleActuelle;  }
	// Mode d'emploi :	Retourne la valeur de l'attribut tailleActuelle = nombre d'�l�ments pr�sent dans le Vecteur

//------------------------------------------------- Surcharge d'op�rateurs
    Vecteur & operator = ( const Vecteur & unVecteur );
	// Mode d'emploi :	R�affecte l'instance courante pour la rendre en tout point similaire � unVecteur.
	//					Les deux Vecteurs auront alors les m�me donn�es, mais non partag�es (copies).

	T& operator[] ( int index );		// ATTENTION : retour de ref, sinon tout plante
	// Mode d'emploi :	Acces � l'element contenu � l'index index
	//					l'index doit �tre existant, c'est a dire positif et inferieur � tailleActuelle

	T operator[] ( int index ) const;
	// Mode d'emploi :	Acces � l'element contenu � l'index index
	//					l'index doit �tre existant, c'est a dire positif et inferieur � tailleActuelle

//-------------------------------------------- Constructeurs - destructeur
    Vecteur ( const Vecteur & unVecteur );
	// Mode d'emploi :	Consruit une nouvelle instance de Vecteur � partir d'un Vecteur existant unVecteur.
	//					Les deux Vecteurs auront alors les m�me donn�es, mais non partag�es (copies).

    Vecteur ( int tailleMax = TAILLE_MAX_BASE );
	// Mode d'emploi :  Construit une nouvelle instance de vecteur vide, avec une taille m�moire pr�allou�e pour tailleMax
	//                  �l�ments.
	// Contrat :		Envoyer une taille r�aliste (positive)

    virtual ~Vecteur ( );
	// Mode d'emploi :  Detruit l'instance de Vecteur pour laquelle la m�thode est appel�e.

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Attributs prot�g�s
int tailleActuelle;
int tailleMax;
T* elements;

};

//----------------------------------------- R�alisation Template de <Vecteur>
template <class T>
void Vecteur<T>::InsererFin(T objet)
//Algorithme :  regarde si il reste de la place pr�te.
//              Si ce n'est pas le cas, r�alloue la m�moire de sorte � recreer de la place pour des insertions.
//              Ensuite, insere l'objet � la fin de la liste.
{
	if (tailleActuelle >= tailleMax)
	{
		tailleMax *= 2;
		T* temp = new T[tailleMax];
		for (int i = 0; i < tailleActuelle; i++)
		{
			temp[i] = elements[i];
		}
		delete[] elements;
		elements = temp;
	}
	elements[tailleActuelle++] = objet;

}//------Fin de InsererFin

template<class T>
int Vecteur<T>::RechercherPosition(T objet) const
//Algorithme :  On suppose que les objets sont ajout�s de mani�re ordonn�es
//              on va donc faire une recherche dichotomique sur l'intervalle [indexMin, indexMax]
{
	int indexMax = tailleActuelle - 1;
	int indexMin = 0;
	int i = (indexMax - indexMin) / 2;
	while (indexMax != indexMin && elements[i] != objet)
	{
		if (elements[i] < objet)
		{
			indexMin = i;
		}
		else
		{
			indexMax = i;
		}
		i = (indexMax - indexMin) / 2;
	}
	if (elements[i] == objet)
	{
		return i;
	}
	return -1;
} //----- Fin de RechercherPosition

  //------------------------------------------------- Surcharge d'op�rateurs
template <class T>
Vecteur<T> & Vecteur<T>::operator = ( const Vecteur<T> & unVecteur )
// Algorithme :		Si on n'est pas en train de faire unVecteur = unVecteur,
//					on "copie" tout les champs :
//					on les modifie pour qu'ils soient comme ceux de unVecteur.
//					On retourne *this pour la bonne marche de la surcharge d'operateur.
{
	if ( this != &unVecteur )
	{
		tailleActuelle = unVecteur.tailleActuelle;
		tailleMax = unVecteur.tailleMax;
		delete[] elements;
		elements = new T[tailleMax];
		for (int i = 0; i<tailleMax; i++)
		{
			elements[i] = unVecteur[i];
		}
	}
	return *this;

} //----- Fin de operator =

template<class T>
T& Vecteur<T>::operator[] ( int index )
// Algorithme : Retour par reference
{
	if ( index >= 0 || index < tailleActuelle )
	{
		return elements[index];
	}
	cout << "Error, attempted to access an element out of range";
	return elements[index];
	// TODO: Mettre une exception ? Dans tous les cas, il faut un retour, sinon �a risque de planter

} //----- Fin de operator[]

template<class T>
T Vecteur<T>::operator[] ( int index ) const
// Algorithme : Retour par reference
{
	if ( index >= 0 || index < tailleActuelle )
	{
		return elements[index];
	}
	cout << "Error, attempted to access an element out of range";
	return elements[index];
	// TODO: Mettre une exception ? Dans tous les cas, il faut un retour, sinon �a risque de planter

} //----- Fin de operator[]


//-------------------------------------------- Constructeurs - destructeur
template <class T>
Vecteur<T>::Vecteur( const Vecteur<T> & unVecteur ) :	tailleActuelle( unVecteur.tailleActuelle ),
														tailleMax( unVecteur.tailleMax )
// Algorithme : copie sequentielle d'�l�ments
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Vecteur>" << endl;
#endif

	elements = new T[tailleMax];
	for (int i = 0; i<tailleMax; i++)
	{
		elements[i] = unVecteur[i];
	}

} //----- Fin de Vecteur (constructeur de copie)

template<class T>
Vecteur<T>::Vecteur( int tMax ) : tailleActuelle(0), tailleMax( tMax )
// Algorithme : Cree un vecteur avec de la place pr�te pour tMax insertions
{
#ifdef MAP
	cout << "Appel au constructeur de <Vecteur>" << endl;
#endif

	elements = new T[tailleMax];
	for (int i = 0; i<tailleMax; i++)
	{
		elements[i] = 0;
	}

} //----- Fin de Vecteur

template <class T>
Vecteur<T>::~Vecteur( )
// Algorithme : Indique qu'il faut supprimer un tableau d'�l�ments
// donc potentiellement d'objets
{
#ifdef MAP
	cout << "Appel au destructeur de <Vecteur>" << endl;
#endif
	delete[] elements;
} //----- Fin de ~Vecteur



#endif // VECTEUR_H
