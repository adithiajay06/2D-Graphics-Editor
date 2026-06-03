CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = editor

SRCS = main.c canvas.c shapes.c menu.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
