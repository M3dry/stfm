CC=clang
CFLAGS=-g -Wall
LIBS=-lcursesw -lm
OBJ=obj
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN=stfm
BINDIR=bin

all: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ)/* $(BINDIR)/*
