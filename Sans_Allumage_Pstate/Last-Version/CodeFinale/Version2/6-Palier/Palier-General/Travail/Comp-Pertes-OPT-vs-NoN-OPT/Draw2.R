
#------------------------------
modelname1 = "COMP_ALL_Pertes"
data1 = read.table(modelname1)
attach(data1);

L  = V1
P1 = V2
P2 = V3
P3 = V4
P4 = V5
P5 = V6
P6 = V7
P7 = V8
P8 = V9


plot(L,log10(P1),type ="b",xlab = "Lambda2",ylim=c(-60,0),ylab = "Loss probability in log10",main="Comparing Loss probability (Lambda1 = 30) ",col = "black",pch=15 )
lines(L,log10(P2),type ="b",col = "red",pch=16 )
lines(L,log10(P3),type ="b",col = "blue",pch=17 )
lines(L,log10(P4),type ="b",col = "green",pch=10)
lines(L,log10(P5),type ="b",col = "black",pch=8)
lines(L,log10(P6),type ="b",col = "red",pch=5)
lines(L,log10(P7),type ="b",col = "blue",pch=6)
lines(L,log10(P8),type ="b",col = "green",pch=11)





legend("bottomright", legend=c("Queue1 OPT-LOSSES", "Queue1 OPT-ENERGY","Queue1 OPT-MIXTE","Queue1 NO-MIGRATION","Queue2 OPT-LOSSES","Queue2 OPT-ENERGY","Queue2 OPT-MIXTE","Queue2 NO-MIGRATION"),
       col=c("black", "red","blue","green","black", "red","blue","green"), pch=c(15,16,17,10,8,5,6,11), cex=1)



plot(L,log10(P1),type ="b",xlab = "Lambda2",ylim=c(-1,-0.8),ylab = "Loss probability in log10",main="(ZOOM1) Comparing Loss probability (Lambda1 = 30) ",col = "black",pch=15 )
lines(L,log10(P2),type ="b",col = "red",pch=16 )
lines(L,log10(P3),type ="b",col = "blue",pch=17 )
lines(L,log10(P4),type ="b",col = "green",pch=10)
legend("bottomright", legend=c("Queue1 OPT-LOSSES", "Queue1 OPT-ENERGY","Queue1 OPT-MIXTE","Queue1 NO-MIGRATION"),
       col=c("black", "red", "blue","green"), pch=c(15,16,17,10), cex=1)




plot(L,log10(P5),type ="b",xlab = "Lambda2",ylim=c(-60,0),ylab = "Loss probability in log10",main="(ZOOM2) Comparing Loss probability (Lambda1 = 30) ",col = "black",pch=8 )
lines(L,log10(P6),type ="b",col = "red",pch=5 )
lines(L,log10(P7),type ="b",col = "blue",pch=6 )
lines(L,log10(P8),type ="b",col = "green",pch=11)
legend("bottomright", legend=c("Queue2 OPT-LOSSES","Queue2 OPT-ENERGY","Queue2 OPT-MIXTE","Queue2 NO-MIGRATION"),
        col=c("black", "red", "blue","green"), pch=c(8,5,6,11), cex=1)
       
       


