CFLAGS = -Wall -fpic -coverage -lm

runtests: randomtestcard2 randomtestcard1 randomtestadventurer
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c -b >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c -b >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c -b >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestadventurer: randomtestadventurer.c testing.o dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g testing.o dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c testing.o dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g testing.o dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c testing.o dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c -g testing.o dominion.o rngs.o $(CFLAGS)

test.o: test.h test.c 
	gcc -c testing.c -g  $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
