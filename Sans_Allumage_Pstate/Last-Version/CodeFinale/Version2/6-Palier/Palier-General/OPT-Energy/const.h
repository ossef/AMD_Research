/*constantes a modifier pour chaque modele*/

#ifndef MON_H
#define MON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NEt               2   /*nombre de composantes du vecteur d'etat*/
#define NbEvtsPossibles   7  /*nombre de vecteurs d'arrivees possibles*/
#define Polynom			0   /* iteration du modele */
#define Epsilon1 0.0		
#define Epsilon2  0.0	
#define MAX_ETAT_MIGRATIONS 1000000

/* --- ---------Parametres de lageneration de chaine, utilisés par  "fun.c" ------------------------- -----*/

#define BufferSize 90 // Taille max de la file
#define C 15	   // Nombre de serveurs

#define Lambda1  20 // Arrivée file1
#define Lambda2  10  // Arrivée file2

#define Mu11 1   // Service, palier1
#define Mu12 1.8 // Service, palier2
#define Mu13 2 // Service, palier3
#define Mu14 2.2 // Service, palier4
#define Mu15 2.4 // Service, palier5
#define Mu16 2.6 // Service, palier6

#define Mu21 1   // Service, palier1
#define Mu22 1.8 // Service, palier2
#define Mu23 2 // Service, palier3
#define Mu24 2.2 // Service, palier4
#define Mu25 2.4 // Service, palier5
#define Mu26 2.6 // Service, palier6

/* --- ---------Parametres energetiques, utilisés par  "funRewardMit.c" ------------------------- -----*/

#define e1 32      // consommation d'un serveur allumé actif, palier 1 
#define e1idle 8  // 75% de gain par rapport à e1

#define e2 55   // consommation d'un serveur allumé  actif, palier 2
#define e2idle 13.75 // 75% de gain par rapport à e2

#define e3 65   // consommation d'un serveur allumé actif, palier 3
#define e3idle 16.25 // 75% de gain par rapport à e3

#define e4 76   // consommation d'un serveur allumé actif, palier 4
#define e4idle 19  // 75% de gain par rapport à e4

#define e5 90  // consommation d'un serveur allumé actif, palier 5
#define e5idle 22.5  // 75% de gain par rapport à e5

#define e6 95  // consommation d'un serveur allumé actif, palier 6
#define e6idle 23.75  // 75% de gain par rapport à e6

#define eb 1 //energie de migrations


typedef struct Couple
{
   int state1;
   int state2;
}couple;


#endif