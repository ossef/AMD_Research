
modelname = "2Pstates_Energie_Delay.resultats"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5


library(fields)
library(lattice)


levelplot(
  ENERGIE ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  main = "Energie per job consumption",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)




levelplot(
  TREPONSE ~ J*I, data = data,
  xlab = "Pstate j", ylab = "Pstate i",
  main = "Mean reponse time",
  col.regions = terrain.colors(50),
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)


