YYPREFIX=xyloxml

all: analyseXML
analyseXML: *.l *.y makefile
	flex -P$(YYPREFIX) xml.l
	bison -p$(YYPREFIX) --debug --verbose --defines=$(YYPREFIX).tab.h xml.y
	g++ -g -DYYDEBUG=1 -o analyseXML  lex.$(YYPREFIX).c  xml.tab.c 
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML

