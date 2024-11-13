// funreward for mitrani's model


#include "const.h"

int min2(int a, int b)
{
	return a<b ? a : b ;
}

long double NombreMoyen1(int tab[],double pi[],int taille) // nombre moyen de clients faisons la queue (donc en attente) 
{
long double NbreMoy = 0;	
int i;

for(i=0; i<taille*NEt ; i=i+NEt){     
        NbreMoy += tab[i]*pi[(int)i/NEt];
    }   	
	
return NbreMoy;	
}

long double proba_perte1(int tab[],double pi[],int taille){ // tableau des etats , dist stat, taille

int i;
long double p = 0;

for(i=0; i<taille*NEt ; i=i+NEt){
        if(tab[i] == BufferSize)
        p +=  pi[(int)i/NEt];
    }   
return p;		
}


long double TempsReponse1(int Lambda1, int tab[],double pi[],int taille) // nombre moyen de clients faisons la queue (donc en attente) 
{
	long double N = NombreMoyen1(tab,pi,taille);	
	long double pertes = proba_perte1(tab,pi,taille);
	return N/(Lambda1*(1.0 - pertes));
}



long double energie1(int tab[],double pi[],int taille, int seuil1,int seuil2,int seuil3,int seuil4, int seuil5,  int SMigrations[MAX_ETAT_MIGRATIONS], int Etats1[MAX_ETAT_MIGRATIONS], int Etats2[MAX_ETAT_MIGRATIONS], int NMigrations[MAX_ETAT_MIGRATIONS], int tailleM ){
	
	int i,j , Inservice1,Outservice1;
	long double ConsMoy1 = 0;
	
	
	for(i=0; i<taille*NEt ; i=i+NEt){
	
		
		Inservice1 = min2(tab[i], C);
		Outservice1 = C - Inservice1; 
			
		if(tab[i] <= seuil1) // palier 1
		{
			ConsMoy1 += (Inservice1*e1 + Outservice1*e1idle )*pi[(int)i/NEt] ;
		}
		if( tab[i] > seuil1 && tab[i] <= seuil2 ) // palier 2
		{
			ConsMoy1 += (Inservice1*e2 + Outservice1*e2idle )*pi[(int)i/NEt] ;
		}
		if( tab[i] > seuil2 && tab[i] <= seuil3) // palier 3
		{
			ConsMoy1 += (Inservice1*e3 + Outservice1*e3idle )*pi[(int)i/NEt] ;
		}
		if( tab[i] > seuil3 && tab[i] <= seuil4) // palier 4
		{	
			ConsMoy1 += (Inservice1*e4 + Outservice1*e4idle )*pi[(int)i/NEt] ;
		}
		if( tab[i] > seuil4 && tab[i] <= seuil5) // palier 5
		{
			ConsMoy1 += (Inservice1*e5 + Outservice1*e5idle )*pi[(int)i/NEt] ;
		}
		if( tab[i] > seuil5) // palier 6
		{
			ConsMoy1 += (Inservice1*e6 + Outservice1*e6idle )*pi[(int)i/NEt] ;
		}
		
    }
    
  	
	return ConsMoy1;
}





















