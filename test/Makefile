CC=clang
CFLAGS=-Wall
OBJECTS=check_cpu.o
EXECUTABLE=TEST

test: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm TEST