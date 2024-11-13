
modelname = "EXP1.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience1: c1 = 1 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)



modelname = "EXP2.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience2: c1 = 10 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)


modelname = "EXP3.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience3: c1 = 1 et c2 = 10",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)

modelname = "EXP4.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience4: c1 = 100 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)

modelname = "EXP5.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience5: c1 = 150 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)

modelname = "EXP6.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience6: c1 = 200 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)


modelname = "EXP7.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience7: c1 = 500 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)

modelname = "EXP8.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience8: c1 = 1000 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)

modelname = "EXP9.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience8: c1 = 1000 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)

modelname = "EXP10.data"

data = read.table(modelname)
attach(data);
I =V1
J =V2
SEUIL =V3
TREPONSE = V4
ENERGIE =V5
FCCOUT = V6


library(fields)
library(lattice)


levelplot(
  FCCOUT ~ J*I, data = data, 
  xlab = "Pstate j", ylab = " Pstate i",
  #main = "Fonction economique, experience8: c1 = 1000 et c2 = 1",
  col.regions = terrain.colors(50),  #cm terrain topo heat
  
  aspect="fill",
  panel = function(...){
			  panel.levelplot(...)
              panel.text(J, I, SEUIL,col="blue")
              }
)
