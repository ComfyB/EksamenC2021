# Makefile template

INCLDIR = ./include
CC = gcc -g
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)

OBJDIR = obj

_DEPS = source.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = source.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

SOURCE: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

.PHONY: clean
clean: 
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
         