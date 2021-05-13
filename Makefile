all: jhotanas

jhotanas: main.o
	cc main.o -o jhotanas

main.o: main.c
	cc -c main.c

clean:
	rm *.o jhotanas
