%{

#include "commun.h"
#include <iostream>

void xylodtderror(DtdDoc *d, char const *msg);
static int yywrap(void);
int xylodtdlex(void);

%}

%parse-param {DtdDoc *d}

%error-verbose

%union { 
	char *s;
	string *st;
	vector<string> *vst;
	DtdElement *dtdElem;
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING PCDATA
%type <st> cp seq_list seq card_opt attribute enumerate enum_list_plus enum_list item_enum list
%type <vst> att_definition_opt 
%type <dtdElem> dtd_declaration
%%


main
: dtd_list_opt				
;


dtd_list_opt
	: dtd_list_opt dtd_declaration CLOSE	{ if($2 != 0) d->addElement(*$2);}
| /* empty */		
;

dtd_declaration
: ELEMENT IDENT list	{
	$$ = new DtdElement($2); 
	$$->completeChildPattern(*$3);
  }
| ATTLIST IDENT att_definition_opt {
	for(int i = 0; i < $3->size(); i++) { 
		d->addAttributetoElement($2, (*$3)[i]);
	}
	$$ = 0;
  }
;

list
: enumerate		{$$ = $1;}
| seq			{$$ = $1;}
;

/* SEQUENCE */
seq
: OPENPAR seq_list CLOSEPAR card_opt	{ $$ = new string("(" + *$2 + ")" + *$4); }
;
seq_list
: seq_list COMMA cp	{$$ = new string(*$1+","+*$3);}
| cp			{$$ = new string(*$1);}
| PCDATA		{$$ = new string($1);}
| /*empty*/		{$$ = new string("");}
;
cp
: IDENT card_opt	{$$ = new string($1 + *$2);}
| enumerate	{$$ = new string(*$1);} 
| seq		{$$ = new string(*$1);}
;

/* GENERAL */
card_opt
: QMARK			{$$ = new string("?");}
| PLUS			{$$ = new string("+");}
| AST			{$$ = new string("*");}
| /* empty */		{$$ = new string("");}
;

/* ATTRIBUTS */
att_definition_opt
: att_definition_opt attribute	{$$=$1; $$->push_back(*$2);}
| /* empty */	{$$ = new vector<string>();}
;
attribute
: IDENT att_type default_declaration	{$$ = new string($1);}
;
att_type
: CDATA
| TOKENTYPE
| list
;
default_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;

/* ENUMERATE */
enumerate
: OPENPAR enum_list_plus CLOSEPAR card_opt {$$ = new string("(" + *$2 + ")" + *$4);}
;
enum_list_plus
: enum_list PIPE item_enum	{$$ = new string(*$1 + "|" + *$3);}
;
enum_list
: enum_list PIPE item_enum	{$$ = new string(*$1 + "|" + *$3);}
| item_enum			{$$ = new string(*$1);}
;
item_enum
	: IDENT		{$$ = new string("("+string($1)+" )");}
| PCDATA  {$$ = new string($1);}
;



%%

int yywrap(void)
{
	return 1;
}




