XMLPREFIX=xyloxml

CC	= g++
CCFLAGS	= -Wall -g
EDL	= g++
LDFLAGS	= -g -DDYDEBUG=1
LIBS = 
SRC	= $(wildcard *.cpp)
OBJS	= $(SRC:.cpp=.o)
EXE     = analyseXML

all: analyseXML

%.o : %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<
	
bison : $(XMLPREFIX).l $(XMLPREFIX).y
	flex -P$(XMLPREFIX) $(XMLPREFIX).l
	bison -p$(XMLPREFIX) --debug --verbose --defines=$(XMLPREFIX).tab.h $(XMLPREFIX).y
	
objs : bison $(OBJS)
	$(CC) $(CCFLAGS) -o lex.$(XMLPREFIX).o -c lex.$(XMLPREFIX).c
	$(CC) $(CCFLAGS) -o $(XMLPREFIX).tab.o -c $(XMLPREFIX).tab.c

analyseXML: objs
	$(EDL) $(LDFLAGS) -o $(EXE) lex.$(XMLPREFIX).o  $(XMLPREFIX).tab.o $(OBJS) $(LIBS)

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output $(OBJS) $(EXE)

