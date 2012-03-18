DTDPREFIX=xylodtd

CC	= g++
CCFLAGS	= -Wall -g
EDL	= g++
LDFLAGS	= -g -DDYDEBUG=1
LIBS = 
SRC	= $(wildcard *.cpp)
OBJS	= $(SRC:.cpp=.o)
EXE     = analyseDTD

all: analyseDTD

%.o : %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

analyseDTD: *.l *.y $(OBJS)
	flex -P$(DTDPREFIX) $(DTDPREFIX).l
	bison -p$(DTDPREFIX) --debug --verbose --defines=$(DTDPREFIX).tab.h $(DTDPREFIX).y
	$(EDL) $(LDFLAGS) -o $(EXE) lex.$(DTDPREFIX).c  $(DTDPREFIX).tab.c $(OBJS) $(LIBS)

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output $(OBJS) analyseDTD

