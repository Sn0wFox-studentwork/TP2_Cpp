/*************************************************************************
                           Vecteur  -  description
                             -------------------
    début                : 19/10/2015
    copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface de la classe <Vecteur> (fichier Vecteur.h) ------
#if ! defined ( VECTEUR_H )
#define VECTEUR_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
const int TAILLE_MAX_BASE = 5;

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Vecteur>
//
//
//------------------------------------------------------------------------

template <typename T>
class Vecteur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void insererFin( T objet );
    //Insere à la fin

    int rechercherPosition( T objet ) const;
	// Rechercher l'indice d'un objet
	// Necessite le surcharge de > sur le type T
	// Renvoie -1 si non trouvé

	int GetTaille() const { return tailleActuelle;  }

//------------------------------------------------- Surcharge d'opérateurs
    Vecteur & operator = ( const Vecteur & unVecteur );
    // Mode d'emploi :
    //
    // Contrat :
    //

	T& operator[] ( int index );		// ATTENTION : retour de ref, sinon tout plante
    // Acces à l'element contenu à l'index index

	T operator[] ( int index ) const;
	// Acces à l'element contenu à l'index index

//-------------------------------------------- Constructeurs - destructeur
    Vecteur ( const Vecteur & unVecteur );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Vecteur ( );		// TODO: pour aller + vite et ne faire qu'une seule alloc, mettre un param par defaut :
						// Vecteur( unsigned int taille = 5 ) (5 me semble pas mal vu que les plus petits font 4 ou 5 cases)
						// On pourra alors mettre ce qu'on veut a l'appel et gagner du temps ( pour embouteillage par exemple )
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Vecteur ( );
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
int tailleActuelle;
int tailleMax;
T* elements;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Vecteur>
template <class T>
void Vecteur<T>::insererFin(T objet)
//Algorithme :  regarde si il reste de la place prête.
//              Si ce n'est pas le cas, réalloue la mémoire de sorte à recreer de la place pour des insertions.
//              Ensuite, insere l'objet à la fin de la liste.
{
	if (tailleActuelle >= tailleMax)
	{
		tailleMax *= 2;
		cout << "Taille max : " << tailleMax << endl;
		T* temp = new T[tailleMax];
		for (int i = 0; i < tailleActuelle; i++)
		{
			temp[i] = elements[i];
		}
		delete[] elements;
		elements = temp;
	}
	elements[tailleActuelle++] = objet;

}//------Fin de insererFin

template<class T>
int Vecteur<T>::rechercherPosition(T objet) const
//Algorithme :  On suppose que les objets sont ajoutés de manière ordonnées
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
} //----- Fin de rechercherPosition

template<class T>
T& Vecteur<T>::operator[] (int index)
// Algorithme : Retour par reference
{
	if (index >= 0 || index < tailleActuelle)
	{
		return elements[index];
	}
	cout << "Error, attempted to access an element out of range";
	return elements[index];
	// TODO: Mettre une exception ? Dans tous les cas, il faut un retour, sinon ça risque de planter

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
	// TODO: Mettre une exception ? Dans tous les cas, il faut un retour, sinon ça risque de planter

} //----- Fin de operator[]


  //------------------------------------------------- Surcharge d'opérateurs
template <class T>
Vecteur<T> & Vecteur<T>::operator = ( const Vecteur<T> & unVecteur )
// Algorithme : Si on n'est pas en train de faire unObjetDeMaClasse = unObjetDeMaClasse,
//					on "copie" tout les champs :
//					on les modifie pour qu'ils soient comme ceux de unObjetDeMaClasse.
//					On retourne *this pour la bonne marche de la surcharge d'operateur
//
{
	if (this != &unVecteur)
	{
		tailleActuelle = unVecteur.tailleActuelle;
		tailleMax = unVecteur.tailleMax;
		elements = new T[tailleMax];
		for (int i = 0; i<unVecteur.tailleActuelle; i++)
		{
			elements[i] = unVecteur[i];
		}
	}
	return *this;

} //----- Fin de operator =


  //-------------------------------------------- Constructeurs - destructeur
template <class T>
Vecteur<T>::Vecteur( const Vecteur<T> & unVecteur )
// Algorithme : copie sequentielle d'éléments
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <Vecteur>" << endl;
#endif
	tailleActuelle = unVecteur.tailleActuelle;
	tailleMax = unVecteur.tailleMax;
	elements = new T[tailleMax];
	for (int i = 0; i<unVecteur.tailleActuelle; i++)
	{
		elements[i] = unVecteur[i];
	}

} //----- Fin de Vecteur (constructeur de copie)

template<class T>
Vecteur<T>::Vecteur()
// Algorithme : Cree un vecteur avec de la place prête pour TAILLE_MAX_BASE insertions
//
{
#ifdef MAP
	cout << "Appel au constructeur de <Vecteur>" << endl;
#endif
	tailleActuelle = 0;
	tailleMax = TAILLE_MAX_BASE;
	elements = new T[tailleMax];
} //----- Fin de Vecteur

template <class T>
Vecteur<T>::~Vecteur()
// Algorithme : Indique qu'il faut supprimer un tableau d'éléments
// donc potentiellement d'objets
{
#ifdef MAP
	cout << "Appel au destructeur de <Vecteur>" << endl;
#endif
	delete[] elements;
} //----- Fin de ~Vecteur



#endif // VECTEUR_H
