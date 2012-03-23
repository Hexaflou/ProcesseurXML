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
	
bison : $(DTDPREFIX).l $(DTDPREFIX).y
	flex -P$(DTDPREFIX) $(DTDPREFIX).l
	bison -p$(DTDPREFIX) --debug --verbose --defines=$(DTDPREFIX).tab.h $(DTDPREFIX).y
	
objs : bison $(OBJS)
	$(CC) $(CCFLAGS) -o lex.$(DTDPREFIX).o -c lex.$(DTDPREFIX).c
	$(CC) $(CCFLAGS) -o $(DTDPREFIX).tab.o -c $(DTDPREFIX).tab.c

analyseDTD: objs
	$(EDL) $(LDFLAGS) -o $(EXE) lex.$(DTDPREFIX).o  $(DTDPREFIX).tab.o $(OBJS) $(LIBS)

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output $(OBJS) $(EXE)

