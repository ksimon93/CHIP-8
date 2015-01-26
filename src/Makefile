CC=clang
CFLAGS=-Wall
LDFLAGS=-framework GLUT -framework OpenGL -framework Cocoa
SOURCES = $(wildcard *.c)
OBJS=$(SOURCES:.c=.o)
ALL_FILES = $(wildcard ../src/*.c)
NO_MAIN = $(filter-out ../src/main.c,$(ALL_FILES))
EXECUTABLE=CHIP-8

all: $(OBJS)
	$(CC) $(CFLAGS) $(ALL_FILES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm *.o
	rm CHIP-8
