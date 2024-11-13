#include <stdio.h> 
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


#include "const.h"
static int Min[NEt], Max[NEt];
#include "funRewardMit.c"


void  usage1()
{
	printf("Usage : ./StateReward gamma seui1 seuil2 seuil3 seuil4 \n");
	exit(1);
}

int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
int a , b;
int taille = BufferSize+1;
int MAT[taille][taille];

if (argc!=6) 
   usage1();
   
            ++argv;
			gamma12 = atof(*argv)/10;
			++argv;
			seuil1= atoi(*argv);
			++argv;
			seuil2= atoi(*argv);
			++argv;
			seuil3= atoi(*argv);
			++argv;
			seuil4= atoi(*argv);

FILE *f1=fopen("StateReward.matrix","w");

int i,j;

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		MAT[i][j] = 0;
	}
}

double engSLB1, engLB1;
double engSLB2, engLB2;
double Inservice1,Outservice1;

for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		engSLB1 = engSLB2 = engLB1 = engLB2 = 0;
		
		if(i <= seuil1) // palier 1
		{
			 Inservice1 = min(i, C);
			 Outservice1 = C - Inservice1; 
			 ConsMoy1 = (Inservice1*e1 + Outservice1*e1idle );
		}
		if( i > seuil1 && i <= seuil2 ) // palier 2
		{
			  Inservice1 = min(tab[i], C);
			  Outservice1 = C - Inservice1; 
			  ConsMoy1 = (Inservice1*e2 + Outservice1*e2idle );
		}
		if( i > seuil2 && i <= seuil3) // palier 3
		{
		     Inservice1 = min(tab[i], C);
			 Outservice1 = C - Inservice1; 
			 ConsMoy1 = (Inservice1*e3 + Outservice1*e3idle );
    	}
		if( i > seuil3 && i <= seuil4) // palier 4
		{
		     Inservice1 = min(tab[i], C);
			 Outservice1 = C - Inservice1; 
		     ConsMoy1 = (Inservice1*e4 + Outservice1*e4idle );
		}
		if( i > seuil4) // palier 5
		{
             Inservice1 = min(tab[i], C);
			 Outservice1 = C - Inservice1; 
			 ConsMoy1 = (Inservice1*e5 + Outservice1*e5idle );
		}
	}
	
}

fprintf(f1,"%5d \n",taille);
for(i=0; i<taille; i=i+1){
	
	for(j=0; j<taille; j=j+1){
		
		fprintf(f1,"%5d",MAT[i][j]);
	}
	fprintf(f1,"\n");
}

fclose(f1);



}
