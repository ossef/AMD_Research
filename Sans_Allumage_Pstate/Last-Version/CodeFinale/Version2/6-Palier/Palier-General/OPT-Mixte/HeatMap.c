

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

#define EB 1 //energie de migrations


/* ------------ Seuils de palier ---------------------------------------------------- */

#define seuil1 3
#define seuil2 6
#define seuil3 12
#define seuil4 24
#define seuil5 48


#define BufferSize 90
#define C 10

typedef struct Couple
{
   int state1;
   int state2;
}couple;

int min (int a, int b){ return a < b ? a : b ;}

long double Eng_Etat(int a, int b, int NbMigrations, int e)
{
	int  Inservice1, Outservice1, Inservice2, Outservice2;
	long double ConsMoy1 = 0;
	long double ConsMoy2 = 0;
	
	Inservice1 = min(a, C);
	Outservice1 = C - Inservice1; 
	
	if(a <= seuil1) // palier 1
			ConsMoy1 += (Inservice1*e1 + Outservice1*e1idle );
	if(a > seuil1 && a <= seuil2)
		    ConsMoy1 += (Inservice1*e2 + Outservice1*e2idle );
	if(a > seuil2 && a <= seuil3)
			ConsMoy1 += (Inservice1*e3 + Outservice1*e3idle );
	if(a > seuil3 && a <= seuil4)
		    ConsMoy1 += (Inservice1*e4 + Outservice1*e4idle );
	if(a > seuil4 && a <= seuil5)
		    ConsMoy1 += (Inservice1*e5 + Outservice1*e5idle );
	if(a > seuil5)
			ConsMoy1 += (Inservice1*e6 + Outservice1*e6idle );
				
	Inservice2 = min(b, C);
	Outservice2 = C - Inservice2; 
	
	if(b <= seuil1) // palier 1
			ConsMoy2 += (Inservice2*e1 + Outservice2*e1idle );
	if(b > seuil1 && b <= seuil2)
		    ConsMoy2 += (Inservice2*e2 + Outservice2*e2idle );
	if(b > seuil2 && b <= seuil3)
			ConsMoy2 += (Inservice2*e3 + Outservice2*e3idle );
	if(b > seuil3 && b <= seuil4)
		    ConsMoy2 += (Inservice2*e4 + Outservice2*e4idle );
	if(b > seuil4 && b <= seuil5)
		    ConsMoy2 += (Inservice2*e5 + Outservice2*e5idle );
	if(b > seuil5)
			ConsMoy2 += (Inservice2*e6 + Outservice2*e6idle );
	
	return (long double)(ConsMoy1 + ConsMoy2 + /*gamma12*/NbMigrations*e);
}

int Id_Etat(int a)
{
	
	if( a <= seuil1 )
		return 1;
	if ( a > seuil1 && a <= seuil2)
		return 2;
	if ( a > seuil2 && a <= seuil3)
		return 3;
	if ( a > seuil3 && a <= seuil4)
		return 4;
	if (  a > seuil4 && a <= seuil5)
		return 5;
	if (a  >= seuil5)
		return 6;
	
}

int main(argc,argv)
int argc;
char *argv[];
{

int i,j,a,b,c,d,s,r,st1,st2,e,t;
FILE *pf1;
long double EngST, minEng, EngTmp;

int taille = (BufferSize+1)*(BufferSize+1);
couple TabInit[taille]; // etat initaile
couple TabOpt[taille];  // etat de migration
long double EngInit[taille];
long double EngOpt[taille];

int NMigrations[taille]; // Nombre de migration

	for ( i = 0 ; i< taille ; i++ )
	{
		TabOpt[i].state1 = -1;
		TabOpt[i].state2 = -1;
		NMigrations[i] = 0;
	}

	int x = 0;
	for ( i = 0 ; i<= BufferSize ; i++ )
	{
		for ( j = 0 ; j<= BufferSize ; j++ )
		{
			 TabInit[x].state1 = i;
			 TabInit[x].state2 = j;
			 x++;
		}

	}
	
	pf1 = fopen("HeatMap.data","w");
	
	/*t = 0;
	e = 1;
	while( e <= EB )
	{*/
	
		for ( i = 0 ; i< taille ; i++ )
		{
			a = TabInit[i].state1;
			b = TabInit[i].state2;
			
			EngST = Eng_Etat(a, b, 0, EB);
			st1 = Id_Etat(a);
			st2 = Id_Etat(b);
			EngInit[i] = EngST;
			
			
			if(st1 != st2) // Si les P-states sont different, sinon on est à la diagonale 
				{
					s = a + b;
					c = s/2;
					d = s - c;
					
					EngTmp = Eng_Etat(c, d, (int)fabs(c - a), EB);
					
					if( EngTmp < EngST )
							{
								TabOpt[i].state1 = c;
								TabOpt[i].state2 = d;
								NMigrations[i]=  (int)fabs(c - a);
								EngOpt[i] = EngTmp;
							}
				}
			}	
					
	
	
	for ( i = 0 ; i< taille ; i++ )
	{
		if(NMigrations[i] != 0)
		{
			printf("(%d , %d) : %Lf  ---> (%d  , %d) : %Lf et %d Migrations \n",TabInit[i].state1,TabInit[i].state2, EngInit[i], TabOpt[i].state1, TabOpt[i].state2, EngOpt[i], NMigrations[i]);
			fprintf(pf1,"%5d %5d %5d %5d %5d\n",TabInit[i].state1,TabInit[i].state2,NMigrations[i],TabOpt[i].state1,TabOpt[i].state2);
		}
		else
		{
			fprintf(pf1,"%5d %5d NaN   NaN   NaN \n",TabInit[i].state1,TabInit[i].state2);
		}
	}
	fclose(pf1);
	

	
	for( i=0; i< taille ; i++ )
	{
		if(NMigrations[i] != 0)
		{
			for(j = 0; j<= taille ; j++)
			{
				
					if(TabOpt[i].state1 == TabInit[j].state1 && TabOpt[i].state2 == TabInit[j].state2 && NMigrations[j] != 0 )
					{
						printf("Erreur etat : (%d,%d) \n",TabOpt[i].state1,TabOpt[i].state2);
						exit(0);
					}	
			}
		}
	}
	
		
	printf("Proprieté Verifiée ! \n");
	



exit(0);
}

