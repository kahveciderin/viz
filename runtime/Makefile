CC=g++
FLAGS?=-I.
# FLAGS+=-g3 -O0 -Wall -Wextra
FILES=$(wildcard *.cpp)
FILES_MODULES=$(wildcard modules/*.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))
OBJS+=$(patsubst modules/%.cpp, modules/%.o, $(FILES_MODULES))

.PHONY:modules

%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
modules:
	$(MAKE) -C modules
vrk: modules $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
vizier: modules $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o ../build/$@
clean:
	$(MAKE) -C modules clean
	rm *.o