CC = gcc
CFLAGS = -Wall -g
TARGET = game_search

# Source files
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
   $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
   $(CC) $(CFLAGS) -c $< -o $@

clean:
   rm -f $(TARGET) $(OBJS)
