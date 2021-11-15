
INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)

OBJDIR = obj

_DEPS = opg2.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = opg2.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OPG2: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -lm

.PHONY: clean
clean: 
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
         