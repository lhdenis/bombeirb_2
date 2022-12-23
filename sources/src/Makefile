#-------------------------------------------------------------------------------
# This file is part of Bombeirb.
# Copyright (C) 2018 by Laurent Réveillère
#-------------------------------------------------------------------------------
CC = gcc

SDLCFLAGS = `sdl-config  --cflags`
SDLLDFLAGS = `sdl-config --libs` 

CFLAGS = -Wall -O0 -g -std=c99 -I../include/ $(SDLCFLAGS)
LDFLAGS = $(SDLLDFLAGS) -lSDL_image
DEPFLAGS = -I../include 

SRC  = $(wildcard $(SRCDIR)/*.c)
OBJ  = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: all 
all : $(BINDIR)/$(EXEC) 

ifndef SRCDIR
	$(error SRCDIR is not set)
endif

ifndef OBJDIR
	$(error OBJDIR is not set)
endif

ifndef BINDIR
	$(error BINDIR is not set)
endif

ifndef EXEC
	$(error EXEC is not set)
endif

$(BINDIR)/$(EXEC) : $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(OBJDIR)/%.d
	$(CC) -c $(CFLAGS) -o $@ $< 

$(OBJDIR)/%.d : $(SRCDIR)/%.c 
	$(CC) -MM $(DEPFLAGS) $< > $@

-include $(SRC:%.c=%.d)
