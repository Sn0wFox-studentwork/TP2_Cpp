/*************************************************************************
Bench  -  description
-------------------
début                : 19/10/2015
copyright            : (C) 2015 par Pericas-Belletier
*************************************************************************/

//---------- Interface des fonctions génériques de <Bench> (fichier Bench.h) ------
#if ! defined ( BENCH_H )
#define BENCH_H

// Version fonction generique :
template<class C, typename retour>
void bench(retour(C::*pf)(), C objet, int repetitions)
// Sans param
{
	clock_t debut = clock();
	for (int i = 0; i < repetitions; i++)
	{
		(objet.*pf)();
	}
	double duree = (double)(clock() - debut) / CLOCKS_PER_SEC;
	cout << "Temps d'execution de " << repetitions << " repetitions : " << duree << " secondes" << endl;
}

template<class C, typename retour, typename param>
void bench(retour(C::*pf)(param), C objet, param p, int repetitions)
// Avec un param
{
	clock_t debut = clock();
	for (int i = 0; i < repetitions; i++)
	{
		(objet.*pf)(p);
	}
	double duree = (double)(clock() - debut) / CLOCKS_PER_SEC;
	cout << "Temps d'execution de " << repetitions << " repetitions : " << duree << " secondes" << endl;
}

template<class C, typename retour, typename param1, typename param2>
void bench(retour(C::*pf)(param1, param2), C objet, param1 p1, param2 p2, int repetitions)
// Avec deux param
{
	clock_t debut = clock();
	for (int i = 0; i < repetitions; i++)
	{
		(objet.*pf)(p1, p2);
	}
	double duree = (double)(clock() - debut) / CLOCKS_PER_SEC;
	cout << "Temps d'execution de " << repetitions << " repetitions : " << duree << " secondes" << endl;
}

template<class C, typename retour, typename param1, typename param2, typename param3>
void bench(retour(C::*pf)(param1, param2, param3), C objet, param1 p1, param2 p2, param3 p3, int repetitions)
// Avec trois param
{
	clock_t debut = clock();
	for (int i = 0; i < repetitions; i++)
	{
		(objet.*pf)(p1, p2, p3);
	}
	double duree = (double)(clock() - debut) / CLOCKS_PER_SEC;
	cout << "Temps d'execution de " << repetitions << " repetitions : " << duree << " secondes" << endl;
}

template<class C, typename retour, typename param1, typename param2, typename param3, typename param4>
void bench(retour(C::*pf)(param1, param2, param3, param4), C objet, param1 p1, param2 p2, param3 p3, param4 p4, int repetitions)
// Avec quatre param
{
	clock_t debut = clock();
	for (int i = 0; i < repetitions; i++)
	{
		(objet.*pf)(p1, p2, p3, p4);
	}
	double duree = (double)(clock() - debut) / CLOCKS_PER_SEC;
	cout << "Temps d'execution de " << repetitions << " repetitions : " << duree << " secondes" << endl;
}
#endif // BENCH_H