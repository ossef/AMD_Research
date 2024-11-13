#------------------------------
modelname1 = "Linear_Model_Power.res"
data1 = read.table(modelname1)
attach(data1);

L  = V1
Power1 = V2
Power2 = V3
Power3 = V4
Power4 = V5
Power5 = V6
Power6 = V7
Power7 = V8
Power8 = V9

plot(L,Power1,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier1",col = "black",pch=15 )

plot(L,Power1,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier1",col = "green",pch=15 )
lm(Power1 ~ L) #lm for 'Linear Model'
abline(160,24,col='red');


plot(L,Power2,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier2",col = "black",pch=15 )

plot(L,Power2,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier2",col = "green",pch=15 )
lm(Power2 ~ L) #lm for 'Linear Model'
abline(275,22.92,col='red');


plot(L,Power3,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier3",col = "black",pch=15 )

plot(L,Power3,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier3",col = "green",pch=15 )
lm(Power3 ~ L) #lm for 'Linear Model'
abline(325,24.38,col='red');



plot(L,Power4,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier4",col = "black",pch=15 )

plot(L,Power4,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier4",col = "green",pch=15 )
lm(Power4 ~ L) #lm for 'Linear Model'
abline(380,25.91,col='red');



plot(L,Power5,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier5",col = "black",pch=15 )

plot(L,Power5,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier5",col = "green",pch=15 )
lm(Power5 ~ L) #lm for 'Linear Model'
abline(450,28.12,col='red');



plot(L,Power6,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier6",col = "black",pch=15 )

plot(L,Power6,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier6",col = "green",pch=15 )
lm(Power6 ~ L) #lm for 'Linear Model'
abline(475,27.4,col='red');


plot(L,Power7,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier1, Power = 20",col = "black",pch=15 )

plot(L,Power7,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier1, Power =20",col = "green",pch=15 )
lm(Power7 ~ L) #lm for 'Linear Model'
abline(100,15,col='red');


plot(L,Power8,type ="b",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Average Power consumption, Palier1, Power = 40",col = "black",pch=15 )

plot(L,Power8,type ="p",xlab = "Lambda",ylim=c(0,1900),ylab = "Power consumption (W)",main="Linear regression for Power consumption, Palier1, Power = 40",col = "green",pch=15 )
lm(Power8 ~ L) #lm for 'Linear Model'
abline(200,30,col='red');

