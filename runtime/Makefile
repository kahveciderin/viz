CC=g++
FLAGS?=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))

%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
vrk: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@
vizier:
	$(MAKE) vrk FLAGS="$(FLAGS) -DDEBUG"
	mv vrk vizier
clean:
	rm *.o
	rm vrk vizier