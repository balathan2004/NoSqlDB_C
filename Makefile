CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude -Ilibs/cJSON

SRC_DIRS = src libs/cJSON
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) main.c
OBJS = $(SRCS:.c=.o)
EXEC = nosql-db

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
