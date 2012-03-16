DTDPREFIX=xylodtd

all: analyseDTD
analyseDTD: *.l *.y makefile
	flex -P$(DTDPREFIX) $(DTDPREFIX).l
	bison -p$(DTDPREFIX) --debug --verbose --defines=$(DTDPREFIX).tab.h $(DTDPREFIX).y
	g++ -g -DYYDEBUG=1 -o analyseDTD  lex.$(DTDPREFIX).c  $(DTDPREFIX).tab.c 
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseDTD

