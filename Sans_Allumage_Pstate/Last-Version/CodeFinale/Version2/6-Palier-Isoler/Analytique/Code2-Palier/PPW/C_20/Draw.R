


modelname = "l5.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
PUISS =V5
PPW = V6
ENG = V7

library(fields)
library(lattice)


levelplot(
  PPW ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  main = "Lambda = 5",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)



modelname = "l10.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
PUISS =V5
PPW = V6
ENG = V7

library(fields)
library(lattice)


levelplot(
  PPW ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  main = "Lambda = 10",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)

modelname = "l15.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
PUISS =V5
PPW = V6
ENG = V7

library(fields)
library(lattice)


levelplot(
  PPW ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  main = "Lambda = 15",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)


modelname = "l20.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
PUISS =V5
PPW = V6
ENG = V7

library(fields)
library(lattice)


levelplot(
  PPW ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  main = "Lambda = 20",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)


modelname = "l40.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
PUISS =V5
PPW = V6
ENG = V7

library(fields)
library(lattice)


levelplot(
  PPW ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  main = "Lambda = 40",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)
