CC=g++
FLAGS?=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))

%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
vsm: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
vsm4web:
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
clean:
	rm *.o