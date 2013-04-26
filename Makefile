GCOV_OUTPUT = *.gcda *.gcno *.gcov 
GCOV_CCFLAGS = -fprofile-arcs -ftest-coverage
CC     = gcc
CCFLAGS = -g -O2 -Wall -Werror -W -fno-omit-frame-pointer -fno-common -fsigned-char $(GCOV_CCFLAGS)

all: tests

main.c:
	sh make-tests.sh > main.c

tests: main.c bitstream.o test_bitstream.c CuTest.c main.c
	$(CC) $(CCFLAGS) -o $@ $^
	./tests
	gcov main.c test_bitstream.c bitstream.c

bitstream.o: bitstream.c
	$(CC) $(CCFLAGS) -c -o $@ $^

clean:
	rm -f main.c bitstream.o tests $(GCOV_OUTPUT)
