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

all : $(BDIR)/ledCube

$(BDIR)/ledCube : $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(IFLAGS) -o $@

build : $(OBJ)

$(ODIR)/main.o : $(SDIR)/main.cpp $(INC)
	$(CC) $(CFLAGS) -c $(IFLAGS) -o $@ $<

$(ODIR)/%.o : $(SDIR)/%.cpp $(IDIR)/common.h $(IDIR)/%.h $(IDIR)/Animation.h
	$(CC) $(CFLAGS) -c $(IFLAGS) -o $@ $<

install : clean $(LDIR)/libiofunc.a $(BDIR)/ledCube

$(LDIR)/libiofunc.a:
	rm -f $(LDIR)/libiofunc.a
	cd iofunc
	$(MAKE) lib
	cd ..
	mv iofunc/libiofunc.a $(LDIR)

clean:
	rm -f $(ODIR)/*
	rm -f $(BDIR)/*
