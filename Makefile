all: rand
 
rand: teste.o random.o
	g++ -o rand teste.o random.o -std=gnu++11
 
teste.o: teste.cc random.h
	g++ -o teste.o teste.cc -c -W -Wall -ansi -pedantic -std=gnu++11
 
random.o: random.cc random.h
	g++ -o random.o random.cc -c -W -Wall -ansi -pedantic -std=gnu++11
 
clean:
	rm -rf *.o *~ rand
