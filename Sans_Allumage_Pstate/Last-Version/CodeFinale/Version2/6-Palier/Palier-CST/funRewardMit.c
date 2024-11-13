// funreward for mitrani's model


#include "const.h"

int min2(int a, int b)
{
	return a<b ? a : b ;
}

long double proba_perte1(int tab[],double pi[],int taille){ // tableau des etats , dist stat, taille

int i;
long double p = 0;

for(i=0; i<taille*2 ; i=i+2){
        if(tab[i] == BufferSize)
        p +=  pi[(int)i/2];
    }   
return p;		
}

long double proba_perte2(int tab[],double pi[],int taille){ // tableau des etats , dist stat, taille

int i;
long double p = 0;

for(i=0; i<taille*2 ; i=i+2){
        if(tab[i+1] == BufferSize)
        p +=  pi[(int)i/2];
    }   
return p;		
}

void Diff_Migr1_Migre2(int tab[],double pi[],int taille, int SMigrations[MAX_ETAT_MIGRATIONS], int Etats1[MAX_ETAT_MIGRATIONS], int Etats2[MAX_ETAT_MIGRATIONS], int NMigrations[MAX_ETAT_MIGRATIONS], int tailleM )
{
		
	double some1, some2;
	some1 = some2 = 0;
	
	int i,j;
	
	for(j=0; j<tailleM ; j++)
	{
	
		for(i=0; i<taille*2 ; i=i+2){
			
			
			if(tab[i] == Etats1[j] && tab[i+1] == Etats2[j] )
			{
					if(SMigrations[j] == 1)
					  some1 +=  pi[(int)i/2];
					if(SMigrations[j] == 2)
					  some2 +=  pi[(int)i/2];
			}
			
		}
	
	}
	
	printf("\n Somme1 = %lf et Somme2 %lf \n",some1,some2);
	
	
}





long double energie1(int tab[],double pi[],int taille, int seuil1,int seuil2,int seuil3,int seuil4, int seuil5, double gamma12, int SMigrations[MAX_ETAT_MIGRATIONS], int Etats1[MAX_ETAT_MIGRATIONS], int Etats2[MAX_ETAT_MIGRATIONS], int NMigrations[MAX_ETAT_MIGRATIONS], int tailleM ){
	
	int i,j , Inservice1,Outservice1;
	long double ConsMoy1 = 0;
	
	
	for(i=0; i<taille*2 ; i=i+2){
		
		if(gamma12 != 0 )
		{
		for( j=0; j<tailleM; j++)
		{
			if( SMigrations[j] == 1 && Etats1[j] == tab[i] &&  Etats2[j] == tab[i+1] )
			{
				tab[i] -= NMigrations[j];
				
				if(tab[i] < 0) {printf("Problème dans l'etat : (%d,%d)", tab[i],tab[i+1]); exit(0); }
					
				ConsMoy1 += /*gamma12*/eb*NMigrations[j]*pi[(int)i/2];
				break;
			}
		
		}
		}
		
		Inservice1 = min2(tab[i], C);
		Outservice1 = C - Inservice1; 
			
		if(tab[i] <= seuil1) // palier 1
		{
			ConsMoy1 += (Inservice1*e1 + Outservice1*e1idle )*pi[(int)i/2] * Mu11;
		}
		if( tab[i] > seuil1 && tab[i] <= seuil2 ) // palier 2
		{
			ConsMoy1 += (Inservice1*e2 + Outservice1*e2idle )*pi[(int)i/2]* Mu12;
		}
		if( tab[i] > seuil2 && tab[i] <= seuil3) // palier 3
		{
			ConsMoy1 += (Inservice1*e3 + Outservice1*e3idle )*pi[(int)i/2]* Mu13;
		}
		if( tab[i] > seuil3 && tab[i] <= seuil4) // palier 4
		{	
			ConsMoy1 += (Inservice1*e4 + Outservice1*e4idle )*pi[(int)i/2]* Mu14;
		}
		if( tab[i] > seuil4 && tab[i] <= seuil5) // palier 5
		{
			ConsMoy1 += (Inservice1*e5 + Outservice1*e5idle )*pi[(int)i/2]* Mu15;
		}
		if( tab[i] > seuil5) // palier 6
		{
			ConsMoy1 += (Inservice1*e6 + Outservice1*e6idle )*pi[(int)i/2]* Mu16;
		}
		
    }
    
  	
	return ConsMoy1;
}

long double energie2(int tab[],double pi[],int taille, int seuil1, int seuil2, int seuil3,int seuil4, int seuil5, double gamma12, int SMigrations[MAX_ETAT_MIGRATIONS], int Etats1[MAX_ETAT_MIGRATIONS], int Etats2[MAX_ETAT_MIGRATIONS], int NMigrations[MAX_ETAT_MIGRATIONS], int tailleM ){
	
	int i,j, Inservice1,Outservice1;
	long double ConsMoy1 = 0;
	
	
	
	for(i=0; i<taille*2 ; i=i+2){
		
		if(gamma12 != 0 )
		{
		for( j=0; j<tailleM; j++)
		{
			if( SMigrations[j] == 2 && Etats1[j] == tab[i] &&  Etats2[j] == tab[i+1] )
			{
				tab[i+1] -= NMigrations[j];
				
				if(tab[i+1] < 0) {printf("Problème dans l'etat : (%d,%d)", tab[i],tab[i+1]); exit(0); }
					
				ConsMoy1 += /*gamma12*/eb*NMigrations[j]*pi[(int)i/2];
				break;
			}
		
		}
		}
		
		Inservice1 = min2(tab[i+1], C);
		Outservice1 = C - Inservice1; 
			
		if(tab[i+1] <= seuil1) // palier 1
		{
			ConsMoy1 += (Inservice1*e1 + Outservice1*e1idle )*pi[(int)i/2]* Mu21;
		}
		if( tab[i+1] > seuil1 && tab[i+1] <= seuil2 ) // palier 2
		{
			ConsMoy1 += (Inservice1*e2 + Outservice1*e2idle )*pi[(int)i/2]* Mu22;
		}
		if( tab[i+1] > seuil2 && tab[i+1] <= seuil3) // palier 3
		{
			ConsMoy1 += (Inservice1*e3 + Outservice1*e3idle )*pi[(int)i/2]* Mu23;
		}
		if( tab[i+1] > seuil3 && tab[i+1] <= seuil4) // palier 4
		{	
			ConsMoy1 += (Inservice1*e4 + Outservice1*e4idle )*pi[(int)i/2]* Mu24;
		}
		if( tab[i+1] > seuil4 && tab[i+1] <= seuil5) // palier 5
		{
			ConsMoy1 += (Inservice1*e5 + Outservice1*e5idle )*pi[(int)i/2]* Mu25;
		}
		if( tab[i+1] > seuil5) // palier 6
		{
			ConsMoy1 += (Inservice1*e6 + Outservice1*e6idle )*pi[(int)i/2]* Mu26;
		}
		
    }
    
  	
	return ConsMoy1;
	
}

long double Proba_Migration1(int tab[],double pi[],int taille, double gamma12, int SMigrations[MAX_ETAT_MIGRATIONS], int Etats1[MAX_ETAT_MIGRATIONS], int Etats2[MAX_ETAT_MIGRATIONS], int NMigrations[MAX_ETAT_MIGRATIONS], int tailleM ){
	
	long double some1 = 0;
	
	if(gamma12 == 0) return some1;
	
	int i,j;
	
	for(j=0; j<tailleM ; j++)
	{
	
		for(i=0; i<taille*2 ; i=i+2)
		{
			
			if(tab[i] == Etats1[j] && tab[i+1] == Etats2[j] && SMigrations[j] == 1 )
					  some1 +=  pi[(int)i/2];
			
		}
	
	}
	
	return some1;
}

long double Proba_Migration2(int tab[],double pi[],int taille, double gamma12, int SMigrations[MAX_ETAT_MIGRATIONS], int Etats1[MAX_ETAT_MIGRATIONS], int Etats2[MAX_ETAT_MIGRATIONS], int NMigrations[MAX_ETAT_MIGRATIONS], int tailleM ){
	
	long double some2 = 0;
	
	if(gamma12 == 0) return some2;
	
	int i,j;
	
	for(j=0; j<tailleM ; j++)
	{
	
		for(i=0; i<taille*2 ; i=i+2)
		{
			
			if(tab[i] == Etats1[j] && tab[i+1] == Etats2[j] && SMigrations[j] == 2 )
					  some2 +=  pi[(int)i/2];
			
		}
	
	}
	
	return some2;
}

void Proba_Paliers(int tab[],double pi[],int taille, double gamma12, int seuil1, int seuil2, int seuil3,int seuil4, int seuil5 , char s1[50] )
{
	
	
	if(gamma12 == 0 || gamma12 == 0.1)
	{
		FILE *f = fopen(s1,"a");
		
		int i;
		double P1St[6], P2St[6];
		double s1 , s2;
		s1 = 0; s2 = 0;
		
		for(i=0; i<6 ; i++)
		{ 
			 P1St[i] = 0;
			 P2St[i] = 0;
		}
		
		for(i=0; i<taille*2 ; i=i+2)
		{     
			if(tab[i]<= seuil1)
			      P1St[0] +=  pi[(int)i/2];
			if(tab[i]> seuil1 && tab[i]<= seuil2)
				  P1St[1] +=  pi[(int)i/2];
			if(tab[i]> seuil2 && tab[i]<= seuil3)
				  P1St[2] +=  pi[(int)i/2];
			if(tab[i]> seuil3 && tab[i]<= seuil4)
				  P1St[3] +=  pi[(int)i/2];
			if(tab[i]> seuil4 && tab[i]<= seuil5)
				  P1St[4] +=  pi[(int)i/2];
			if(tab[i]> seuil5)
				  P1St[5] +=  pi[(int)i/2];	
				  
				  
			if(tab[i+1]<= seuil1)
			      P2St[0] +=  pi[(int)i/2];
			if(tab[i+1]> seuil1 && tab[i+1]<= seuil2)
				  P2St[1] +=  pi[(int)i/2];
			if(tab[i+1]> seuil2 && tab[i+1]<= seuil3)
				  P2St[2] +=  pi[(int)i/2];
			if(tab[i+1]> seuil3 && tab[i+1]<= seuil4)
				  P2St[3] +=  pi[(int)i/2];
			if(tab[i+1]> seuil4 && tab[i+1]<= seuil5)
				  P2St[4] +=  pi[(int)i/2];
			if(tab[i+1]> seuil5)
				  P2St[5] +=  pi[(int)i/2];	
		}
		
		fprintf(f,"Cas de  C = %d serveurs et taux de migration = %lf \n",C,gamma12);
		for(i=0; i<6 ; i++)
		{ 
			fprintf(f,"   P%d		   %.10le      %.10le       \n",i+1,P1St[i],P2St[i]);
			s1 += P1St[i];
			s2 += P2St[i];
		}
		fprintf(f,"\n \n");
		
		printf("Verification somme des marginales : %.5le  et %.5le \n",s1,s2);
		
		fclose(f);
    }  
	
}


long double NombreMoyen1(int tab[],double pi[],int taille) // nombre moyen de clients faisons la queue (donc en attente) 
{
long double NbreMoy = 0;	
int i;

for(i=0; i<taille*2 ; i=i+2){     
        NbreMoy += tab[i]*pi[(int)i/2];
    }   	
	
return NbreMoy;	
}


long double NombreMoyen2(int tab[],double pi[],int taille) // nombre moyen de clients faisons la queue (donc en attente) 
{
long double NbreMoy = 0;	
int i;

for(i=0; i<taille*2 ; i=i+2){     
        NbreMoy += tab[i+1]*pi[(int)i/2];
    }   	
	
return NbreMoy;	
}

/*double TempAttente(double NbreMoyAtt){   // Temps moyen des clients en attente (loi de little : Ta = Na/Lambda et Ts = Ns/Lambda)
	return NbreMoyAtt/Lambda;
}*/


















