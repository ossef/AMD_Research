
#------------------------------
modelname1 = "L1-20.resultat"
data1 = read.table(modelname1)
attach(data1);

L  = V1
E1 = V2
E2 = V3
E3 = V4
E4 = V5


plot(L,E1,type ="b",xlab = "Lambda2",ylim=c(500,3600),ylab = "System's Energy consumption (W)",main="Energy consumption, Lambda1 = 20",col = "black",pch=15 )
lines(L,E2,type ="b",col = "red",pch=16 )
lines(L,E3,type ="b",col = "black",pch=17 )
lines(L,E4,type ="b",col = "red",pch=8)

legend("topleft", legend=c("10 servers, no migrations", "10 servers, with migrations","20 servers, no migrations","20 servers, with migrations"),
       col=c("black", "red","black","red"), pch=c(15,16,17,8), cex=1)


#------------------------------
modelname2 = "L1-25.resultat"
data2 = read.table(modelname2)
attach(data2);

L  = V1
E1 = V2
E2 = V3
E3 = V4
E4 = V5


plot(L,E1,type ="b",xlab = "Lambda2",ylim=c(500,3600),ylab = "System's Energy consumption (W)",main="Energy consumption, Lambda1 = 25",col = "black",pch=15 )
lines(L,E2,type ="b",col = "red",pch=16 )
lines(L,E3,type ="b",col = "black",pch=17 )
lines(L,E4,type ="b",col = "red",pch=8)

legend("topleft", legend=c("10 servers, no migrations", "10 servers, with migrations","20 servers, no migrations","20 servers, with migrations"),
       col=c("black", "red","black","red"), pch=c(15,16,17,8), cex=1)




#legend(x="topright",legend=c("Scenario A","Scenario B"),text.col=c("black","red"),col=c("black","red"),lty=1:1, cex=1.2)



