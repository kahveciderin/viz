CC=g++
FLAGS=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))
BUILDNAME:=vrk

ifeq ($(BUILDTYPE),DEBUG):
	FLAGS+=-DDEBUG
	BUILDNAME=vizier
endif
ifeq ($(BUILDTYPE),WEB):
	FLAGS+=-DVIZ4WEB
	BUILDNAME=viz4web
endif


build: $(OBJS) buildcommon
	$(CC) $(OBJS) $(wildcard common/*.o) $(FLAGS) -o build/$(BUILDNAME)
	$(MAKE) partclean
%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
buildcommon:
	$(MAKE) -C modules 
partclean:
	rm -f *.o
	$(MAKE) -C modules clean
clean: partclean
	rm -f build/*