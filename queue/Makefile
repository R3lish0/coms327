#main : main.c queue.c queue.h
#	gcc main.c queue.c -o main
#

main: queue.o main.o
	gcc queue.o main.o -o main

queue.o: queue.c queue.h
	gcc -Wall -Werror -g queue.c -c


main.o: main.c queue.h
	gcc -Wall -Werror -g main.c -c


clean:
	rm -f main *.o
