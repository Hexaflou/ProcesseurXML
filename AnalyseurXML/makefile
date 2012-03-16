XMLPREFIX=xyloxml

all: analyseXML
analyseXML: *.l *.y makefile
	flex -P$(XMLPREFIX) $(XMLPREFIX).l
	bison -p$(XMLPREFIX) --debug --verbose --defines=$(XMLPREFIX).tab.h $(XMLPREFIX).y
	g++ -g -DYYDEBUG=1 -o analyseXML  lex.$(XMLPREFIX).c  $(XMLPREFIX).tab.c 
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML

