CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Ilibs/cJSON

SRC_DIRS = . commands db utils libs/cJSON


SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS = $(SRCS:.c=.o)
EXEC = nosql-db

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
