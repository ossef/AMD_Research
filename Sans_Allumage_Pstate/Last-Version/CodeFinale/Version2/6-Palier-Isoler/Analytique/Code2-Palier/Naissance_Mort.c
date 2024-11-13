
#include "const.h"

double MuState[6] = {Mu11,Mu12,Mu13,Mu14,Mu15,Mu16};
double eState[6]  = {e1, e2, e3, e4, e5, e6};

long double pi[(int)MAX];

int max (int a, int b)
{
	return  a >= b ? a : b ;
} 


void Init_Tab()
{
	for(int i=0; i<=MAX ; i++)
	{
		pi[i] = 0;
	}
}


void  usage(char*chaine)
{
	printf("usage : %s \n",chaine);
	exit(1);
}

int min(int a, int b)
{
	return a<b ? a : b ;
}

long double Mu(int a, int b, int i, int seuil1) // a = indice du pstate1 et b l'indice du pstate2
{

int Inservice = min(i,C);

	if(i <= seuil1) // palier 1
			{
				return Inservice*MuState[a];
			}

				return Inservice*MuState[b];
}


void Calcul_Dist_PI (int a, int b, int Lambda, int seuil1)
{	
	int i;
	long double s1 = 0, s2;
	
	
	pi[0] = 1;
	for( i=1; i<=MAX ; i++)
	{
		pi[i] = 0;
	}
	
	for( i=1; i<=MAX; i++)
	{
		pi[i] = ((Lambda*1.0)/Mu(a,b,i,seuil1))*pi[i-1];
	}
	
	/*------- Calcul de la borne de stabilté du decoupage du processus de naissance/mort -------- */
	
	int R = max(C,seuil1);
	
	/* ----------- Calcule de la première somme -------------*/
	
	for( i=1; i<=R; i++)
	{
		s1 += pi[i];
	}
	
	//printf("s1 = %.10Le \n", s1);
	
	/* ----------- Calcule de la deuxième somme -------------*/
	

	//s2 = ((1.0/( 1.0 - (Lambda/(C*Mu14*1.0)))) - 1 )*pi[R] ;
	s2 = (Lambda*1.0/(C*MuState[b]*1.0 - Lambda))*pi[R];
	
	//printf("s2 = %.10Le \n", s2);
	
	/*------------ Normalisation ---------------------------*/

	long double pi0 = 1.0 / ( 1 + s1 + s2);
	
	//printf("pi0 = %.10Le \n", pi0);
	
	for( i=0; i<=MAX ; i++)
	{
		pi[i] *= pi0;
		
	}
	
	/*----------- Affichage et test ---------------------*/
	
	long double teste = 0;
	
	for( i=MAX; i>=0 ; i--)
	{
		//printf("PI[%d] = %.10Le \n",i,pi[i]);
		teste += pi[i];
	}
	printf("La somme des probas = %.20Le \n",teste);
	
}

long double Calcul_Puiss_Moy(int a, int b, int seuil1)
{
	
	int i, Inservice, Outservice;
	long double consMoy = 0;
	
	for( i=0; i<=MAX ; i++)
	{
		Inservice = min(i, C);
		Outservice = C - Inservice; 
		
		if(i <= seuil1) // palier 1
		{
			consMoy += pi[i]*(Inservice*eState[a] + Outservice*eState[a]*Alpha);
		}
		else // palier 2
		{
			consMoy += pi[i]*(Inservice*eState[b] + Outservice*eState[b]*Alpha);
		}
   }
   	return consMoy;
}


long double Nbre_Moyen()
{
	long double s = 0;
	for( int i=0; i<=MAX ; i++)
	{
		s += i*pi[i];
	}
	return s;
}

long double Temps_reponse(int Lambda, long double N)
{
	return Lambda == 0 ? -1 : N/Lambda;
}

long double Energie_Job(int Lambda, long double puissance)
{
	return Lambda == 0 ? -1 : puissance/Lambda;
}

void Experiences_Lambda_Seuil(int a, int b)
{
long double Puiss, NMoyen, Treponse, Eng;	
int Lambda;
int seuil1;


FILE *f = fopen("File_Infini.resultats","w");


for( seuil1 = 10 ; seuil1 < 11 ; seuil1++)
	{
	fprintf(f,"Seuil = {%d} \n ", seuil1);
	for( Lambda = 1 ; Lambda < C*MuState[b] ; Lambda+=2)
		{
			Init_Tab();
			Calcul_Dist_PI (a,b,Lambda, seuil1);
			NMoyen = Nbre_Moyen();
			Treponse = Temps_reponse(Lambda, NMoyen);
			Puiss = Calcul_Puiss_Moy(a,b,seuil1);
			Eng = Energie_Job(Lambda, Puiss);
			
			printf("Pstate i= %d et Pstate j= %d et Seuil = {%d} \n",a,b,seuil1);
			fprintf(f,"%5d     	", Lambda);
			fprintf(f,"%.10Lf       ", NMoyen);
			fprintf(f,"%.10Lf       ", Treponse);
			fprintf(f,"%.10Lf       ", Puiss);
			fprintf(f,"%.10Lf      \n", Eng);
		}
	}

fclose(f);
	
}

void Lemma_numerique(int a, int b) //trouver un Th max pour un lambda donnée a et b dans {0,1,...,5}
{
	
long double Puiss, PuissAvant, NMoyen, Treponse;
long double EPSILON = 1e-10;	
int Lambda = 20;
int seuil1;


FILE *f = fopen("File_Infini.resultats","w");
//fprintf(f,"Verification Lemme numérique, EPSILON = %.10Le \n \n", EPSILON);

/*for( Lambda = 1 ; Lambda < C*MuState[b] ; Lambda+=1)
{*/
	PuissAvant = 0;
	Puiss = 1e6;
	seuil1 = 1;
	
	fprintf(f,"\n -------------------- Lambda = %5d ----------------- \n", Lambda);
	//while(fabs(Puiss - PuissAvant) > EPSILON)
	while( seuil1 < 100 )
		{		
				printf("Seuil = {%d} \n",seuil1);
				PuissAvant = Puiss;

				Init_Tab();
				Calcul_Dist_PI (a,b,Lambda, seuil1);
				Puiss = Calcul_Puiss_Moy(a,b,seuil1);
				NMoyen = Nbre_Moyen();
				Treponse = Temps_reponse(Lambda, NMoyen);

				
				if( PuissAvant < Puiss )
				{
					fprintf(f,"%5d     	", seuil1);
					fprintf(f,"%.30Le       ", Treponse);
					fprintf(f,"%.3Lf       ", Puiss);	
					fprintf(f,"    ------------!----------      \n");	
					//break;
					
				}
				else
				{
					fprintf(f,"%5d     	", seuil1);
					fprintf(f,"%.30Le       ", Treponse);
					fprintf(f,"%.3Lf      \n", Puiss);
				}
				seuil1++;
		 }
//fprintf(f,"Pour Lambda = %d, le SeuilMax = %d \n ", Lambda, seuil1-1);
//}

printf("LambdaMax = %f \n",C*MuState[b]);
fclose(f);

}

void Algo_Exhaustive_Energie()
{

long double Puiss, NMoyen, Treponse, Eng, TreponseMin, EngMin;
int Lambda = 20;
int SeuilMax = 100;
int a, b, seuil, seuilmin;
double EngMax = 50; 

FILE *f = fopen("2Pstates_Energie.resultats","w");


	fprintf(f,"Entrée:\n Lambda = %5d \n #Serveurs = %5d \n EnergieMax = %5.2f (Watt/job) \n SeuilMax = %5d \n\n", Lambda, C, EngMax, SeuilMax);
	fprintf(f,"Sortie: \n\n");
	fprintf(f,"Pstate i	 Pstate j	  Seuil			 Treponse 				Energie \n\n");

	for( b = 0 ; b < 6 ; b+=1)
		{
		for( a = 0 ; a < b ; a+=1)
			{	
				if( Lambda < C*MuState[b] )
				{
					EngMin = 1e10;
					TreponseMin = 1e10;
				
					for( seuil = 1 ; seuil <= SeuilMax  ; seuil+=1)
						{
							Init_Tab();
							Calcul_Dist_PI (a,b,Lambda, seuil);
							NMoyen = Nbre_Moyen();
							Treponse = Temps_reponse(Lambda, NMoyen);
							Puiss = Calcul_Puiss_Moy(a,b,seuil);
							Eng = Energie_Job(Lambda, Puiss);
							
							if( Eng <= EngMax )//&& Treponse <= DelayMax )
							{
								if( Eng < EngMin ) //&& Treponse < TreponseMin )
								{
									TreponseMin = Treponse;
									EngMin = Eng;
									seuilmin = seuil;
								}
							}
						}
						if( EngMin != 1e10 )
						{
							fprintf(f,"%3d          ", a+1);
							fprintf(f,"%3d          ", b+1);
							fprintf(f,"%3d          ", seuilmin);
							fprintf(f,"%.25Le       ", TreponseMin);
							fprintf(f,"%.25Le      \n", EngMin);
						}
				}
				else
				{
					fprintf(f,"i = %d et j = %d, avec Lambda = %d et C = %d, le systeme est instable \n", a+1,b+1,Lambda,C);
				}
			}
		}

fclose(f);
	
}

void Algo_Exhaustive_Delay()
{

long double Puiss, NMoyen, Treponse, Eng, TreponseMin, EngMin;
int Lambda = 20;
int SeuilMax = 100;
int a, b, seuil, seuilmin;
double DelayMax = 0.5;

FILE *f = fopen("2Pstates_Delay.resultats","w");


	fprintf(f,"Entrée:\n Lambda = %5d \n #Serveurs = %5d \n DelayMax = %5.2f (t) \n SeuilMax = %5d \n\n", Lambda, C, DelayMax, SeuilMax);
	fprintf(f,"Sortie: \n\n");
	fprintf(f,"Pstate i	 Pstate j	  Seuil			 Treponse 				Energie \n\n");

	for( b = 0 ; b < 6 ; b+=1)
		{
		for( a = 0 ; a < b ; a+=1)
			{	
				if( Lambda < C*MuState[b] )
				{
					TreponseMin = 1e10;
					EngMin = 1e10;
				
					for( seuil = 1 ; seuil <= SeuilMax  ; seuil+=1)
						{
							Init_Tab();
							Calcul_Dist_PI (a,b,Lambda, seuil);
							NMoyen = Nbre_Moyen();
							Treponse = Temps_reponse(Lambda, NMoyen);
							Puiss = Calcul_Puiss_Moy(a,b,seuil);
							Eng = Energie_Job(Lambda, Puiss);
							
							if(  Treponse <= DelayMax )
							{
								if( Treponse < TreponseMin )
								{
									TreponseMin = Treponse;
									EngMin = Eng;
									seuilmin = seuil;
								}
							}
						}
						if( EngMin != 1e10 )
						{
							fprintf(f,"%3d          ", a+1);
							fprintf(f,"%3d          ", b+1);
							fprintf(f,"%3d          ", seuilmin);
							fprintf(f,"%.25Le       ", TreponseMin);
							fprintf(f,"%.25Le      \n", EngMin);
						}
				}
				else
				{
					fprintf(f,"i = %d et j = %d, avec Lambda = %d et C = %d, le systeme est instable \n", a+1,b+1,Lambda,C);
				}
			}
		}

fclose(f);
	
}

void Algo_Exhaustive_Energie_Delay() //fonction economique
{

long double Puiss, NMoyen, Treponse, Eng, TreponseMin, PuissMin, EngMin, Ppw, PpwMax;	
int Lambda = 40;
int SeuilMax = 100;
int a, b, seuil, seuilmin;
//double EngMax = 50;  double DelayMax = 0.5;
double c1 = 1; //constante du temps de reponse
double c2 = 50; //constante de l'energie
long double fct,fctMin;

FILE *f = fopen("2Pstates_Energie_Delay.resultats","w");


	fprintf(f,"Entrée:\n Lambda = %5d \n #Serveurs = %5d \n SeuilMax = %5d \n\n", Lambda, C, SeuilMax);
	fprintf(f,"Sortie: \n\n");
	fprintf(f,"Pstate i	 Pstate j	  Seuil			 Treponse 		Puissance	 	PPW			Energie 	\n\n");

	for( b = 0 ; b < 6 ; b+=1)
		{
		for( a = 0 ; a <= b ; a+=1)
			{	
				if( Lambda < C*MuState[b] )
				{
					
					if( a == b )
					{
						    seuil = 0;
							Init_Tab();
							Calcul_Dist_PI (a,b,Lambda, seuil);
							NMoyen = Nbre_Moyen();
							Treponse = Temps_reponse(Lambda, NMoyen);
							Puiss = Calcul_Puiss_Moy(a,b,seuil);
							Ppw = 1.0 / (Treponse*Puiss);  
							Eng = Energie_Job(Lambda, Puiss);
							fct = c1*Treponse + c2*Eng;
							
							fprintf(f,"%3d          ", a+1);
							fprintf(f,"%3d          ", b+1);
							fprintf(f," -           ");
							fprintf(f,"%.10Le       ", Treponse);
							fprintf(f,"%.10Le       ", Puiss);
							fprintf(f,"%.10Le       ", Ppw);
							fprintf(f,"%.10Le       ", Eng);
							fprintf(f,"\n    	    ");
							
					}
					else
					{
					
						PpwMax = -1;
					
						for( seuil = 1 ; seuil <= SeuilMax  ; seuil+=1)
							{
								Init_Tab();
								Calcul_Dist_PI (a,b,Lambda, seuil);
								NMoyen = Nbre_Moyen();
								Treponse = Temps_reponse(Lambda, NMoyen);
								Puiss = Calcul_Puiss_Moy(a,b,seuil);
								Ppw = 1.0 / (Treponse*Puiss);  
								Eng = Energie_Job(Lambda, Puiss);
								fct = c1*Treponse + c2*Eng;
								
								if( Ppw > PpwMax  )
								{
										PuissMin = Puiss;
										PpwMax = Ppw;
										EngMin = Eng;
										TreponseMin = Treponse;
										seuilmin = seuil;
								}
							}
							if( PpwMax != -1 )
							{
								fprintf(f,"%3d          ", a+1);
								fprintf(f,"%3d          ", b+1);
								fprintf(f,"%3d          ", seuilmin);
								fprintf(f,"%.10Le       ", TreponseMin);
								fprintf(f,"%.10Le       ", PuissMin);
								fprintf(f,"%.10Le       ", PpwMax);
								fprintf(f,"%.10Le       ", EngMin);
								fprintf(f,"\n    	    ");
							}
					}
				} // fin condition stabilite
				else
				{
					fprintf(f,"i = %d et j = %d, avec Lambda = %d et C = %d, le systeme est instable \n", a+1,b+1,Lambda,C);
				}
			}
		}

fclose(f);
	
}





int main(argc,argv)
int argc;
char *argv[];
{

if (argc!=1) usage(argv[0]);

/*Algo_Exhaustive_Energie();
Algo_Exhaustive_Delay();
Algo_Exhaustive_Energie_Delay();*/

//Algo_Exhaustive_Energie_Delay();

Experiences_Lambda_Seuil(2, 4);

return 0;
}
