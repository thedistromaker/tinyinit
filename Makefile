CC = gcc
CFLAGS = -Wall -static
SRCS = init.c mounts.c login.c shutdown.c
OBJS = $(SRCS:.c=.o)
TARGET=init

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET) *.o
