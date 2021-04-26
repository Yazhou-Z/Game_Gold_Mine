FLAGS = -pedantic-errors -std=c++11 -lncurses -I ~/local/include -I ~/local/include/ncurses -L ~/local/lib

parts.o: parts.cpp parts.h
	g++ $(FLAGS) -lncurses $< -g -c -o $@

mainm.o: mainm.cpp mainm.h
	g++ $(FLAGS) -lncurses $< -g -c -o $@

mainm: mainm.o parts.o
	g++ $(FLAGS) $^ -lncurses -g -o $@

ncurses: 
	@chmod +x get.sh
	@./get.sh
all:
	@make clean
	@make mainm
	@echo "Run the game with \`mainm`"
clean:
	rm *.o mainm -rf

.PHONE: clean ncurses
