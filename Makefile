CC :=gcc
C_SOURCES :=$(wildcard src/*.c)
C_EXECUTABLE :=$(C_SOURCES:.c=)
 
all: $(C_EXECUTABLE)

$(C_EXECUTABLE):$(C_SOURCES)
	$(CC) $< $(LDFLAGS) $(CFLAGS) -o bin/KessC

clean:
	rm -rf $(EXECUTABLE)
