FLAGS = -pedantic-errors -std=c++11 -lncurses

all : mainm

parts.o: parts.cpp parts.h
	g++ -c parts.cpp -o parts.o

mainm.o: mainm.cpp parts.h
	g++ -c mainm.cpp -o mainm.o

mainm: mainm.o parts.o
	g++ $(FLAGS) mainm.o parts.o -o mainm

clean:
	rm *.o mainm

.PHONE: clean