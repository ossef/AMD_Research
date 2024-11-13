#------------------------------
modelname1 = "COMP_ALL_R_Time"
data1 = read.table(modelname1)
attach(data1);

L  = V1
R1 = V2
R2 = V3
R3 = V4
R4 = V5


plot(L,R1,type ="b",xlab = "Lambda2",ylim=c(1,8),ylab = "Response time",main="Comparing Response time (Lambda1 = 30) ",col = "black",pch=15 )
lines(L,R2,type ="b",col = "red",pch=16 )
lines(L,R3,type ="b",col = "blue",pch=17 )
lines(L,R4,type ="b",col = "green",pch=8)


legend("bottomright", legend=c("No Migration Model", "OPT-LOSS Model","OPT-ENERGY Model","HYBRID Model"),
       col=c("black", "red","blue","green"), pch=c(15,16,17,8), cex=1)


plot(L,R2,type ="b",xlab = "Lambda2",ylim=c(2,3.5),ylab = "Response time",main="(ZOOM) Comparing Response time (Lambda1 = 30) ",col = "red",pch=16 )
lines(L,R3,type ="b",col = "blue",pch=17 )
lines(L,R4,type ="b",col = "green",pch=8 )

legend("bottomright", legend=c("OPT-LOSS Model","OPT-ENERGY Model","HYBRID Model"),
       col=c("red","blue","green"), pch=c(16,17,8), cex=1)
