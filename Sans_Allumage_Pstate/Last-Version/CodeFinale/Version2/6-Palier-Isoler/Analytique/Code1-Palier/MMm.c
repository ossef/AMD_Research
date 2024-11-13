/*
 Modèle Mono-Pstate infinie , programmé sur Pstate 3
 Changer les Mu13 et e3 et e3idle pour l'adapter à un pstate donné
*/

#include "const.h"


int Lambda;
long double pi0;
long double rho;
long double PI[(int)MAX];

void  usage(char*chaine)
{
	printf("usage : %s Lambda \n",chaine);
	exit(1);
}

int min(int a, int b)
{
	return a<b ? a : b ;
}

unsigned long long int factorielle (unsigned short nombre) // maximum 65! , en printf on utilise %llu
{
    if (nombre == 0)
        return 1;
    else
        return nombre * factorielle(nombre - 1);
}


long double pow_log(long double x, int n) { //logarithmique complexité x^n
	 if (n == 0) return 1;
	 if (n == 1 || x == 0)   return x; 
	 if (n < 0)  return pow(1 / x, -n); 
	 if (n % 2 == 0) return pow(x * x, n / 2);
     else return pow(x * x, n / 2) * x; 
	}



void PI0()
{
	rho = (Lambda*1.0)/(C*Mu13);
	long double s1 = pow_log(C*rho,C)/(factorielle(C)*(1-rho));
	
	long double s2 = 0;
	for(int i = 1; i<= C-1; i++)
	{
		s2 += (pow_log(C*rho,i)/(factorielle(i)));
	}
	
    pi0 = 1.0/(1 + s1 + s2);
	printf("PI0 = %.10Le \n", pi0);
	
}


void Calcul_Dist_PI()
{
	int i;
	
	PI0();
	
	for(i = 0; i<= C-1; i++)
	{
		PI[i] = pi0*(pow_log(C*rho,i)/(factorielle(i)));
	}
	
	long double tmp = (pi0*pow_log(C,C))/factorielle(C) ;
	
	for(i = C; i<= MAX; i++)
	{
		PI[i] = tmp*pow_log(rho,i);
	}
	
	long double test = 0;
	for(i = 0; i<= MAX; i++)
	{
		//printf("PI[%d] = %.10Le \n",i,PI[i]);
		test += PI[i];
	}
	printf("La somme des probas : %.15Le \n",test);
	
}

long double Mu(int i)
{

int Inservice = min(i,C);
return Inservice*Mu13;

}

long double Calcul_Puiss_Moy_Num()
{
	
	int i, Inservice, Outservice;
	long double consMoy = 0;
	
	for( i=0; i<=MAX ; i++)
	{
		Inservice = min(i, C);
		Outservice = C - Inservice; 
		consMoy += PI[i]*(Inservice*e3 + Outservice*e3idle);
    }
   	return consMoy;
}

long double Calcul_Puiss_Moy_An()
{
	return e3idle*C + ((e3 - e3idle)*Lambda*1.0)/Mu13;
}

long double Calcul_Puiss_Moy_IDLE()
{
	return ( C - (Lambda*1.0/Mu13) )* e3idle;
}

long double Energie_Job_An()
{
	return Lambda == 0 ? -1 : (e3idle*C*1.0)/Lambda + (e3 - e3idle)/(Mu13*1.0);
}

long double Nbre_Moyen()
{
	long double s = 0;
	for( int i=0; i<=MAX ; i++)
	{
		s += i*PI[i];
	}
	return s;
}

long double Temps_reponse(long double N)
{
	if(Lambda != 0)
		return N/Lambda;
	else
		return -1;
}

long double Energie_Job_Num(long double puissance)
{
	if(Lambda != 0)
		return puissance/Lambda;
	else
		return -1;
}

long double Energie_Sys(long double puissance)
{
		return puissance/Mu13;
}

void Ecrire_PI()
{
	FILE *f1 = fopen("Dist_Stat.PI","w");
	for( int i=0; i<=MAX ; i++)
	{
		fprintf(f1,"%3d		%.10Le \n",i,PI[i]);
	}
	fclose(f1);
}


int main(argc,argv)
int argc;
char *argv[];
{

if (argc!=2) usage(argv[0]);

long double Puiss_Num,Puiss_An, Puiss_Idle, Eng_Num, Eng_An, Eng_Sys, NMoyen, Treponse;
Lambda = atoi(argv[1]);


Calcul_Dist_PI ();
Ecrire_PI();
NMoyen = Nbre_Moyen();
Treponse = Temps_reponse(NMoyen);


//Puiss_Num =  Calcul_Puiss_Moy_Num();
//Eng_Num = Energie_Job_Num(Puiss_Num);

Puiss_An = Calcul_Puiss_Moy_An();
Puiss_Idle = Calcul_Puiss_Moy_IDLE();
Eng_An = Energie_Job_An();
Eng_Sys = Energie_Sys(Puiss_An);


FILE *f = fopen("File_Infini.resultats","a");

fprintf(f,"%5d     	", Lambda);
fprintf(f,"%.10Lf       ", NMoyen);
fprintf(f,"%.10Lf       ", Treponse);
//fprintf(f,"%.10Le       ", Puiss_Num);
fprintf(f,"%.10Lf       \n", Puiss_An);
//fprintf(f,"%.10Le       ", Eng_Num);
//fprintf(f,"%.10Lf      ", Eng_An);
//fprintf(f,"%.10Lf      ", Eng_Sys);
//fprintf(f,"%.10Lf      \n", Puiss_Idle);

//fprintf(f,"%.10Le      \n", (long double)(Cons/Treponse));

fclose(f);



return 0;
}

