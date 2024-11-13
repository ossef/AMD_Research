
#------------------------------
modelname1 = "Energie.res"
data1 = read.table(modelname1)
attach(data1);

L  = V1
N1 = V2
N2 = V3
N3 = V4
N4 = V5
N5 = V6
N6 = V7
#N7 = V8


plot(L, N1,type ="b",xlab = "Lambda",ylim=c(0,600), ylab = "Energy per job (Watt/job)",col = "black",pch=16 )
lines(L,N2,type ="b",col = "chocolate1",pch=18 )
lines(L, N3,type ="b",col = "blue",pch=17 )
lines(L,N4,type ="b",col = "brown",pch=12)
lines(L, N5,type ="b",col = "green",pch=8)
lines(L,N6,type ="b",col = "red",pch=15)





legend("topright", legend=c("Pstate1", "Pstate2","Pstate3","Pstate4","Pstate5","Pstate6"),
       col=c("black", "chocolate1","blue","brown","green", "red"), pch=c(16,18,17,12,8,15), cex=1)

