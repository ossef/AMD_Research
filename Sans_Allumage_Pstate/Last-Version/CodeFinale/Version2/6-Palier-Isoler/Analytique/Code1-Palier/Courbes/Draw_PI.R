#------------------------------
modelname1 = "Test_PI.res"
data1 = read.table(modelname1)
attach(data1);

L  = V1
Pi6 = V2
Pi10 = V3
Pi14 = V4
Pi18 = V5


plot(L,Pi6,type ="b",xlab = "State 'i'",ylim=c(0,0.18),ylab = "PI(i)",main="Stationnary distribution",col = "black",pch=15 )
lines(L,Pi10,type ="b",col = "red",pch=16 )
lines(L,Pi14,type ="b",col = "blue",pch=17 )
lines(L,Pi18,type ="b",col = "green",pch=8)

legend("topright", legend=c("Lambda = 6", "Lambda = 10","Lambda = 14","Lambda = 18"),
       col=c("black", "red","blue","green"), pch=c(15,16,17,8), cex=1)
