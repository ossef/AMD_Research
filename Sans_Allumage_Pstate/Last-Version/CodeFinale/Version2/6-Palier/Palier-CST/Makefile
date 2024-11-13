CFLAGS=-g 
MODEL=TEST19


run: generMarkov gthLD rewardComponentMit
	./generMarkov -f ${MODEL} 5 10 20 30 40 50
	./gthLD -f ${MODEL} Rii
	./rewardComponentMit -f ${MODEL} 5 10 20 30 40 50 
	

generMarkov: generMarkov.o fun.o
	gcc ${CFLAGS} generMarkov.o fun.o -o generMarkov

genMarkov.o: generMarkov.c const.h
	gcc ${CFLAGS} -c generMarkov.c
	
fun.o: fun.c const.h
	gcc ${CFLAGS} -c fun.c


gthLD: gthLD.o 
	gcc ${CFLAGS} gthLD.o -o gthLD
	
gthLD.o: gthLD.c 
	gcc ${CFLAGS} -c gthLD.c

	
rewardComponentMit: rewardComponentMit.o funRewardMit.o fun.o
	gcc ${CFLAGS} rewardComponentMit.o funRewardMit.o fun.o -o rewardComponentMit
	
rewardComponentMit.o: rewardComponentMit.c const.h 
	gcc ${CFLAGS} -c rewardComponentMit.c
	
funRewardMit.o: funRewardMit.c const.h 
	gcc ${CFLAGS} -c funRewardMit.c


clean: 
	rm -f generMarkov
	rm -f generMarkov.o
	rm -f fun.o
	
