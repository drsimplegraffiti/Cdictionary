
CC = gcc
CFLAGS = -Wall
LIBS = -lmysqlclient

TARGET = library
SRCS = main.c db.c books.c members.c borrowings.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
