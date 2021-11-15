# Makefile template

INCLDIR = ./include
CC = gcc -g
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)

OBJDIR = obj

_DEPS = opg4.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = opg4.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OPG4: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

.PHONY: clean
clean: 
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
         