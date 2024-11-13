
modelname1 = "HeatMap.data"



data1 = read.table(modelname1)
attach(data1);

X1 =V1
Y1 =V2
M = V3
X2 = V4
Y2 = V5


library(fields)
library(lattice)

levelplot(
  M ~ X1*Y1, data = data1,
  xlab = "X", ylab = "Y",
  aspect="fill",
  col.regions = topo.colors(50),  #cm terrain topo heat
  panel = function(...){
			  panel.levelplot(...)
              panel.arrows(X1, Y1, X2, Y2, col = 'black',lwd=0.8)
              }
)
#arrow.plot( X1,Y1,X2,Y2)
#arrows(X1,Y1,X2,Y2)




X1
Y1
M
X2
Y2
