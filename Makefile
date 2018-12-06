CC=clang
CPPCHECK=cppcheck
CFLAGS=-Wall -Werror
LDFLAGS=-lSDL2
BINARY=tetris
BINARY_TESTS=tetris_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

tetris: main.o tetris.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c
	$(CPPCHECK) $^
	$(CC) -c -o $@ $(CFLAGS) $^

tetris.o: tetris.c tetris.h
	$(CPPCHECK) $^
	$(CC) -c -o $@ $(CFLAGS) $<

tests.o: tests.c
	$(CPPCHECK) $^
	$(CC) -c -o $@ $(CFLAGS) $^

test: tests.o tetris.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)
