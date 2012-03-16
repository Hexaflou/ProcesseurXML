%{

void yyerror(char *msg);
int yywrap(void);
int yylex(void);
%}

%parse-param {DtdDoc *d}

%union { 
   char *s; 
   }

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING
%%


main
: dtd_list_opt				
;


dtd_list_opt
: dtd_list_opt dtd_declaration CLOSE	{d->addElement($2);}
| /* empty */		
;

dtd_declaration
: ELEMENT IDENT list	{$$ = new DtdElement($2); $$->completeChildPattern($3);}
| ATTLIST IDENT att_definition_opt {for(int i = 0; i < $3->size(); i++) { d->addAttributetoElement($2,(*$3)[i]);}}
;

list
: enumerate		{$$ = $1;}
| seq			{$$ = $1;}
;

/* SEQUENCE */
seq
: OPENPAR seq_list CLOSEPAR card_opt	{$$ = new string("("); $$ += $2+ ")" + $3;}
;
seq_list
: seq_list COMMA cp	{$$ = $1+","+$2;}
| cp			{$$ = $1;}
| PCDATA		{$$ = $1;}
| /*empty*/		{$$ = new string("");}
;
cp
: IDENT card_opt	{$$ = new string($1); $$+=$2;}
| enumerate card_opt	{$$ = $1+$2;} 
| seq card_opt		{$$ = $1+$2;}
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
: att_definition_opt attribute	{$$=$1; $$->push_back($2);}
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
: OPENPAR enum_list_plus CLOSEPAR card_opt {$$ = new string("("); $$ += $2+ ")" + $3;}
;
enum_list_plus
: enum_list PIPE item_enum	{$$ = $1+"|"+$2;}
;
enum_list
: enum_list PIPE item_enum	{$$ = $1+"|"+$2;}
| item_enum			{$$ = $1;}
| PCDATA	{$$ = new string($1);}
;
item_enum
: IDENT		{$$ = new string($1);}
;



%%
int main(int argc, char **argv)
{
  int err;

  yydebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
        else  printf("Parse ended with success\n", err);
  return 0;
}
int yywrap(void)
{
  return 1;
}

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}


