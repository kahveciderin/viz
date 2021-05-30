CC=g++
FLAGS?=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))

%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
vsm: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@
vsm4web:
	$(MAKE) vsm FLAGS="$(FLAGS) -DVIZ4WEB"
	mv vsm vsm4web
clean:
	rm *.o
	rm vsm vsm4web