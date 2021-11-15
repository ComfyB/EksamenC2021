# Makefile template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)

OBJDIR = obj

_DEPS = opg5.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = opg5.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OPG5: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -pthread

.PHONY: clean
clean: 
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
         