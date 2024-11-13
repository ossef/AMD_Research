// fichier rewardComponent.c pour modele de Mitrani

/* 
 calcul des recompenses a partir de la matrice,
 des probabilites stationnaires, du codage des etats des composantes
 
 V2.0 le 04/05/16
 
 Hypotheses  de fonctionnement : 
 l'argument est le nom du modele : filename 
 la taille est dans le fichiez filename.sz
 le codage dans filename.cd, 
 et la distribution dans filename.pi
 */

#include <stdio.h> 
#include <math.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>




/* 
 inclusions des constantes, types et variables particulieres a chaque modele
 */

#include "const.h"

 int SMigrations[MAX_ETAT_MIGRATIONS];
 int Etats1[MAX_ETAT_MIGRATIONS];
 int Etats2[MAX_ETAT_MIGRATIONS];
 int NMigrations[MAX_ETAT_MIGRATIONS];

 int taille = 0 ;
 int seuil1,seuil2, seuil3 , seuil4, seuil5;

/* Variables donnant l'etendue de chaque variable isolee */ 
int Min[NEt],Max[NEt]; 
typedef int Etat[NEt];

/* Le nombre d'etats atteignables et de transitions */ 

int ReachableStates, NArcs;

/* la distribution stationnaire et la marginale en cours */ 

double *pi; 
long double *marginale;
int *et;


FILE *pf1; 


//#include "fun.c" 
#include "funRewardMit.c"

void ProblemeMemoire() { printf("Sorry, not enougth memory \n"); exit(1); }


void usage() { 
    printf("usage : RewardComponent -f filename Lambda1 seuil1 seuil2 seuil3 seuil4 \n");
    printf("filename.pi, filename.sz and filename.cd must exist before \n");
    exit(1); 
}

void Lecture_File_Migrations()
{
	FILE*f = fopen("Migration_States.data","r");
	int n1,n2,n3,n4;
	
	fscanf(f,"%d %d %d %d",&n1,&n2,&n3,&n4);
	
	while( n1 != -1 )
	{			
					
				
				SMigrations[taille] = n1;
				Etats1[taille] = n2;
				Etats2[taille] = n3;
				NMigrations[taille] = n4;
				
				fscanf(f,"%d %d %d %d",&n1,&n2,&n3,&n4);
				taille++;
	} 
	printf("LEcture FIle2\n");
	fclose(f);
}

void Affiche_File_Migrations()
{
	int x1 , x2;
	x1 = x2 = 0;
	for( int i=0; i<taille;i++)
	{
		printf("%d : %d %d %d %d \n",i,SMigrations[i],Etats1[i],Etats2[i],NMigrations[i]);
		
		if(SMigrations[i] == 1)
		x1++;
		if(SMigrations[i] == 2)
		x2++;
	}
	
	printf("X1 = %d et X2 = %d\n",x1,x2);
}



int main(argc, argv) 
int argc; 
char *argv[]; 
{ 
    int i,j, k, plusieur, nb ; 
    int comp,Lambda1; 
    int maxcompsize, alpha; 
    long double Mean, Deviate; 
    double gamma12,Eb;
    char s1[50]; 
    char s2[50]; 
    char s3[50]; 
    char s4[50];
    char s5[50];
    
    /* On recupere le nom du modele et on verifie que les fichiers existent */
    
    //printf("Arguments : %d \n",argc);
	if (argc!=9) usage();
    --argc; ++argv; 
    if (**argv != '-') usage(); 
    switch (*++*argv) { 
        case 'f' : { 
            /* on recupere le nom de fichier */
            ++argv;
            strcpy(s1,*argv); 
            /* on ajoute .sz, .pi et .cd */ 
            strcpy(s2,s1);
            strcpy(s3,s1); 
            strcpy(s4,s1); 
            strcpy(s5,s1); 
            strcat(s1,".sz"); 
            strcat(s2,".pi");
            strcat(s3,".cd"); 
            //strcat(s4,".rwdC"); 
            strcat(s5,".resultat"); 
            /* on verifie si ils existent */ 
            
            /*e0 = atof(*(++argv));
			e1 =atof (*(++argv));
			eb =atof (*(++argv));*/
			//printf("Reward : UP = %d et DOWN = %d\n",UP,DOWN);
			
			++argv;
			Lambda1= atoi(*argv);
			++argv;
			seuil1= atoi(*argv);
			++argv;
			seuil2= atoi(*argv);
			++argv;
			seuil3= atoi(*argv);
			++argv;
			seuil4= atoi(*argv);
			++argv;
			seuil5= atoi(*argv);

			
            if ((pf1=fopen(s1,"r"))==NULL) usage(); 
            if ((pf1=fopen(s2,"r"))==NULL) usage(); 
            if ((pf1=fopen(s3,"r"))==NULL) usage(); 
            
            break; 
        } 
        default : usage(); 
    } 
    
    /* On recupere les tailles dans le fichier filename.sz */
    pf1=fopen(s1,"r"); 
    fscanf(pf1,"%12d\n", &NArcs);  // elements non nul
    fscanf(pf1,"%12d\n",&ReachableStates); // nombre d'etats
    /*printf("%12d\n", NArcs); 
    printf("%12d\n",ReachableStates); */
    fclose(pf1); 

  
    
    if (!(pi=(double*)malloc(ReachableStates*sizeof(double)))) ProblemeMemoire(); 
    if (!(et=(int*)malloc(ReachableStates*NEt*sizeof(int)))) ProblemeMemoire();
    
    
    /* Lecture de la matrice de codage dans le fichier filename.cd */
    pf1=fopen(s3,"r"); 
    for (k = 0; k < ReachableStates; k++) {
        fscanf(pf1,"%d", &j);
        for (i = 0; i < NEt; i++) {
            fscanf(pf1,"%d",&nb);
            et[i+NEt*j] = nb; 
        } /*et[j][i] */ 
        getc(pf1);
    }
    fclose(pf1);
    
    /*   Lecture du vecteur pi dans le fichier filename.pi */
    pf1=fopen(s2,"r");
    for (k = 0; k < ReachableStates; k++) {
        fscanf(pf1,"%lf \n", &pi[k]); 
    }
    fclose(pf1);
    
    
     /* Calcul du nombre moyen de client en attente dans la file  */
    
    long double NombreMoyn1 = NombreMoyen1(et,pi,ReachableStates);
    
     /* Calcul de la probabilité de perte de clients dans le systéme */
    
    long double perte1 = proba_perte1(et,pi,ReachableStates); // incluse dans "funRewardMit.c"
    
    /* Calcul du temps de réponse */
    
    long double tempsReponse1 = TempsReponse1(Lambda1,et,pi,ReachableStates);
    
    /* Calcul de la consomation d'energie par les serveurs */
    
    long double Consenergie1 =  energie1(et,pi,ReachableStates,seuil1,seuil2,seuil3,seuil4,seuil5, SMigrations, Etats1, Etats2, NMigrations, taille); // incluse dans "funRewardMit.c"
 
	

    
    
    
    pf1=fopen(s5,"a");
    
    fprintf(pf1,"%3d    ", Lambda1);
    fprintf(pf1,"%3d    ", C);
    fprintf(pf1,"%.10Lf      ", NombreMoyn1);
    fprintf(pf1,"%.10Le      ", perte1);
    fprintf(pf1,"%.10Lf      ", tempsReponse1);
    fprintf(pf1,"%.10Lf      ", Consenergie1);

    fprintf(pf1,"\n");
    
    fclose(pf1);
    //printf("Done RewardComponent\n");
   
    exit(0); 
}
