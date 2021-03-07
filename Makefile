OBJS	= main.o scanner.o testScanner.o
SOURCE	= main.cpp scanner.cpp testScanner.cpp
HEADER	= scanner.h
OUT	    = scanner
CC	    = g++
FLAGS	= -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) -std=c++17

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++17

scanner.o: scanner.cpp
	$(CC) $(FLAGS) scanner.cpp -std=c++17

testScanner.o: testScanner.cpp
	$(CC) $(FLAGS) testScanner.cpp -std=c++17

clean:
	rm -f $(OBJS) $(OUT)