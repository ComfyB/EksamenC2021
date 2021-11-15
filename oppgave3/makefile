# Makefile template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2 
CFLAGS += -I $(INCLDIR)

OBJDIR = obj

_DEPS = opg3.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = opg3.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OPG3: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean: 
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
         