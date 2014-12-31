CC=clang
CFLAGS=-Wall
OBJECTS=cpu.o gfx.o mem.o input.o main.o
EXECUTABLE=CHIP-8

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm CHIP-8