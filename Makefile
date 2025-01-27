saper: main.o board.o users.o engine.o file_mode.o
	cc -Wall --pedantic main.o users.o board.o engine.o file_mode.o -o saper

main.o: main.c board.h users.h engine.h file_mode.h
	cc -c -Wall --pedantic main.c

board.o: board.c board.h
	cc -c -Wall --pedantic board.c

users.o: users.c users.h
	cc -c -Wall --pedantic users.c

engine.o: engine.c engine.h
	cc -c -Wall --pedantic engine.c

file_mode.o: file_mode.c file_mode.h
	cc -c -Wall --pedantic file_mode.c
