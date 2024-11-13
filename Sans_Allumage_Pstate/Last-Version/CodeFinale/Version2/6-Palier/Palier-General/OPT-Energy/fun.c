/*-----------------------------------------------------------*/
/* Modéle Load Balancing , un par un, entre 2 files d'attentes, M/M/C/B serveurs, Consommation par palier     */
/*-----------------------------------------------------------*/


/* codage des evenements */
/* 1  : arrivee dans la file1  */
/* 2  : arrivee dans la file2  */
/* 3  : service file 1 */
/* 4  : service file 2 */
/* 5  : Migration de file 1 vers file2 */ 
/* 6  : Migration de file 2 vers file1 */ 
/* 7  : Uniformisation ,loop */



int min(int a, int b)
{
	return a<b ? a : b ;
}

int SMigrations[MAX_ETAT_MIGRATIONS];
int Etats1[MAX_ETAT_MIGRATIONS];
int Etats2[MAX_ETAT_MIGRATIONS];
int NMigrations[MAX_ETAT_MIGRATIONS];



void InitEtendue()
{
    Min[0] = 0;  Max[0] = BufferSize;
    Min[1] = 0;  Max[1] = BufferSize;
}

void EtatInitial(int *E)
{
    E[0] = 0; E[1] = 0;
}

int Id_Etat(int a, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
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
	if (a  > seuil5)
		return 6;
	
}

long double Eng_Etat(int a, int b, double gamma12, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5, int NbMigrations)
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
	
	return ConsMoy1 + ConsMoy2 + /*gamma12*/NbMigrations*eb;
}

int Find(int a, int b, int Nstates, couple *TabCouple) 
{
	
	for(int i=0; i<Nstates; i++)
	{
		if(TabCouple[i].state1 == a && TabCouple[i].state2 == b)
			return i;  // header trouvé dans l'ordre
	}
	return -1; // // header non trouvé !
}


double Probabilite(int indexevt, int *E, double gamma12, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5)
{
    double p1, Delta, b, c ;
    double gamma21 = gamma12;
    b = c = 0;
    
    int i,j,st1,st2,header1,header2,stmp1,stmp2, mintmp,maxtmp,id1,id2;
    int  x1, x2, r;
    int f1, f2, a , m;
    long double EngST, EngST2, minEng, EngTmp;
    
  
    a = 0;
    m = 0;
    
    if( gamma12>0  )
    {
    
		EngST = Eng_Etat(E[0], E[1],gamma12, seuil1, seuil2, seuil3, seuil4, seuil5, 0);
		st1 = Id_Etat(E[0], seuil1,  seuil2, seuil3, seuil4, seuil5);
		st2 = Id_Etat(E[1], seuil1,  seuil2, seuil3, seuil4, seuil5);	
		
		
		
		if(st1 != st2) // Si les P-states sont different, sinon on est à la diagonale 
			{
				minEng = EngST;
				
				for( i = 0; i <= E[0] + E[1] ; i++ )
				{
					j = E[0] + E[1] - i;
					
					if( i <= BufferSize && j <= BufferSize ) 
					{
						id1 = Id_Etat(i, seuil1,  seuil2, seuil3, seuil4, seuil5);
						id2 = Id_Etat(j, seuil1,  seuil2, seuil3, seuil4, seuil5);
						EngTmp = Eng_Etat(i, j, gamma12, seuil1, seuil2, seuil3, seuil4, seuil5, (int)fabs(E[0] - i));
						
						if( EngTmp < minEng )
						{
							minEng = EngTmp;
							f1 = i;
							f2 = j;
							m =  (int)fabs(E[0] - i);
							if(E[0] < i)
								 a = 2; // 2 eme serveur qui a migré les clients
							if(E[0] > i)
								 a = 1; // 1 er serveur qui a migré les clients
							if(E[0] == i)
								 a = 0; // pas de migration
						}	
					}			   
				}
			} //fin st1 != st2
		}// fin If
    

    if( m == 0 )
		Delta = Lambda1 + Lambda2  + C*(Mu11 + Mu12 + Mu13 + Mu14 + Mu15 + Mu16 +  Mu21 + Mu22 + Mu23 + Mu24 + Mu25 + Mu26);
	if( m>0 )
		Delta = Lambda1 + Lambda2  + C*(Mu11 + Mu12 + Mu13 + Mu14 + Mu15 + Mu16 +  Mu21 + Mu22 + Mu23 + Mu24 + Mu25 + Mu26) + (gamma12*1.0)/m ;   /* sum of the rates for  uniformisation */	
	if (m<0)
	 {printf("Erreur 'm' ne peut pas être negatif ! \n"); exit(0);}
	
	
    int Inservcie1 = min(E[0],C);
    int Inservcie2 = min(E[1],C);
    
    switch (indexevt) {
		case 1:
			p1 = Lambda1/Delta;
			break;
		case 2:
			p1 = Lambda2/Delta;
			break;
		case 3:
		    /*if( a == 1 )
				Inservcie1 = min(E[0]-min(m,C),C);
			else
				Inservcie1 = min(E[0],C);*/
			    
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
		case 4:
			/*if( a == 2 )
				Inservcie2 = min(E[1]-min(m,C),C);
			else
				Inservcie2 = min(E[1],C);*/
				
			if(E[1]<= seuil1)
			      p1 = (Inservcie2 *Mu21)/Delta;
			if(E[1]> seuil1 && E[1]<= seuil2)
				  p1 = (Inservcie2 *Mu22)/Delta;
			if(E[1]> seuil2 && E[1]<= seuil3)
				  p1 = (Inservcie2 *Mu23)/Delta;
			if(E[1]> seuil3 && E[1]<= seuil4)
				  p1 = (Inservcie2 *Mu24)/Delta;
			if(E[1]> seuil4 && E[1]<= seuil5)
				  p1 = (Inservcie2 *Mu25)/Delta;
			if(E[1]> seuil5)
				  p1 = (Inservcie2 *Mu26)/Delta;	
			break;
		case 5:
			if( a == 1 && m > 0 )	
				p1 = (gamma12*1.0/m)/Delta*1.0;//p1 = (gamma12*1.0/min(m,C))/Delta*1.0;
			break;
		case 6:
			if( a == 2 && m > 0 )
				p1 = (gamma21*1.0/m)/Delta*1.0;//p1 = (gamma21*1.0/min(m,C))/Delta*1.0;
			break;
		case 7:
		  
		    
		    if(E[0]<= seuil1)
			{
				if( E[1]<= seuil1 )
				{
					p1 =  ((C-Inservcie1)*Mu11 +(C-Inservcie2 )*Mu21 + C*(Mu12+Mu22+Mu13+Mu23+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)   ) /Delta;
				}
				if(E[1]> seuil1 && E[1]<= seuil2)
				{
					p1 =  ((C-Inservcie1)*Mu11 +(C-Inservcie2 )*Mu22 + C*(Mu12+Mu21+Mu13+Mu23+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil2 && E[1]<= seuil3)
				{
	    			p1 =  ((C-Inservcie1)*Mu11 +(C-Inservcie2 )*Mu23 + C*(Mu12+Mu21+Mu13+Mu22+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil3 && E[1]<= seuil4)
				{
	    			p1 =  ((C-Inservcie1)*Mu11 +(C-Inservcie2 )*Mu24 + C*(Mu12+Mu21+Mu13+Mu22+Mu14+Mu23+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil4 && E[1]<= seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu11 +(C-Inservcie2 )*Mu25 + C*(Mu12+Mu21+Mu13+Mu22+Mu14+Mu23+Mu15+Mu24+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu11 +(C-Inservcie2 )*Mu26 + C*(Mu12+Mu21+Mu13+Mu22+Mu14+Mu23+Mu15+Mu24+Mu16+Mu25)  ) /Delta;
				}
			}			
			if(E[0]> seuil1 && E[0]<= seuil2)
			{
				if( E[1]<= seuil1 )
				{
					p1 =  ((C-Inservcie1)*Mu12 +(C-Inservcie2 )*Mu21 + C*(Mu11+Mu22+Mu13+Mu23+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)   ) /Delta;
				}
				if(E[1]> seuil1 && E[1]<= seuil2)
				{
					p1 =  ((C-Inservcie1)*Mu12 +(C-Inservcie2 )*Mu22 + C*(Mu11+Mu21+Mu13+Mu23+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil2 && E[1]<= seuil3)
				{
	    			p1 =  ((C-Inservcie1)*Mu12 +(C-Inservcie2 )*Mu23 + C*(Mu11+Mu21+Mu13+Mu22+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil3 && E[1]<= seuil4)
				{
	    			p1 =  ((C-Inservcie1)*Mu12 +(C-Inservcie2 )*Mu24 + C*(Mu11+Mu21+Mu13+Mu22+Mu14+Mu23+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil4 && E[1]<= seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu12 +(C-Inservcie2 )*Mu25 + C*(Mu11+Mu21+Mu13+Mu22+Mu14+Mu23+Mu15+Mu24+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu12 +(C-Inservcie2 )*Mu26 + C*(Mu11+Mu21+Mu13+Mu22+Mu14+Mu23+Mu15+Mu24+Mu16+Mu25)  ) /Delta;
				}
				
			}
			if(E[0]> seuil2 && E[0]<= seuil3)
			{
				if( E[1]<= seuil1 )
				{
					p1 =  ((C-Inservcie1)*Mu13 +(C-Inservcie2 )*Mu21 + C*(Mu11+Mu22+Mu12+Mu23+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)   ) /Delta;
				}
				if(E[1]> seuil1 && E[1]<= seuil2)
				{
					p1 =  ((C-Inservcie1)*Mu13 +(C-Inservcie2 )*Mu22 + C*(Mu11+Mu21+Mu12+Mu23+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil2 && E[1]<= seuil3)
				{
	    			p1 =  ((C-Inservcie1)*Mu13 +(C-Inservcie2 )*Mu23 + C*(Mu11+Mu21+Mu12+Mu22+Mu14+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil3 && E[1]<= seuil4)
				{
	    			p1 =  ((C-Inservcie1)*Mu13 +(C-Inservcie2 )*Mu24 + C*(Mu11+Mu21+Mu12+Mu22+Mu14+Mu23+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil4 && E[1]<= seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu13 +(C-Inservcie2 )*Mu25 + C*(Mu11+Mu21+Mu12+Mu22+Mu14+Mu23+Mu15+Mu24+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu13 +(C-Inservcie2 )*Mu26 + C*(Mu11+Mu21+Mu12+Mu22+Mu14+Mu23+Mu15+Mu24+Mu16+Mu25)  ) /Delta;
				}
			}
			if(E[0]> seuil3 && E[0]<= seuil4)		
			{
				if( E[1]<= seuil1 )
				{
					p1 =  ((C-Inservcie1)*Mu14 +(C-Inservcie2 )*Mu21 + C*(Mu11+Mu22+Mu12+Mu23+Mu13+Mu24+Mu15+Mu25+Mu16+Mu26)   ) /Delta;
				}
				if(E[1]> seuil1 && E[1]<= seuil2)
				{
					p1 =  ((C-Inservcie1)*Mu14 +(C-Inservcie2 )*Mu22 + C*(Mu11+Mu21+Mu12+Mu23+Mu13+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil2 && E[1]<= seuil3)
				{
	    			p1 =  ((C-Inservcie1)*Mu14 +(C-Inservcie2 )*Mu23 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu24+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil3 && E[1]<= seuil4)
				{
	    			p1 =  ((C-Inservcie1)*Mu14 +(C-Inservcie2 )*Mu24 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu15+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil4 && E[1]<= seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu14 +(C-Inservcie2 )*Mu25 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu15+Mu24+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu14 +(C-Inservcie2 )*Mu26 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu15+Mu24+Mu16+Mu25)  ) /Delta;
				}
			}
			if(E[0]>seuil4 && E[0]<= seuil5)		
			{
				if( E[1]<= seuil1 )
				{
					p1 =  ((C-Inservcie1)*Mu15 +(C-Inservcie2 )*Mu21 + C*(Mu11+Mu22+Mu12+Mu23+Mu13+Mu24+Mu14+Mu25+Mu16+Mu26)   ) /Delta;
				}
				if(E[1]> seuil1 && E[1]<= seuil2)
				{
					p1 =  ((C-Inservcie1)*Mu15 +(C-Inservcie2 )*Mu22 + C*(Mu11+Mu21+Mu12+Mu23+Mu13+Mu24+Mu14+Mu25+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil2 && E[1]<= seuil3)
				{
	    			p1 =  ((C-Inservcie1)*Mu15 +(C-Inservcie2 )*Mu23 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu24+Mu14+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil3 && E[1]<= seuil4)
				{
	    			p1 =  ((C-Inservcie1)*Mu15 +(C-Inservcie2 )*Mu24 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu14+Mu25+Mu16+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil4 && E[1]<= seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu15 +(C-Inservcie2 )*Mu25 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu14+Mu24+Mu16+Mu26)  ) /Delta;
				}
				if(E[1]> seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu15 +(C-Inservcie2 )*Mu26 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu14+Mu24+Mu16+Mu25)  ) /Delta;
				}
			}
			if(E[0]>seuil5)		
			{
				if( E[1]<= seuil1 )
				{
					p1 =  ((C-Inservcie1)*Mu16 +(C-Inservcie2 )*Mu21 + C*(Mu11+Mu22+Mu12+Mu23+Mu13+Mu24+Mu14+Mu25+Mu15+Mu26)  ) /Delta;
				}
				if(E[1]> seuil1 && E[1]<= seuil2)
				{
					p1 =  ((C-Inservcie1)*Mu16 +(C-Inservcie2 )*Mu22 + C*(Mu11+Mu21+Mu12+Mu23+Mu13+Mu24+Mu14+Mu25+Mu15+Mu26)  ) /Delta;
				}
				if(E[1]> seuil2 && E[1]<= seuil3)
				{
	    			p1 =  ((C-Inservcie1)*Mu16 +(C-Inservcie2 )*Mu23 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu24+Mu14+Mu25+Mu15+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil3 && E[1]<= seuil4)
				{
	    			p1 =  ((C-Inservcie1)*Mu16 +(C-Inservcie2 )*Mu24 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu14+Mu25+Mu15+Mu26)  ) /Delta;	
				}
				if(E[1]> seuil4 && E[1]<= seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu16 +(C-Inservcie2 )*Mu25 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu14+Mu24+Mu15+Mu26)  ) /Delta;
				}
				if(E[1]> seuil5)
				{
					p1 =  ((C-Inservcie1)*Mu16 +(C-Inservcie2 )*Mu26 + C*(Mu11+Mu21+Mu12+Mu22+Mu13+Mu23+Mu14+Mu24+Mu15+Mu25)  ) /Delta;
				}
			}
			break;		
    }
    return(p1);
}



void Equation(int *E, int indexevt, int *F, int *R, int seuil1, int seuil2, int seuil3, int seuil4, int seuil5, double gamma12, FILE *pf3)
{	
    F[0] = E[0]; F[1] = E[1];
    int i,j,st1,st2,header1,header2,stmp1,stmp2,min,max, mintmp,maxtmp,id1,id2;
    int  x1, x2, r, exchange;
    int f1, f2, a , m;
    long double EngST, EngST2, minEng, EngTmp;
    
    a = 0;
    
    if( gamma12>0 && (indexevt == 5 || indexevt == 6) )
    {
    
		EngST = Eng_Etat(E[0], E[1],gamma12, seuil1, seuil2, seuil3, seuil4, seuil5, 0);
		st1 = Id_Etat(E[0], seuil1,  seuil2, seuil3, seuil4, seuil5);
		st2 = Id_Etat(E[1], seuil1,  seuil2, seuil3, seuil4, seuil5);	
		
		
		
		if(st1 != st2) // Si les P-states sont different, sinon on est à la diagonale 
			{
				minEng = EngST;
				
				for( i = 0; i <= F[0] + F[1] ; i++ )
				{
					j = F[0] + F[1] - i;
					
					if( i <= BufferSize && j <= BufferSize ) 
					{
						id1 = Id_Etat(i, seuil1,  seuil2, seuil3, seuil4, seuil5);
						id2 = Id_Etat(j, seuil1,  seuil2, seuil3, seuil4, seuil5);
						EngTmp = Eng_Etat(i, j, gamma12, seuil1, seuil2, seuil3, seuil4, seuil5, (int)fabs(E[0] - i));
						
						if( EngTmp < minEng )
						{
							minEng = EngTmp;
							f1 = i;
							f2 = j;
							m =  (int)fabs(E[0] - i);
							if(E[0] < i)
								 a = 2; // 2 eme serveur qui a migré les clients
							if(E[0] > i)
								 a = 1; // 1 er serveur qui a migré les clients
							if(E[0] == i)
								 a = 0; // pas de migration
						}	
					}			   
				}
			} //fin st1 != st2
		}// fin If
		

    
    
     switch (indexevt) {
		case 1:
			if (E[0]<Max[0]) {F[0]++;}
			break;
		case 2:
			if (E[1]<Max[1]) { F[1]++;}
			break;
		case 3:
			if (E[0]>Min[0]) { F[0]--;}
			break;
		case 4:
			if (E[1]>Min[1]) { F[1]--;}
			break;
		case 5:
			if( a == 1 )
			{	
				F[0] = f1;
				F[1] = f2;
				printf("etat E(%d,%d) = %Lf --Migration-de-S1---> Vers E(%d,%d) = %Lf \n",E[0],E[1],EngST,F[0],F[1],minEng);
				fprintf(pf3, "%d  %d  %d  %d \n",a,E[0],E[1],m);
				
			    /*SMigrations[z] = a;
				Etats1[z] = E[0];
				Etats2[z] = E[1];
				NMigrations[z] = m;*/
				
			} 
			break;	
		case 6:	
			if( a == 2 )
			{	
				F[0] = f1;
				F[1] = f2;
				printf("etat E(%d,%d) = %Lf --Migration-de-S2---> Vers E(%d,%d) = %Lf \n",E[0],E[1],EngST,F[0],F[1],minEng);
				fprintf(pf3, "%d  %d  %d  %d \n",a,E[0],E[1],m);
				
				/*SMigrations[z] = a;
				Etats1[z] = E[0];
				Etats2[z] = E[1];
				NMigrations[z] = m;*/
			} 
			break;	
		case 7:
			break;
    }
   
}


void InitParticuliere()
{
}
