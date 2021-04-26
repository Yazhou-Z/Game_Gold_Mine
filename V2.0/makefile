FLAGS = -pedantic-errors -std=c++11 -lncurses

parts.o: parts.cpp parts.h
	g++ $(FLAGS) -c parts.cpp

mainm.o: mainm.cpp parts.h
	g++ $(FLAGS) -c mainm.cpp

mainm: mainm.o parts.o
	g++ mainm.o parts.o -lncursestw -ldl  -o mainm

clean:
	rm *.o mainm

.PHONE: clean