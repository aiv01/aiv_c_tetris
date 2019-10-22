CC = clang
CPPCHECK = cppcheck
CFLAGS = -Iinclude -Wall -O3
LDFLAGS = -lSDL2
BINARY = tetris
BINARY_TESTS = tetris_tests
OBJ = src/

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

tetris: main.o tetris.o gfx.o sfx.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^
	./$(BINARY)

main.o: src/main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

tetris.o: src/tetris.c include/tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

gfx.o: src/gfx.c include/tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

sfx.o: src/sfx.c include/tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

tests.o: src/tests.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

test: tests.o tetris.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)
	rm -f *.o tetris tetris_tests

clean: 
	rm -f *.o tetris tetris_tests