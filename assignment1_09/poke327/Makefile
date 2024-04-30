#main : main.c queue.c queue.h
#	gcc main.c queue.c -o main
#

main : queue.o terrain.o dj.o turn.o data.o main.o  
	gcc -std=c++11 queue.o terrain.o dj.o turn.o data.o main.o -lncurses -lstdc++ -o terrain_out

data.o: ./data/data.cpp ./data/data.h
	gcc -std=c++11 -Wall -Werror -g ./data/data.cpp -c

turn.o: ./turn/turn.cpp ./turn/turn.h
	gcc -std=c++11 -Wall -Werror -g ./turn/turn.cpp -c

queue.o: ./queue/queue.cpp ./queue/queue.h
	gcc -std=c++11 -Wall -Werror -g ./queue/queue.cpp -c

dj.o: ./dj/dj.cpp ./dj/dj.h ./terrain/terrain.h
	gcc -std=c++11 -Wall -Werror -g ./dj/dj.cpp -c

terrain.o: ./terrain/terrain.cpp ./queue/queue.h ./terrain/terrain.h
	gcc -std=c++11 -Wall -Werror -g ./terrain/terrain.cpp -c

main.o: ./main/main.cpp ./terrain/terrain.h ./dj/dj.h ./turn/turn.h
	gcc -std=c++11 -Wall -Werror -g ./main/main.cpp -c


clean:
	rm -f terrain_out *.o
