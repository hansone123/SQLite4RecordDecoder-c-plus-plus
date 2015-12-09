
include config.mk


SRC := $(wildcard $(TOP)/src/*.cc)
	
HDR := $(wildcard $(TOP)/src/*.h)


OBJ := $(patsubst %.cc,%.o,$(wildcard $(TOP)/src/*.cc))
OBJ := $(patsubst $(TOP)/src/%, %,$(OBJ))
	
OBJLIST = \
    rd.o \
    record.o 

all: $(OBJ) test
	
%.o: $(TOP)/src/%.cc $(HDR)
	g++ -o $(TOP)/obj/$@ -c $<

test: testRD testRecord

testRD:
	g++ -o $(TOP)/test/testRD$(EXE) $(TOP)/test/testRD.cc $(HDR) $(SRC) $(LIBLEVELDB)
testRecord:
	g++ -o $(TOP)/test/testRecord$(EXE) $(TOP)/test/testRecord.cc $(HDR) $(SRC)
clean:
	rm $(TOP)/test/test*$(EXE)
	rm $(TOP)/obj/*
testcmd:
	echo $(OBJ)