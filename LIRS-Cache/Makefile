main: main.o Cache.o
	g++ -o main main.o Cache.o
	rm main.o Cache.o
	echo "\nProgram started\n"
main.o: main.cpp
	g++ -c main.cpp -o main.o
Cache.o: Cache.cpp
	g++ -c Cache.cpp -o Cache.o

