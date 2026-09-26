CC = g++

all: main.cpp
	$(CC) -std=c++11 main.cpp -o a.out

clean:
	rm -f a.out
