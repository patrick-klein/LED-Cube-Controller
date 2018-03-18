BDIR=bin
IDIR=inc
LDIR=lib
ODIR=obj
SDIR=src

_INC = common.h Animation.h AnimateBullet.h EdgeLight.h Raindrops.h MovingPlane.h RandomToggle.h
INC = $(patsubst %,$(IDIR)/%,$(_INC))

_OBJ = main.o AnimateBullet.o EdgeLight.o Raindrops.o MovingPlane.o RandomToggle.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CC=clang++
CFLAGS= -std=c++11 -stdlib=libc++
IFLAGS=-I$(IDIR)
LFLAGS=-L$(LDIR) -liofunc

.DEFAULT_GOAL := all

install : clean $(LDIR)/libiofunc.a $(BDIR)/ledCube

all : $(BDIR)/ledCube

clean:
	rm -f $(ODIR)/*
	rm -f $(BDIR)/*

$(BDIR)/ledCube : $(OBJ)
	$(CC) $(OBJECTS) $(LFLAGS) $(IFLAGS) -o bin/ledCube

$(ODIR)/main.o : $(SDIR)/main.cpp $(INC)
	$(CC) $(CFLAGS) -c $(IFLAGS) -o $@ $<

$(ODIR)/%.o : $(SDIR)/%.cpp $(IDIR)/common.h $(IDIR)/%.h
	$(CC) $(CFLAGS) -c $(IFLAGS) -o $@ $<

$(LDIR)/libiofunc.a:
	rm -f $(LDIR)/libiofunc.a
	cd iofunc
	$(MAKE) lib
	cd ..
	mv iofunc/libiofunc.a $(LDIR)
