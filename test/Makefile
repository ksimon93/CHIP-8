CC=clang
CFLAGS=-Wall
SOURCES = $(wildcard *.c)
OBJS=$(SOURCES:.c=.o)
TESTS=$(SOURCES:.c=)
ALL_FILES = $(wildcard ../src/*.c) $(wildcard ../test/*.c)
NO_MAIN = $(filter-out ../src/main.c,$(ALL_FILES))
EXECUTABLE=TEST

all: $(TESTS)

$(TESTS): $(OBJS)
	$(CC) $(CFLAGS) $(NO_MAIN) -o $(EXECUTABLE)

clean:
	rm *.o
	rm TEST