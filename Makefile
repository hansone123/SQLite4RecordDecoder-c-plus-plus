
include config.mk


SRC = \
    $(TOP)/src/rd.cc \
    $(TOP)/src/record.cc

HDR = \
    $(TOP)/src/rd.h \
    $(TOP)/src/ErrMsg.h \
    $(TOP)/src/datatype.h \
    $(TOP)/src/record.h

OBJ = \
    $(TOP)/obj/rd.o
OBJLIST = \
    rd.o \
    record.o

all:	$(OBJLIST) test
	
rd.o:
	g++ -o $(TOP)/obj/rd.o -c $(TOP)/src/rd.cc $(HDR) 
record.o:
	g++ -o $(TOP)/obj/record.o -c $(TOP)/src/record.cc $(HDR) 
	
test: testRD testRecord

testRD:
	g++ -o $(TOP)/test/testRD$(EXE) $(TOP)/test/testRD.cc $(HDR) $(SRC) $(LIBLEVELDB)
testRecord:
	g++ -o $(TOP)/test/testRecord$(EXE) $(TOP)/test/testRecord.cc $(HDR) $(SRC)
clean:
	rm $(TOP)/test/test*$(EXE)
	rm $(TOP)/obj/*
	