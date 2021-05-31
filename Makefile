CC=g++
FLAGS?=-I.

ifeq ($(PARAMS),DBG)
	FLAGS+=-g3 -O0 -Wall -Wextra
endif

all: vizier vrk vsm
release: all
	$(MAKE) clean
	zip -r viz_suite.zip build/
vizier:
	$(MAKE) -C runtime vizier
vrk:
	$(MAKE) -C runtime vrk
vsm:
	$(MAKE) -C assembler vsm
vsm4web:
	$(MAKE) -C assembler vsm4web
%.o: %.cpp
	$(CC) $< $(FLAGS) -c -o $@
clean:
	$(MAKE) -C runtime clean
	$(MAKE) -C assembler 
assemble_tests: vsm
	build/vsm hello.viz hello.vsm
tests: assemble_tests vrk
	build/vrk hello.vsm