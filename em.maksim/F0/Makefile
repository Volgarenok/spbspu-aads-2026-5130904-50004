CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = dbd_coursework
SOURCES = main.c hash.c knapsack.c commands.c
HEADERS = types.h hash.h knapsack.h commands.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean
