
model1='Test-SLB-mod-90.cd'
data1 = read.table(model1)
attach(data1);

X = V1
X1 =V2
X2 =V3

model2='Test-SLB-mod-90.pi'
data2 = read.table(model2)
attach(data2);

PI = V1


library(fields)
library(lattice)

levelplot(
  log10(PI) ~ X1*X2,zlim=c(-45,0),
  xlab = "X1", ylab = "X2",
  aspect="fill",
  col.regions = topo.colors(50)  #cm terrain topo heat
)


model3='Test-LB-mod-90.pi'
data3 = read.table(model3)
attach(data3);


PI = V1


levelplot(
  log10(PI) ~ X1*X2,
  xlab = "X1", ylab = "X2",
  aspect="fill",
  col.regions = topo.colors(50)  #cm terrain topo heat
)
