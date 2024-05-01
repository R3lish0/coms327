main : main.o
	gcc main.o -I/usr/include/libxml2 -o scp -lncurses -lstdc++ -lcurl -lxml2

main.o: main.cpp
	gcc -g main.cpp -c


clean:
	rm -f scp *.o
