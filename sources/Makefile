#-------------------------------------------------------------------------------
# This file is part of Bombeirb.
# Copyright (C) 2018 by Laurent Réveillère
#-------------------------------------------------------------------------------
SRCDIR = src
BINDIR = bin
OBJDIR = .obj
EXEC   = bombeirb

all: $(OBJDIR) $(BINDIR)
	@cd $(OBJDIR) ; make -f ../$(SRCDIR)/Makefile SRCDIR=../$(SRCDIR) OBJDIR=../$(OBJDIR) BINDIR=../$(BINDIR) EXEC=$(EXEC)

$(OBJDIR) $(BINDIR):
	-mkdir $@

.ONESHELL:

clean :
	-rm -rf $(BINDIR) $(OBJDIR)
	
mrproper : clean
	-rm -rf .project .cproject .settings '*~' #*

archive:
	-zip -9 -r bombeirb-`date +'%y-%m-%d-%Hh%M'`.zip . -x "*/\.*" -x "\.*" -x "bin/*" -x "*.zip" -x "*~"

