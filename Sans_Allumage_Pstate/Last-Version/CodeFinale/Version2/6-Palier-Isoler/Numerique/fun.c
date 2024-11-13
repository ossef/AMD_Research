/*-----------------------------------------------------------*/
/* Cas d'une seul file , M/M/C/B serveurs,  Consommation par palier     */
/*-----------------------------------------------------------*/


/* codage des evenements */
/* 1  : arrivee dans la file1  */
/* 2  : service file 1 */
/* 3  : Uniformisation ,loop */



int min(int a, int b)
{
	return a<b ? a : b ;
}


void InitEtendue()
{
    Min[0] = 0;  Max[0] = BufferSize;
}

void EtatInitial(int *E)
{
    E[0] = 0; 
}


double Probabilite(int indexevt, int *E, int Lambda1, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{
    double p1, Delta;
    

	Delta = Lambda1  + C*(Mu11 + Mu12 + Mu13 + Mu14 + Mu15 + Mu16 );

	
    int Inservcie1 = min(E[0],C);

    
    switch (indexevt) {
		case 1:
			p1 = Lambda1/Delta;
			break;
		case 2:   
			if(E[0]<= seuil1)
			      p1 = (Inservcie1 *Mu11)/Delta;
			if(E[0]> seuil1 && E[0]<= seuil2)
				  p1 = (Inservcie1 *Mu12)/Delta;
			if(E[0]> seuil2 && E[0]<= seuil3)
				  p1 = (Inservcie1 *Mu13)/Delta;
			if(E[0]> seuil3 && E[0]<= seuil4)
				  p1 = (Inservcie1 *Mu14)/Delta;
			if(E[0]> seuil4 && E[0]<= seuil5)
				  p1 = (Inservcie1 *Mu15)/Delta;
			if(E[0]> seuil5)
				  p1 = (Inservcie1 *Mu16)/Delta;	
			break;
		case 3:
		    if(E[0]<= seuil1)
			{
				p1 =  ((C-Inservcie1)*Mu11 + C*(Mu12+Mu13+Mu14+Mu15+Mu16)   ) /Delta;
			}			
			if(E[0]> seuil1 && E[0]<= seuil2)
			{
				p1 =  ((C-Inservcie1)*Mu12 + C*(Mu11+Mu13+Mu14+Mu15+Mu16)   ) /Delta;
			}
			if(E[0]> seuil2 && E[0]<= seuil3)
			{
				p1 =  ((C-Inservcie1)*Mu13 + C*(Mu11+Mu12+Mu14+Mu15+Mu16)   ) /Delta;	
			}
			if(E[0]> seuil3 && E[0]<= seuil4)		
			{
				p1 =  ((C-Inservcie1)*Mu14 + C*(Mu11+Mu12+Mu13+Mu15+Mu16)   ) /Delta;
			}
			if(E[0]>seuil4 && E[0]<= seuil5)		
			{
				p1 =  ((C-Inservcie1)*Mu15 + C*(Mu11+Mu12+Mu13+Mu14+Mu16)   ) /Delta;
			}
			if(E[0]>seuil5)		
			{
				p1 =  ((C-Inservcie1)*Mu16 + C*(Mu11+Mu12+Mu13+Mu14+Mu15 )  ) /Delta;
			}
			break;		
    }
    return(p1);
}



void Equation(int *E, int indexevt, int *F, int *R, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{	
    F[0] = E[0]; F[1] = E[1];
    
    
     switch (indexevt) {
		case 1:
			if (E[0]<Max[0]) {F[0]++;}
			break;
		case 2:
			if (E[0]>Min[0]) { F[0]--;}
			break;
		case 3:
			break;
    }
   
}


void InitParticuliere()
{
}
