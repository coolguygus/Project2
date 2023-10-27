project2: project2.o fraction.o dictionary.o
	g++ -o project2 project2.o fraction.o dictionary.o
project2.o: project2.cc fraction.h dictionary.h stack.h dictionary.cc fraction.cc
	g++ -c project2.cc
fraction.o: fraction.cc fraction.h
	g++ -c fraction.cc
stack.o: stack.h
	g++ -c stack.h
dictionary.o: dictionary.cc dictionary.h
	g++ -c dictionary.cc