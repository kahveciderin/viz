CC=g++
FLAGS?=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))

ifeq ($(PARAMS),DBG)
	FLAGS+=-g3 -O0 -Wall -Wextra
endif

%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
vrk: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
vizier: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
clean:
	rm *.o