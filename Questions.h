#pragma once

/* QUESTIONS A POSER LORS DE LA SEANCE DE LA RENTREE
 *
 * Quelle tronche a la fin de ligne ? (\r\n, \n, ... ?) \R\N
 * De quelle tailles sont les IDs des capteurs ? (long int, int ?) Et l'ID max vaut ? LONG
 * Les IDs des capteurs sont-ils aléatoires ou sont-ils rentrés par ordre croissant ? ALEATOIRE
 *		Si croissant, de 1 en 1 en partant de 0 ?
 * Quelle précision sur les % ? Remplace-t-on le "pas de données" par 0% ? PRECISION C++/ 0%
 * Pour la question pseudo-bonus (5) :
 *		- Lorsqu'on n'a pas de données, on ne compte pas les endroits sans données ? ON NE COMPTE PAS
 *		- Doit-on prendre en compte le temps de déplacement sur les segments précédents ? OUI
 *		
 */