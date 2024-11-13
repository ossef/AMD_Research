
/*----Le modèle est finie, DVFS processeur avec un bufferMax fini ----*/

#include "const.h"


long double pi[B+1];

int max (int a, int b)
{
	return  a > b ? a : b ;
} 
int min(int a, int b)
{
	return a<b ? a : b ;
}

void Init_Tab()
{
	for(int i=0; i<=B ; i++)
	{
		pi[i] = 0;
	}
}
void  usage(char*chaine)
{
	printf("usage : %s Lambda seuil1 seuil2 seuil3 seuil4 seuil5\n",chaine);
	exit(1);
}



long double Mu(int i, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{

int Inservice = min(i,C);

	if(i <= seuil1) // palier 1
			{
				return Inservice*Mu11;
			}
	if( i > seuil1 && i <= seuil2 ) // palier 2
			{
				return Inservice*Mu12;
			}
	if( i > seuil2 && i <= seuil3) // palier 3
			{
				return Inservice*Mu13;
			}
	if( i > seuil3 && i <= seuil4) // palier 4
			{	
				return Inservice*Mu14;
			}
	if( i > seuil4 && i <= seuil5) // palier 5
			{
				return Inservice*Mu15;
			}
	if( i > seuil5) // palier 6
			{
				return Inservice*Mu16;
			}
}

double Omega(int x, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{
	if(x==0)
	{
		printf("Erreur Omega(0), pas de service à l'etat 0 \n");
		exit(0);
	}
	 
	double s=1;
	int i;
	for( i=1; i<=x ; i++)
	{
		s*=Mu(i,seuil1,seuil2,seuil3,seuil4,seuil5);
	}
	return s;
}

void Calcul_Dist_PI (int Lambda, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{	
	int i;
	long double s1 = 0, s2 = 0;
	
	
	pi[0] = 1.0;
	
	/*------- Calcul de la borne de stabilté du decoupage du processus de naissance/mort -------- */
	
	int R = max(C,seuil5);
	
	/* ----------- Calcule des probas dans x in [1,R] -------------*/
	
	for( i=1; i<=R; i++)
	{
		pi[i] = pow(Lambda,i)/Omega(i,seuil1,seuil2,seuil3,seuil4,seuil5);
	}
	
	/* ----------- Calcule des probas dans x in [R+1,B] -------------*/
	
	for( i=R+1; i<=B; i++)
	{
		pi[i] = pow(Lambda,i)/(Omega(R,seuil1,seuil2,seuil3,seuil4,seuil5)*pow(C*Mu16,i-R));
	}
	
	
	/* ----------- Calcule de la première somme: x in [0,R] -------------*/
	
	for( i=1; i<=R; i++)
	{
		s1 += pi[i];
	}
	
	/* ----------- Calcule de la deuxième somme : x in [R+1,B] -------------*/
	

	for( i=R+1; i<=B; i++)
	{
		s2 += pi[i];
	}	
	//printf("s2 = %.10Le \n", s2);
	
	/*------------ Normalisation ---------------------------*/

	long double pi0 = 1.0 / ( 1 + s1 + s2);
	
	
	for( i=0; i<=B ; i++)
	{
		pi[i] *= pi0;
		
	}
	
	printf("pi0 = %.10Le \n", pi[0]);
	printf("piB = %.10Le \n", pi[B]);
	
	/*----------- Affichage et test ---------------------*/
	
	long double teste = 0;
	
	for( i=B; i>=0 ; i--)
	{
		//printf("PI[%d] = %.10Le \n",i,pi[i]);
		teste += pi[i];
	}
	printf("Lambda = %d, La somme des probas = %.20Le \n",Lambda,teste);
	
	/*----------Ecrire Probas dans un fichier -----------*/
	FILE *f1 = fopen("Dist_stat","w");
	for( i=0; i<=B ; i++)
	{
		fprintf(f1,"%.10Le \n", pi[i]); 
	}
	fclose(f1);
	

	
}

long double Calcul_Puiss_Moy(int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{
	
	int i, Inservice, Outservice;
	long double consMoy = 0;
	
	for( i=0; i<=B ; i++)
	{
		Inservice = min(i, C);
		Outservice = C - Inservice; 
		
		if(i <= seuil1) // palier 1
		{
			consMoy += pi[i]*(Inservice*e1 + Outservice*e1idle);
		}
		if( i > seuil1 && i <= seuil2 ) // palier 2
		{
			consMoy += pi[i]*(Inservice*e2 + Outservice*e2idle);
		}
		if( i > seuil2 && i <= seuil3 ) // palier 3
		{
			consMoy += pi[i]*(Inservice*e3 + Outservice*e3idle);
		}
		if( i > seuil3 && i <= seuil4 ) // palier 4
		{
			consMoy += pi[i]*(Inservice*e4 + Outservice*e4idle);
		}
		if( i > seuil4 && i <= seuil5 ) // palier 5
		{
			consMoy += pi[i]*(Inservice*e5 + Outservice*e5idle);
		}
		if( i > seuil5) // palier 6
		{
			consMoy += pi[i]*(Inservice*e6 + Outservice*e6idle);
		}
   }
   	return consMoy;
}


long double Nbre_Moyen() //dans le systeme
{
	long double s = 0;
	for( int i=0; i<=B ; i++)
	{
		s += i*pi[i];
	}
	return s;
}

long double Temps_reponse(int Lambda, long double N) //dans le systeme, systeme finie !!
{
	return N/(Lambda*(1-pi[B]));
}

long double Energie_Job(int Lambda, long double puissance)
{
	return puissance/Lambda;
}

long double * Proba_Pstates(long double S[6],int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{
	
	for( int i=0; i<6 ; i++)
	{
		S[i] = 0;
	}
	
	for( int i=0; i<=B ; i++)
	{
		if(i <= seuil1) // palier 1
		{
			S[0] += pi[i];
		}
		if( i > seuil1 && i <= seuil2 ) // palier 2
		{
			S[1] += pi[i];		
		}
		if( i > seuil2 && i <= seuil3 ) // palier 3
		{
			S[2] += pi[i];
		}
		if( i > seuil3 && i <= seuil4 ) // palier 4
		{
			S[3] += pi[i];
		}
		if( i > seuil4 && i <= seuil5 ) // palier 5
		{
			S[4] += pi[i];
		}
		if( i > seuil5) // palier 6
		{
			S[5] += pi[i];
		}
	}
	
	return S;
	
}


int main(argc,argv)
int argc;
char *argv[];
{

if (argc!=6) usage(argv[0]);

int seuil1 = atoi(argv[1]);
int seuil2 = atoi(argv[2]);
int seuil3 = atoi(argv[3]);
int seuil4 = atoi(argv[4]);
int seuil5 = atoi(argv[5]);

int Lambda;
long double Puiss, NMoyen, Treponse, Eng;
//long double *S = malloc(6*sizeof(long double));

FILE *f = fopen("File_Infini.resultats","w");
fprintf(f,"seuils = {%d, %d, %d, %d, %d} \n \n", seuil1, seuil2, seuil3, seuil4, seuil5);

for( Lambda = 1 ; Lambda <= C*Mu16 ; Lambda+=2)
	{
		Init_Tab();
		Calcul_Dist_PI (Lambda, seuil1, seuil2, seuil3, seuil4, seuil5);
		NMoyen = Nbre_Moyen();
		Treponse = Temps_reponse(Lambda, NMoyen);
		Puiss = Calcul_Puiss_Moy(seuil1, seuil2, seuil3, seuil4, seuil5);
		//Eng = Energie_Job(Lambda, Puiss);

		fprintf(f,"%5d     	", Lambda);
		fprintf(f,"%.10Lf       ", NMoyen);
		fprintf(f,"%.10Lf       ", Treponse);
		fprintf(f,"%.10Lf       ",  pi[B]);
		fprintf(f,"%.10Lf       \n", Puiss);
	
	}
	
fclose(f);

return 0;
}
