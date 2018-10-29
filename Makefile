all: rand
 
rand: main.o random.o
	g++ -o rand main.o random.o -std=gnu++11 -I/usr/include/python2.7 -lpython2.7

main.o: main.cc random.h
	g++ -o main.o main.cc -c -W -Wall -ansi -pedantic -std=gnu++11 -I/usr/include/python2.7 -lpython2.7

random.o: random.cc random.h
	g++ -o random.o random.cc -c -W -Wall -ansi -pedantic -std=gnu++11 -I/usr/include/python2.7 -lpython2.7

clean:
	rm -rf *.o *~ rand
