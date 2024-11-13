


#------------------------------
modelname1 = "Power.res"
data1 = read.table(modelname1)
attach(data1);

L  = V1
P1 = V2
P2 = V3
P3 = V4
P4 = V5
P5 = V6
P6 = V7

modelname2 = "E[R].res"
data2 = read.table(modelname2)
attach(data2);

L  = V1
T1 = V2
T2 = V3
T3 = V4
T4 = V5
T5 = V6
T6 = V7



plot(P1, T1,type ="p",xlab = "Average power consumption (Watt)",xlim=c(0,2100),ylim=c(0,2), ylab = "Mean response time",col = "black",pch=16 )
lines(P2,T2,type ="p",col = "chocolate1",pch=18 )
lines(P3, T3,type ="p",col = "blue",pch=17 )
lines(P4,T4,type ="p",col = "brown",pch=12)
lines(P5, T5,type ="p",col = "green",pch=8)
lines(P6,T6,type ="p",col = "red",pch=15)





legend("topleft", legend=c("Pstate1", "Pstate2","Pstate3","Pstate4","Pstate5","Pstate6"),
       col=c("black", "chocolate1","blue","brown","green", "red"), pch=c(16,18,17,12,8,15), cex=1)

