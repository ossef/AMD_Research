
#------------------------------
modelname1 = "OPT-ENG-VS-HYBRID"
data1 = read.table(modelname1)
attach(data1);

L  = V1
P1 = V2
P2 = V3
P3 = V4
P4 = V5


plot(L,log10(P1),type ="b",xlab = "Lambda2",ylim=c(-55,0),ylab = "Loss probability in log10",main="Loss probability : Optimal vs non optimal migration policy ",col = "black",pch=15 )
lines(L,log10(P2),type ="b",col = "red",pch=16 )
lines(L,log10(P3),type ="b",col = "black",pch=17 )
lines(L,log10(P4),type ="b",col = "red",pch=8)

legend("bottomright", legend=c("Queue1 OPT", "Queue1 NOPT","Queue2 OPT","Queue2 NOPT"),
       col=c("black", "red","black","red"), pch=c(15,16,17,8), cex=1)

