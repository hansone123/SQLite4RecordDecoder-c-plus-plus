
include config.mk


SRC = \
    $(TOP)/src/rd.cc
HDR = \
    $(TOP)/src/rd.h



all:	test$(EXE)
	
test$(EXE):	$(SRC) $(HDR)
	g++ -o test$(EXE) $(SRC) $(HDR)
	
clean:
	rm test$(EXE)
	
run:
	./test$(EXE)