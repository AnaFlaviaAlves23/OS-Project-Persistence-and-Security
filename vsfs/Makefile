CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = vsfs

SRCS = main_vsfs.c vsfs_format.c vsfs_disk.c vsfs_control.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c vsfs.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) disco.img

.PHONY: all clean