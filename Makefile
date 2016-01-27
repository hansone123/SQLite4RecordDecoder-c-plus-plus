include config.mk


SRC := $(wildcard $(TOP)/src/*.cc)
	
HDR := $(wildcard $(TOP)/src/*.h)

OBJ := $(patsubst %.cc,%.o,$(wildcard $(TOP)/src/*.cc))
OBJ := $(patsubst $(TOP)/src/%, %,$(OBJ))
	

all: check library test 
	
check:
	echo 'HDR: $(HDR)'
	echo 'SRC: $(SRC)'
	echo 'OBJ: $(OBJ)'
	
library:	$(OBJ)
	$(AR) libRD.a $(TOP)/obj/*.o libleveldb.a
	$(RANLIB) libRD.a
%.o: $(TOP)/src/%.cc $(HDR)
	g++ -o $(TOP)/obj/$@ -c $<


test: testRD testRecord

testRD:
	g++ -o $(TOP)/test/testRD$(EXE) $(TOP)/test/testRD.cc $(HDR) libRD.a $(LIBPTHREAD) $(LIBLEVELDB)
testRecord:
	g++ -o $(TOP)/test/testRecord$(EXE) $(TOP)/test/testRecord.cc $(HDR) libRD.a
clean:
	rm $(TOP)/test/test*$(EXE)
	rm $(TOP)/obj/*
testcmd:
	echo $(OBJ)