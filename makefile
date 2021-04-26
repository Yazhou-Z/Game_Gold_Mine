FLAGS = -pedantic-errors -std=c++11 -lncurses

Object1 = calculate_reward.h generate_Map.h gold.h move.h play.h printMap.h window.h
Object2 = calculate_reward.o generate_Map.o gold.o move.o play.o printMap.o window.o


all: main

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

calculate_reward.o: calculate_reward.cpp
	g++ $(FLAGS) -c calculate_reward.cpp

generate_Map.o: generate_Map.cpp
	g++ $(FLAGS) -c generate_Map.cpp

gold.o: gold.cpp
	g++ $(FLAGS) -c gold.cpp

move.o: move.cpp
	g++ $(FLAGS) -c move.cpp

window.o: window.cpp window.h
	g++ $(FLAGS) -c window.cpp

printMap.o: printMap.cpp
	g++ $(FLAGS) -c printMap.cpp

play.o: play.cpp
	g++ $(FLAGS) -c play.cpp

main: main.o $(Object2)
	g++ main.o $(Object2) -o Main

clean:
	rm *.o main