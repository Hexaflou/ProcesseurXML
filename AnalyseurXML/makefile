YYPREFIX=xyloxml

all: analyseXML
analyseXML: *.l *.y makefile
	flex -P$(YYPREFIX) $(YYPREFIX).l
	bison -p$(YYPREFIX) --debug --verbose --defines=$(YYPREFIX).tab.h $(YYPREFIX).y
	g++ -g -DYYDEBUG=1 -o analyseXML  lex.$(YYPREFIX).c  $(YYPREFIX).tab.c 
clean:
	-rm -rf *.tab.c lex.*.c *.tab.h *.output analyseXML

