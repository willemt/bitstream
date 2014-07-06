GCOV_OUTPUT = *.gcda *.gcno *.gcov 
GCOV_CCFLAGS = -fprofile-arcs -ftest-coverage
CC     = gcc
CCFLAGS = -I. -Itests -g -O2 -Wall -Werror -Wcast-align -fno-omit-frame-pointer -fno-common -fsigned-char $(GCOV_CCFLAGS)

all: test

main.c:
	sh tests/make-tests.sh tests/test_*.c > main.c

test: main.c bitstream.o tests/test_bitstream.c tests/CuTest.c main.c
	$(CC) $(CCFLAGS) -o $@ $^
	./test
	gcov main.c tests/test_bitstream.c bitstream.c

bitstream.o: bitstream.c
	$(CC) $(CCFLAGS) -c -o $@ $^

clean:
	rm -f main.c bitstream.o test $(GCOV_OUTPUT)
