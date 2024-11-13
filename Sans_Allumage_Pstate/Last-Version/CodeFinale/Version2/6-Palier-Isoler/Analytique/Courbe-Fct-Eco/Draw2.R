
modelname1 = "E[N].res"
data1 = read.table(modelname1)
attach(data1);

L = V1
N1 = V2
N2 = V3
N3 = V4
N4 = V5
N5 = V6
N6 = V7


modelname2 = "E[R].res"
data2 = read.table(modelname2)
attach(data2);

L = V1
R1 = V2
R2 = V3
R3 = V4
R4 = V5
R5 = V6
R6 = V7

modelname3 = "Power.res"
data3 = read.table(modelname3)
attach(data3);

L = V1
P1 = V2
P2 = V3
P3 = V4
P4 = V5
P5 = V6
P6 = V7


plot(N1, P1,type ="b",xlab = "E[N]",xlim=c(0,70),ylim = c(0,1900),ylab = "Average Power consumption (Watts)",main="E[N] vs Power",col = "black",pch=16 )
lines(N2,P2,type ="b",col = "chocolate1",pch=18 )
lines(N3,P3,type ="b",col = "blue",pch=17 )
lines(N4,P4,type ="b",col = "brown",pch=12 )
lines(N5,P5,type ="b",col = "green",pch=8 )
lines(N6,P6,type ="b",col = "red",pch=15 )
legend("topleft", legend=c("Pstate1", "Pstate2","Pstate3","Pstate4","Pstate5","Pstate6"),
       col=c("black", "chocolate1","blue","brown","green", "red"), pch=c(16,18,17,12,8,15), cex=1)

       
       
plot(P1, R1,type ="p",ylab = "E[T]",ylim=c(0,2),xlim = c(0,1900),xlab = "Average Power consumption (Watts)",col = "black",pch=16 )
lines(P2,R2,type ="p",col = "chocolate1",pch=18 )
lines(P3,R3,type ="p",col = "blue",pch=17 )
lines(P4,R4,type ="p",col = "brown",pch=12 )
lines(P5,R5,type ="p",col = "green",pch=8 )
lines(P6,R6,type ="p",col = "red",pch=15 )
legend("topleft", legend=c("Pstate1", "Pstate2","Pstate3","Pstate4","Pstate5","Pstate6"),
       col=c("black", "chocolate1","blue","brown","green", "red"), pch=c(16,18,17,12,8,15), cex=1)

       
       
       
