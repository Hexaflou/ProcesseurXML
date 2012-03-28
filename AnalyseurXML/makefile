XMLPREFIX=xyloxml

CC	= g++
CCFLAGS	= -Wall -g
EDL	= g++
LDFLAGS	= -g -DDYDEBUG=1
LIBS = 
SRC	= $(wildcard *.cpp)
OBJS	= $(SRC:.cpp=.o) lex.$(XMLPREFIX).o  $(XMLPREFIX).tab.o
EXE     = analyseXML

all: analyseXML

%.o : %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

%.o : %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
lex.$(XMLPREFIX).c: $(XMLPREFIX).l
	flex -P$(XMLPREFIX) $(XMLPREFIX).l
	
$(XMLPREFIX).tab.h $(XMLPREFIX).tab.c: $(XMLPREFIX).y
	bison -p$(XMLPREFIX) --debug --verbose --defines=$(XMLPREFIX).tab.h $(XMLPREFIX).y
	
bison : lex.$(XMLPREFIX).c $(XMLPREFIX).tab.h lex.$(XMLPREFIX).c
	
objs : bison $(OBJS)
	
analyseXML: objs
	$(EDL) $(LDFLAGS) -o $(EXE) lex.$(XMLPREFIX).o  $(XMLPREFIX).tab.o $(OBJS) $(LIBS)

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output $(OBJS) $(EXE)

