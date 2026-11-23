CC     = gcc
CFLAGS = -O2 -Wall -Wextra -std=c11

FF = finite_field_arithmetic.c

.PHONY: all test clean

all: test_encode test_decode

# Task 1.1: matrix-vector encoder + small test program
test_encode: test_encode.c encode.c $(FF) finite_field_arithmetic.h
	$(CC) $(CFLAGS) -o $@ test_encode.c encode.c $(FF)

# Task 1.2: Lagrange decoder (round trip encode -> decode)
test_decode: test_decode.c decode.c encode.c $(FF) finite_field_arithmetic.h
	$(CC) $(CFLAGS) -o $@ test_decode.c decode.c encode.c $(FF)

test: all
	./test_encode
	./test_decode

clean:
	rm -f test_encode test_decode
