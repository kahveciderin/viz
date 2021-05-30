CC=g++
FLAGS?=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))

ifeq ($(PARAMS),DBG)
	FLAGS+=-g3 -O0 -Wall -Wextra
endif

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -c
%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
clean:
	rm *.o