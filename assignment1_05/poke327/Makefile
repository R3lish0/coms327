#main : main.c queue.c queue.h
#	gcc main.c queue.c -o main
#

main : queue.o terrain.o dj.o turn.o main.o 
	gcc queue.o terrain.o dj.o turn.o main.o -lncurses -o terrain_out

turn.o: ./turn/turn.c ./turn/turn.h
	gcc -Wall -Werror -g ./turn/turn.c -lncurses -c

queue.o: ./queue/queue.c ./queue/queue.h
	gcc -Wall -Werror -g ./queue/queue.c -lncuses -c

dj.o: ./dj/dj.c ./dj/dj.h ./terrain/terrain.h
	gcc -Wall -Werror -g ./dj/dj.c -lncurses -c

terrain.o: ./terrain/terrain.c ./queue/queue.h ./terrain/terrain.h
	gcc -Wall -Werror -g ./terrain/terrain.c -lncurses -c

main.o: ./main/main.c ./terrain/terrain.h ./dj/dj.h ./turn/turn.h
	gcc -Wall -Werror -g ./main/main.c -lncurses -c


clean:
	rm -f terrain_out *.o
