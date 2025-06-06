CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lm

# Object files
OBJS = main.o utils.o

# Target executable
TARGET = myht

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJS) $(TARGET)
