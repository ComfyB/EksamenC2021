# Makefile template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2 -g
CFLAGS += -I $(INCLDIR)

OBJDIR = obj

_DEPS = opg6.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = opg6.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OPG6: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
         