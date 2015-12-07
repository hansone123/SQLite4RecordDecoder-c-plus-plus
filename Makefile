
include config.mk


SRC = \
    $(TOP)/src/rd.cc \
    $(TOP)/src/main.cc
HDR = \
    $(TOP)/src/rd.h
OBJ = \
    $(TOP)/obj/rd.o


all:	rd.o test$(EXE)
	
rd.o:	$(SRC) $(HDR)
	g++ -o ./obj/rd.o $(SRC) $(HDR)
	
test$(EXE): $(OBJ) $(HDR)
	g++ -o test$(EXE) $(SRC) $(HDR)
	
clean:
	rm test$(EXE)
	
run:
	./test$(EXE)