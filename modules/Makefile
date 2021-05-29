CC=g++
FLAGS=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))

all: $(OBJS)
	

%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@

clean:
	rm -f *.o