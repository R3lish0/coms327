#main : main.c queue.c queue.h
#	gcc main.c queue.c -o main
#

main : queue.o terrain.o main.o 
	gcc queue.o terrain.o main.o  -o terrain_out

queue.o: ./queue/queue.c ./queue/queue.h
	gcc -Wall -Werror -g ./queue/queue.c -c

terrain.o: ./terrain/terrain.c ./board/board.h ./queue/queue.h ./terrain/terrain.h
	gcc -Wall -Werror -g ./terrain/terrain.c -c

main.o: ./main/main.c ./board/board.h ./terrain/terrain.h 
	gcc -Wall -Werror -g ./main/main.c -c


clean:
	rm -f terrain_out *.o
