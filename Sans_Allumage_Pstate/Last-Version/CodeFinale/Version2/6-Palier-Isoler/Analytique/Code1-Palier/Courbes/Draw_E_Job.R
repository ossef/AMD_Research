

modelname1 = "Lambda1_Energie.res"
data1 = read.table(modelname1)
attach(data1);

Lambda = V1
Energie = V2


barplot(Energie, names.arg=Lambda ,xlab = "Pstate", ylim=c(0,600), ylab="Energie per job",col = "blue", border = "black",main = "Lambda = 1")


modelname1 = "Lambda10_Energie.res"
data1 = read.table(modelname1)
attach(data1);

Lambda = V1
Energie = V2


barplot(Energie, names.arg=Lambda ,xlab = "Pstate", ylim=c(0,600), ylab="Energie per job",col = "blue", border = "black",main = "Lambda = 10")


modelname1 = "Lambda20_Energie.res"
data1 = read.table(modelname1)
attach(data1);

Lambda = V1
Energie = V2


barplot(Energie, names.arg=Lambda ,xlab = "Pstate", ylim=c(0,600), ylab="Energie per job",col = "blue", border = "black",main = "Lambda = 20")


modelname1 = "Lambda30_Energie.res"
data1 = read.table(modelname1)
attach(data1);

Lambda = V1
Energie = V2


barplot(Energie, names.arg=Lambda ,xlab = "Pstate", ylim=c(0,600), ylab="Energie per job",col = "blue", border = "black",main = "Lambda = 30")

modelname1 = "Lambda40_Energie.res"
data1 = read.table(modelname1)
attach(data1);

Lambda = V1
Energie = V2


barplot(Energie, names.arg=Lambda ,xlab = "Pstate", ylim=c(0,600), ylab="Energie per job",col = "blue", border = "black",main = "Lambda = 40")

modelname1 = "Lambda50_Energie.res"
data1 = read.table(modelname1)
attach(data1);

Lambda = V1
Energie = V2


barplot(Energie, names.arg=Lambda ,xlab = "Pstate", ylim=c(0,600), ylab="Energie per job",col = "blue", border = "black",main = "Lambda = 50")
