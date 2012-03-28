DTDPREFIX=xylodtd

CC	= g++
CCFLAGS	= -Wall -g
EDL	= g++
LDFLAGS	= -g -DDYDEBUG=1
LIBS = 
SRC	= $(wildcard *.cpp)
OBJS	= $(SRC:.cpp=.o) lex.$(DTDPREFIX).o $(DTDPREFIX).tab.o
EXE     = analyseDTD

all: analyseDTD

%.o : %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<
	
%.o : %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
lex.$(DTDPREFIX).c: $(DTDPREFIX).l
	flex -P$(DTDPREFIX) $(DTDPREFIX).l
	
$(DTDPREFIX).tab.h $(DTDPREFIX).tab.c: $(DTDPREFIX).y
	bison -p$(DTDPREFIX) --debug --verbose --defines=$(DTDPREFIX).tab.h $(DTDPREFIX).y
	
bison : lex.$(DTDPREFIX).c $(DTDPREFIX).tab.h lex.$(DTDPREFIX).c
	
objs : bison $(OBJS)
analyseDTD: objs
	$(EDL) $(LDFLAGS) -o $(EXE) $(OBJS) $(LIBS)

clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output $(OBJS) $(EXE)

