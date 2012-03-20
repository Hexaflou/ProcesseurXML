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

analyseXML: *.l *.y $(OBJS)
	flex -P$(XMLPREFIX) $(XMLPREFIX).l
	bison -p$(XMLPREFIX) --debug --verbose --defines=$(XMLPREFIX).tab.h $(XMLPREFIX).y
	$(EDL) $(LDFLAGS) -o $(EXE)  lex.$(XMLPREFIX).c  $(XMLPREFIX).tab.c $(OBJS) $(LIBS)
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output $(OBJS) $(EXE)

