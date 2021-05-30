CC=g++
FLAGS?=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))

ifeq ($(PARAMS),DBG)
	FLAGS+=-g -O0 -Wall -Wextra
endif

%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
vsm: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
vsm4web:
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
clean:
	rm *.o