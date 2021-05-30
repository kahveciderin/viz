CC=g++
FLAGS=-I.
FILES=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp, %.o, $(FILES))
BUILDNAME:=vrk


ifeq ($(BUILDTYPE),RUNTIME)
	FLAGS+=-DRUNTIME
	BUILDNAME=vrk
endif
ifeq ($(BUILDTYPE),ASSEMBLER)
	FLAGS+=-DASSEMBLER
	BUILDNAME=vsm
endif
ifeq ($(BUILDTYPE),DEBUG)
	FLAGS+=-DDEBUG -DRUNTIME
	BUILDNAME=vizier
endif
ifeq ($(BUILDTYPE),WEB)
	FLAGS+=-DVIZ4WEB -DASSEMBLER -DRUNTIME
	BUILDNAME=viz4web
endif
ifeq ($(PARAMS),DBG)
	FLAGS+=-g3 -O0
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