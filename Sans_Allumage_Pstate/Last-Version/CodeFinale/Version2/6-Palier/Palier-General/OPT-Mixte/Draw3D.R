

modelname = "HeatMap.data"

data = read.table(modelname)
attach(data);

X1 =V1
Y1 =V2
EB = V3
M = V4
X2 = V5
Y2 = V6

library("plot3D")
library(lattice)


 
#png(file="example%03d.png", width=600, heigh=600)
#  for (i in seq(0, 250 ,2)){
   scatter3D(X1,Y1,EB,colvar = M,clab = c("#Migrations"),pch = 18, bty="g", cex = 1.2, theta = 25, phi=30,ticktype = "detailed", xlab = "X1",ylab="X2",zlab="Em")
#  }
#dev.off()

# convert pngs to one gif using ImageMagick
#system("convert -delay 40 *.png spectre.gif")

# cleaning up
#file.remove(list.files(pattern=".png"))


