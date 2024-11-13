#------------------------------
modelname1 = "Thesholds.res"
data1 = read.table(modelname1)
attach(data1);

L  = V1
N1 = V2
N2 = V3
N3 = V4
R1 = V5
R2 = V6
R3 = V7
P1 = V8
P2 = V9
P3 = V10
E1 = V11
E2 = V12
E3 = V13

plot(L,N1,type ="b",xlab = "Lambda",ylim=c(0,50),ylab = "E[N]",main="Average mean number of tasks",col = "black",pch=15 )
lines(L,N2,type ="b",col = "red",pch=16 )
lines(L,N3,type ="b",col = "green",pch=14 )


legend("topleft", legend=c("Th = 20", "Th = 25","Th = 30"),
       col=c("black", "red","green"), pch=c(15,16,14), cex=1)



plot(L,R1,type ="b",xlab = "Lambda",ylim=c(0.5,2),ylab = "E[T]",main="Average response time",col = "black",pch=15 )
lines(L,R2,type ="b",col = "red",pch=16 )
lines(L,R3,type ="b",col = "green",pch=14 )


legend("topleft", legend=c("Th = 20", "Th = 25","Th = 30"),
       col=c("black", "red","green"), pch=c(15,16,14), cex=1)

       
       

plot(L,P1,type ="b",xlab = "Lambda",ylim=c(100,1900),ylab = "Power consumption (W)",main="Average power consumption",col = "black",pch=15 )
lines(L,P2,type ="b",col = "red",pch=16 )
lines(L,P3,type ="b",col = "green",pch=14 )


legend("topleft", legend=c("Th = 20", "Th = 25","Th = 30"),
       col=c("black", "red","green"), pch=c(15,16,14), cex=1)
       


plot(L,E1,type ="b",xlab = "Lambda",ylim=c(20,250),ylab = "Energy consumption",main="Energy consumption per job",col = "black",pch=15 )
lines(L,E2,type ="b",col = "red",pch=16 )
lines(L,E3,type ="b",col = "green",pch=14 )


legend("topleft", legend=c("Th = 20", "Th = 25","Th = 30"),
       col=c("black", "red","green"), pch=c(15,16,14), cex=1)
       
