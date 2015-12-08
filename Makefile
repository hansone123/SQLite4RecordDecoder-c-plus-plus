
include config.mk


SRC = \
    $(TOP)/src/rd.cc \

HDR = \
    $(TOP)/src/rd.h \
    $(TOP)/src/ErrMsg.h \
    $(TOP)/src/datatype.h

OBJ = \
    $(TOP)/obj/rd.o
OBJLIST = \
    rd.o

all:	$(OBJLIST) test
	
rd.o:
	g++ -o $(TOP)/obj/rd.o -c $(TOP)/src/rd.cc $(HDR) 
	
test:
	g++ -o $(TOP)/test$(EXE) $(TOP)/src/main.cc $(HDR) $(SRC) $(LIBLEVELDB)
	
clean:
	rm $(TOP)/test$(EXE)
	rm $(TOP)/obj/*
	
run:
	./test$(EXE)